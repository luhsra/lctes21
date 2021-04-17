#include "DataFlowPruner.hpp"

#include <fstream>
#include <regex>
#include <sstream>
#include <unordered_map>

#include "util/Logger.hpp"

using namespace fail;

using std::endl;
using DFNode = DataFlowPruner::DataFlowGraph::DFNode;
using DFLink = DataFlowPruner::DataFlowGraph::DFLink;

bool DataFlowPruner::commandline_init() {

    if (!cmd.parse()) {
        std::cerr << "Error parsing arguments." << endl;
        return false;
    }

    ELF_FILE = cmd.addOption("e", "elf-file", Arg::Required,
        "-e/--elf-file \tELF File (default: UNSET)");

    FLAGS = cmd.addOption("", "flags", Arg::None,
        "--flags \tInclude EFLAGS register");

    NO_LOCAL_RULES = cmd.addOption("", "no-local-semantics", Arg::None,
        "--no-local-semantics\tIgnore all local masking rules and do global ones only.");

    //IP    = cmd.addOption("", "ip", Arg::None,
    //    "--ip \tInclude instruction pointer");

    PRINT_TRACE = cmd.addOption("", "trace", Arg::None,
        "--trace\tPrint trace with register and memory accesses.");

    DOT = cmd.addOption("", "dot", Arg::Numeric,
        "--dot <n>\tCreate a DOT file for every variant data-flow graph but the first <n> links only.");

    DOT_START_AT = cmd.addOption("", "dot-start-at", Arg::Numeric,
        "--dot-start-at <n>\tWhen --dot <n>, start printing with the <n>th link.");

    DOT_FULL = cmd.addOption("", "dot-full", Arg::None,
        "--dot-full\tCreate a DOT file for every complete variant data-flow graph.");

    DOT_MASKS = cmd.addOption("", "masks", Arg::None,
        "--masks\tWhen --dot-full or --dot <n>, print injection masks in DOT file.");

    STATS = cmd.addOption("", "stats", Arg::None,
        "--stats\tPrint some stats of the pruning method.");

    return true;
}

bool DataFlowPruner::prune_all(){
    if(m_variants.size() == 0){
        LOG << "No variants found. Specify variant for the correct objdump data from the data base with -v VARIANT or --variant VARIANT (-b or --benchmark does not matter for this pruner. Fault space of DataFlowPruner contains both registers and memory). Abort." << endl;
        return false;
    }

    variant_t& var = m_variants.at(0);
    for(unsigned int i = 1; i < m_variants.size(); i++){
        if(var.variant.compare(m_variants.at(i).variant) != 0){
            LOG << "Several variants found. Specify variant for the correct objdump data from the data base with -v VARIANT or --variant VARIANT (-b or --benchmark does not matter for this pruner. Fault space of DataFlowPruner contains both registers and memory). Abort." << endl;
            return false;
        }
    }

    LOG << "Pruning for variant: " << var.variant << endl;

    //import disassemble string for regex processing
    //registers used as pointer, memory offset, constants can be determined
    if(!this->import_objdump(var)) return false;

    //TODO non-final, should be removed and integrated to data_flow_graph
    if(!this->import_trace()) return false;

    //construct the data-flow graph from the sql data
    //also determine injection symbols
    if(!this->build_data_flow_graph()) return false;

    //set instruction-local injection masks for every single (defined) instruction.
    //an injection mask is a set of failure equivalence sets within the defs and uses of one instruction.
    //one set is defined as an unique symbol.
    if(!this->do_local_mask_rules()) return false;

    //determine failure equivalence sets over several injection masks
    //and create global injection masks.
    //one set is defined as an unique symbol.
    if(!this->do_global_mask_rules()) return false;

    //create an SQL table for injecting
    if(!this->create_tables()) return false;

    //fill the SQL table with injections
    if(!this->export_injections(var)) return false;

    if(cmd[PRINT_TRACE]){
        LOG << "Printing extended trace" << endl;
        for(TraceEventData& data : m_trace_data_list){
            LOG << "EVENT " << data.dynamic_instr
                << ":  IP " << std::hex << data.static_instr
                << " - time " << std::dec << data.dynamic_time
                << " | " << m_disas_string_map.at(data.static_instr)
                << endl;
            for(Data& d : data.uses){
                LOG << "  use address = " << d.address << " | value = " << d.value << endl;
            }
            for(Data& d : data.defs){
                LOG << "  def address = " << d.address << " | value = " << d.value << endl;
            }
            LOG << "" << endl;
        }
    }

    LOG << "end of pruning for variant: " << var.variant << endl << endl;

    if(cmd[DOT_MASKS] && !(cmd[DOT] || cmd[DOT_FULL])){
        LOG << "Printing masks require DOT parameter --dot <n> or --dot-full" << endl;
    }

    if(cmd[DOT] || cmd[DOT_FULL]){
        this->create_dot_file(var.variant);
        LOG << "DOT file created for variant " << var.variant << endl << endl;
    }

    if(cmd[STATS]){
        this->print_stats();
    }

    return true;
}


bool DataFlowPruner::import_objdump(const variant_t& var){

    std::stringstream ss;
    ss << "SELECT instr_address, disassemble, (char_length(opcode) DIV 2)  FROM objdump WHERE variant_id = "
       << var.id
       << " ORDER BY instr_address";

    MYSQL_RES *res = db->query_stream(ss.str().c_str());
    if (!res) {

        LOG << "ERROR: sql read to objdump table failed." << std::endl;
        return false;
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {

        address_t abs_instr =  std::strtoul(row[0], 0, 10);
        std::string disas =  row[1];
        this->m_disas_string_map[abs_instr] = disas;
        this->m_instruction_width_map[abs_instr] = std::strtoul(row[2], 0 , 10);
    }

    if (this->m_disas_string_map.size() == 0) {
        LOG << "ERROR: No objdump table found." << std::endl;
        return false;
    }

    LOG << "objdump: " << this->m_disas_string_map.size() << " instructions read." << endl;
    return true;
}


class TraceStream {
    fail::Logger LOG;;

    std::ifstream normal_stream;
    igzstream gz_stream;
    fail::ProtoIStream ps;

    std::istream &openStream(const char *input_file, std::ifstream& normal_stream, igzstream& gz_stream) {
        normal_stream.open(input_file);
        if (!normal_stream) {
            LOG << "couldn't open " << input_file << endl;
            exit(-1);
        }
        unsigned char b1, b2;
        normal_stream >> b1 >> b2;

        if (b1 == 0x1f && b2 == 0x8b) {
            normal_stream.close();
            gz_stream.open(input_file);
            if (!gz_stream) {
                LOG << "couldn't open " << input_file << endl;
                exit(-1);
            }
            LOG << "opened file " << input_file << " in GZip mode" << endl;
            return gz_stream;
        }

        normal_stream.seekg(0);

        LOG << "opened file " << input_file << " in normal mode" << endl;
        return normal_stream;
    }

public:
    TraceStream(std::string file) :
        LOG("trace_stream"), normal_stream(), gz_stream(),
        ps(&openStream(file.c_str(), normal_stream, gz_stream))
        {}

    bool next(Trace_Event& event){
        Trace_Event ev;
        if(ps.getNext(&ev)){
            event = ev;
            return true;
        }
        return false;
    }
};


bool DataFlowPruner::import_trace(){

    if(!m_is_disassembled){
        if(!disassemble()){
            LOG << "ERROR: Disassembling failed." << endl;
            return false;
        }
        LOG << "Disassembling done. Start streaming program trace." << endl;
    }

    TraceStream stream(trace_file);
    Trace_Event current_ev, next_ev;
    bool is_event_valid = stream.next(next_ev);
    assert(is_event_valid && "There must be at least one valid instruction."); (void) is_event_valid;

    unsigned instr = 0;
    unsigned curtime = 0;
    bool is_first_event = true;
    bool is_ip_between = false;
    bool is_last_event = false;
    Trace_Event previous_ev;
    TraceEventData current_event_data;

    //register def value is available after one complete ip event (including corresponding mem events)
    //mem values can be recorded one event earlier (read and write)
    //and will be added after the complte ip event
    std::vector<Data> current_mem_uses, current_mem_defs;

    while(true){
        previous_ev = current_ev;
        current_ev = next_ev;

        if(is_first_event){
            if(!current_ev.has_memaddr()){
                is_first_event = false;
                is_event_valid = stream.next(next_ev);
                continue;

            }else{
                LOG << "Trace startet with a memory event, but should be an IP event. Abort." << endl;
                return false;
            }
        }

        if (!current_ev.has_memaddr()){
            //sometime, for unknown reasons, traces contain events that
            //are contained within other instructions.
            static_instr_t l = previous_ev.ip();
            if(this->m_instruction_width_map.find(l) == m_instruction_width_map.end()){
                LOG << "WARNING: Instruction width for instruction 0x" << std::hex << current_ev.ip() << std::dec << " not available. " << endl;
                if(!stream.next(current_ev)) break;
                is_ip_between = true;
                continue;
            }

            static_instr_t w = this->m_instruction_width_map.at(l);
            if ( l < current_ev.ip() && current_ev.ip() < (l+w)) {
                LOG << "WARNING: Instruction within previous instruction: 0x" << std::hex << current_ev.ip() << std::dec << endl;
                if(!stream.next(current_ev)) break;
                is_ip_between = true;
                continue;
            }

            is_ip_between = false;

            if(!previous_ev.has_trace_ext()){
                LOG << "Extended trace needed. Unable to extract use and def registers. Abort." << endl;
                return false;
            }

            if (previous_ev.has_time_delta()) {
                //curtime also always holds the max time, provided we only get
                //nonnegative deltas
                assert(previous_ev.time_delta() >= 0);
                curtime += previous_ev.time_delta();
            }

            TraceEventData current_event_data;
            current_event_data.dynamic_instr = instr++;
            current_event_data.static_instr  = previous_ev.ip();
            current_event_data.dynamic_time = curtime;

            const Trace_Event_Extended& current_ev_ext = previous_ev.trace_ext();

            if(m_instr_map.find(previous_ev.ip()) == m_instr_map.end()){
                continue;
            }

            const CapstoneDisassembler::Instr& current_opcode = m_instr_map.at(previous_ev.ip());
            //uses
            for(std::vector<CapstoneDisassembler::register_t>::const_iterator it = current_opcode.reg_uses.begin();
                it != current_opcode.reg_uses.end();
                ++it){
                const CapstoneToFailTranslator::reginfo_t& disas_reg_info = m_ctof->getFailRegisterInfo(*it);
                if(&disas_reg_info == &m_ctof->notfound){
                    // record failed translation, report later
                    m_regnotfound[*it].count = instr;
                    m_regnotfound[*it].address.insert(previous_ev.ip());
                    continue;
                }

                //only proceed if we want to inject into this register
                if(m_register_ids.find(disas_reg_info.id) == m_register_ids.end()){
                    continue;
                }

                for(int i = 0; i < current_ev_ext.registers_size(); i++){
                    const Trace_Event_Extended_Registers& trace_reg_info = current_ev_ext.registers(i);

                    //find the value from tracing appropriate to the capstone register
                    if(disas_reg_info.id == trace_reg_info.id() && trace_reg_info.has_value()){
                        Data d;
                        d.address = disas_reg_info.toDataAddress();
                        //previous values for uses
                        d.value = trace_reg_info.value();
                        d.datatype = REGISTER;
                        current_event_data.uses.push_back(d);
                        break;
                    }
                }
            }

            //defs
            for(std::vector<CapstoneDisassembler::register_t>::const_iterator it = current_opcode.reg_defs.begin();
                it != current_opcode.reg_defs.end();
                ++it){
                const CapstoneToFailTranslator::reginfo_t& disas_reg_info = m_ctof->getFailRegisterInfo(*it);
                if(&disas_reg_info == &m_ctof->notfound){
                    // record failed translation, report later
                    m_regnotfound[*it].count = instr;
                    m_regnotfound[*it].address.insert(previous_ev.ip());
                    continue;
                }

                //only proceed if we want to inject into this register
                if(m_register_ids.find(disas_reg_info.id) == m_register_ids.end()){
                    continue;
                }

                for(int i = 0; i < current_ev_ext.registers_size(); i++){
                    const Trace_Event_Extended_Registers& trace_reg_info = current_ev_ext.registers(i);

                    //find the value from tracing appropriate to the capstone register
                    if(disas_reg_info.id == trace_reg_info.id() && trace_reg_info.has_value()){
                        Data d;
                        d.address = disas_reg_info.toDataAddress();
                        //next values for defs
                        if(is_last_event){
                            //dummy value for registers written
                            d.value = 0;
                            //memory events of the last instruction are missing
                            //because the tracing ended after processing
                            //the ip event of the last instruction.
                            //so, no memory defs are available for the last instruction,
                            //neither data values nor addresses.
                            //it can be ignored here because it will result in a write equivalence set.
                        }else{
                            d.value = current_ev.trace_ext().registers(i).value();
                        }

                        d.datatype = REGISTER;
                        current_event_data.defs.push_back(d);
                        break;
                    }
                }
            }

            //add the mem use and defs recorded before
            for(Data d : current_mem_uses){
                current_event_data.uses.push_back(d);
            }
            for(Data d : current_mem_defs){
                current_event_data.defs.push_back(d);
            }
            current_mem_uses.clear();
            current_mem_defs.clear();

            m_trace_data_list.push_back(current_event_data);

        }else{

            if(is_ip_between){
                continue;
            }

            Data d;
            d.address = current_ev.memaddr();
            d.datatype = MEMORY;
            d.value = current_ev.trace_ext().data();

            if(current_ev.accesstype() == Trace_Event_AccessType_READ){
                current_mem_uses.push_back(d);

            }else{
                current_mem_defs.push_back(d);
            }
        }
        if(is_last_event){
            break;
        }

        is_event_valid = stream.next(next_ev);
        if(!is_event_valid){
            is_last_event = true;
        }
    }

    LOG << "Crawled " << instr << " dynamic instructions" << std::endl;

    return true;
}


bool DataFlowPruner::disassemble(){

    m_elf = new ElfReader(cmd[ELF_FILE].first()->arg);
    if (!m_elf) {
        LOG << "Please give an ELF binary as parameter (-e/--elf)." << std::endl;
        return false;
    }

    // retrieve register IDs for general-purpose and flags register(s) for
    // the configured architecture
    fail::Architecture arch;
    //m_ip_register_id = (*arch.getRegisterSetOfType(RT_IP)->begin())->getId();
    fail::UniformRegisterSet *regset;
    regset = arch.getRegisterSetOfType(RT_GP);

    for (fail::UniformRegisterSet::iterator it = regset->begin();
         it != regset->end(); ++it) {
        m_register_ids.insert((*it)->getId());
    }

    if (cmd[FLAGS]){
        regset = arch.getRegisterSetOfType(RT_ST);
        for (fail::UniformRegisterSet::iterator it = regset->begin();
             it != regset->end(); ++it) {
            m_register_ids.insert((*it)->getId());
        }
    }

    m_disas.reset(new CapstoneDisassembler(m_elf));
    LOG << "Start to dissamble" << std::endl;
    m_disas->disassemble();

    LOG << "Get instruction map" << std::endl;
    m_instr_map = m_disas->getInstrMap();

    LOG << "Instructions disassembled: " << std::dec << m_instr_map.size() << std::endl;
    m_ctof = m_disas->getTranslator();
    m_is_disassembled = true;

    return true;
}


bool DataFlowPruner::build_data_flow_graph(){

    std::set<DFNode*> past_data;
    unsigned long counter = 0;

    for(TraceEventData& ted : m_trace_data_list){
        Instruction instr;
        instr.instr             = ted.dynamic_instr;
        instr.instr_absolute    = ted.static_instr;
        instr.time              = ted.dynamic_time;
        instr.is_cond           = false;
        instr.disassemble       = m_disas_string_map.at(ted.static_instr);

        DFNode* instr_node = m_graph.add_node(instr);

        for(Data& use : ted.uses){

            std::set<DFNode*>::iterator found_past_data_node = std::find_if(
                past_data.begin(),
                past_data.end(),
                [&use](DFNode* d){
                    return d->data.address == use.address;
            });

            if(found_past_data_node != past_data.end()){
                //known defs
                if((*found_past_data_node)->out_links.size() == 0){
                    m_graph.add_link(*found_past_data_node, instr_node);

                }else{
                    Instruction epsilon(true);
                    epsilon.instr = ted.dynamic_instr;
                    epsilon.time = ted.dynamic_time;
                    DFNode* epsilon_node = m_graph.add_node(epsilon);

                    Data data_copy = (*found_past_data_node)->data;
                    DFNode* data_copy_node = m_graph.add_node(data_copy);

                    m_graph.add_link(*found_past_data_node, epsilon_node);
                    m_graph.add_link(epsilon_node, data_copy_node);
                    m_graph.add_link(data_copy_node, instr_node);

                    past_data.erase(found_past_data_node);
                    past_data.insert(data_copy_node);
                }
            }else{
                //unknown, new defs and constants
                DFNode* use_node = m_graph.add_node(use);
                m_graph.add_link(use_node, instr_node);
                //create a "def" initially in case of read before write
                past_data.insert(use_node);
            }
        }

        for(Data& def : ted.defs){

            DFNode* def_node = m_graph.add_node(def);
            def_node->data.birth_time = instr.instr;

            m_graph.add_link(instr_node, def_node);

            // check if a current instruction's use is a known def from the past
            // if yes, put it in m_graph;
            // ignore otherwise
            std::set<DFNode*>::iterator found_past_data_node = std::find_if(
                past_data.begin(),
                past_data.end(),
                [&def_node](DFNode* d){
                    return d->data.address == def_node->data.address;
            });

            //replace defs in past_data with the current ones
            if(found_past_data_node != past_data.end()){
                //instr which causes the death of a value
                (*found_past_data_node)->data.death_time = instr.instr;

                //propagate the death time through all data nodes
                //in the current epsilon chain
                DFNode* eps_chain_node = *found_past_data_node;
                while(true){
                    //data nodes of the epsilon chain have one in_link only
                    if(eps_chain_node->in_links.size() > 0){
                        if(eps_chain_node->in_links.at(0)->from->instr.masking_rule == EPSILON){
                            //get the next data node of the epsilon chain
                            eps_chain_node = eps_chain_node->in_links.at(0)->from->in_links.at(0)->from;

                            if(eps_chain_node->out_links.at(0)->to->instr.masking_rule == EPSILON){
                                eps_chain_node->data.death_time = eps_chain_node->out_links.at(0)->to->instr.instr;

                            }else{
                                eps_chain_node->data.death_time = eps_chain_node->out_links.at(1)->to->instr.instr;
                            }

                        }else{
                            break;
                        }

                    }else{
                        break;
                    }
                }

                past_data.erase(found_past_data_node);
            }

            past_data.insert(def_node);
        }

        if(!process_disassemble_string(instr_node)){
            return false;
        }

        if(++counter % 1000 == 0){
            LOG << std::dec << counter << " instructions imported." << endl;
        }
    }

    LOG << "imported " << counter << " instructions" << endl;
    return true;
}


bool DataFlowPruner::process_disassemble_string(DataFlowGraph::DFNode* instr_node){

    if(!instr_node->is_instr){
        LOG << "Given node in string disassembling is not an instruction. Abort." << endl;
        return false;
    }

    Instruction& instr = instr_node->instr;

    //determine instruction type like add, or, xor etc
    //set an identifier for further processing
    std::smatch op_match;
    if(std::regex_search(instr.disassemble, op_match, std::regex("^([a-z]+)"))){
        std::string substring = op_match[1];
        instr.masking_rule = determine_operation(substring);
    }

    //add constants (or absolute addresses) as uses to instr
    if(!instr.disassemble.empty()){
        //extract constant values from the disassemble string
        std::regex pure_constant;
        pure_constant = "\\$0x([0-9a-f]+),";

        std::smatch const_match;

        if(std::regex_search(instr.disassemble, const_match, pure_constant)){
            std::string substring = const_match[1];

            Data constant;
            constant.address = std::numeric_limits<address_t>::max();
            constant.value = std::stoul(substring, nullptr, 16);
            constant.datatype = CONSTANT;

            DFNode* constant_node = m_graph.add_node(constant);
            m_graph.add_link(constant_node, instr_node);
        }

        //extract offset from memory addressing
        std::regex pure_offset;
        pure_offset = "(-?)0x([0-9a-f]+)\\(.*\\)";

        std::smatch offset_match;

        if(std::regex_search(instr.disassemble, offset_match, pure_offset)){

            instr.memory_access_offset = std::stoi(offset_match[2], nullptr, 16);

            //check if offset is negative
            if(!std::string(offset_match[1]).empty()){
                instr.memory_access_offset = -instr.memory_access_offset;
            }
        }

        //set flag for "is_pointer" in Data struct uses,
        //if data's address plus memory offset equals address of other one
        std::regex effective_address;
        effective_address = "\\(\\s?%[\\w\\s]+,\\s?%[\\w\\s]+,(\\d+)\\)";

        std::smatch effective_address_match;

        if(std::regex_search(instr.disassemble, effective_address_match, effective_address)){

            for(DFLink* use_link : instr_node->in_links){
                Data& use = use_link->from->data;

                if(use.datatype != REGISTER){
                    continue;
                }

                for(DFLink* use_link_iter : instr_node->in_links){
                    Data& use_iter = use_link_iter->from->data;

                    if(use.address == use_iter.address &&
                            use_iter.datatype != REGISTER){
                        continue;
                    }

                    for(DFLink* use_link_iter2 : instr_node->in_links){
                        Data& use_iter2 = use_link_iter2->from->data;

                        if(use.address == use_iter2.address ||
                           use_iter.address == use_iter2.address){
                            continue;
                        }

                        if(use.value + use_iter.value * std::stoi(effective_address_match[1]) + instr.memory_access_offset == use_iter2.address &&
                                use_iter2.datatype == MEMORY){
                            use_link->as_pointer = true;
                            use_link_iter->as_pointer = true;
                        }
                    }

                    for(DFLink* def_link_iter : instr_node->out_links){
                        Data& def_iter = def_link_iter->to->data;

                        if(use.value + use_iter.value * std::stoi(effective_address_match[1]) + instr.memory_access_offset == def_iter.address &&
                                def_iter.datatype == MEMORY){
                            use_link->as_pointer = true;
                            use_link_iter->as_pointer = true;
                        }
                    }
                }
            }
        }

        //set flag for "is_pointer" in Data struct uses,
        //if data's address plus memory offset equals address of other one
        //
        //instructions including mem ref like (%XX)
        for(DFLink* use_link : instr_node->in_links){
            Data& use = use_link->from->data;

            if(use.datatype != REGISTER){
                continue;
            }

            for(DFLink* use_link_iter : instr_node->in_links){
                Data& use_iter = use_link_iter->from->data;

                if(use.address == use_iter.address){
                    continue;
                }

                if(use.value + instr.memory_access_offset == use_iter.address &&
                        use_iter.datatype == MEMORY){
                    use_link->as_pointer = true;
                }
            }

            for(DFLink* def_link_iter : instr_node->out_links){
                Data& def_iter = def_link_iter->to->data;

                if(use.value + instr.memory_access_offset == def_iter.address &&
                        def_iter.datatype == MEMORY){
                    use_link->as_pointer = true;
                }
            }
        }

    }else{
        return false;
    }

    return true;
}


bool DataFlowPruner::do_local_mask_rules(){
    LOG << "starting local rules" << endl;
    unsigned long counter = 0;

    if(cmd[NO_LOCAL_RULES]){
        //set symbols for every single instruction
        for(DataFlowGraph::DFNode* instr_node : m_graph.nodes_instr){
            if(instr_node->instr.masking_rule == EPSILON){
                continue;
            }
            for(DFLink* in_link : instr_node->in_links){
                for(int i = 0; i < 32; i++){
                    in_link->local_mask.at(i) = m_graph.get_new_symbol();
                }
            }

            //inject every single bit
            for(DFLink* out_link : instr_node->out_links){
                for(int i = 0; i < 32; i++){
                    out_link->local_mask.at(i) = m_graph.get_new_symbol();
                }
            }

            instr_node->set_initial_global_symbols();

            if(++counter % 1000 == 0){
                LOG << std::dec << counter << " local rules done." << endl;
            }
        }

    }else{
        //set symbols for every single instruction
        for(DataFlowGraph::DFNode* instr_node : m_graph.nodes_instr){

            //checking def datatypes
            DFLink* out_link = nullptr;
            DFLink* flags_out_link = nullptr;
            if(instr_node->instr.masking_rule == EPSILON){
                out_link = instr_node->out_links.at(0); //whether flags register or not, EPSILON needs the out_links variable

            }else{
                //for(DFLink* l : instr_node->out_links){
                for(int i = 0; i < instr_node->out_links.size(); i++){
                    DFLink* l = instr_node->out_links.at(i);
                    if(l->to->data.address != FLAGS_REGISTER_ADDRESS){
                        out_link = l;

                    }else{
                        flags_out_link = l;
                    }
                }
            }
            //checking use datatypes
            DFLink* data1_in_link = nullptr;
            DFLink* data2_in_link = nullptr;
            DFLink* const_in_link = nullptr;
            DFLink* ptr1_in_link = nullptr;
            //ptr2 is for instructions with effective address calculation
            //like: MOV (%eax, %edx, 4), %eax
            DFLink* ptr2_in_link = nullptr;
            for(int i = 0; i < instr_node->in_links.size(); i++){
                DFLink* in_link = instr_node->in_links.at(i);
            //for(DFLink* in_link : instr_node->in_links){
                if(in_link->as_pointer){
                    if(!ptr1_in_link){
                        ptr1_in_link = in_link;
                    }else{
                        ptr2_in_link = in_link;
                    }
                }else{
                    if(in_link->from->data.datatype == CONSTANT){
                        const_in_link = in_link;
                    }else{ //"real" data in reg or mem
                        if(!data1_in_link){
                            data1_in_link = in_link;
                        }else{
                            data2_in_link = in_link;
                        }
                    }
                }
            }

            if(ptr1_in_link){
                do_pointer_mask_rule(ptr1_in_link, instr_node->instr.memory_access_offset);
            }

            if(ptr2_in_link){
                do_pointer_mask_rule(ptr2_in_link, instr_node->instr.memory_access_offset);
            }


            //ignore other access types than 32 bit
            std::regex ignore_regex;
            ignore_regex = "%al|%bl|%cl|%dl|%spl|%bpl|%sil|%dil|%ah|%bh|%ch|%dh|%ax|%bx|%cx|%dx|%sp|%bp|%si|%di";

            std::smatch ignore_regex_match;

            if(std::regex_search(instr_node->instr.disassemble, ignore_regex_match, ignore_regex)){

                if(instr_node->instr.masking_rule != OTHER){
                    LOG << instr_node->instr.disassemble << endl;
                    LOG << "Ignoring local mask rules for instruction " << std::dec << instr_node->instr.instr << " with absolute address 0x" << std::hex << instr_node->instr.instr_absolute << ". Inappropriate accesstype: " << ignore_regex_match[0] << ". Inject all bits." << endl;
                }
                do_inject_all_mask_rule(instr_node);

            }else{
                //arbitrarily expandable
                //(do not forget function determine_operation
                // and enum OPERATION in header)
                switch(instr_node->instr.masking_rule){
                    case EPSILON: {
                        //EPSILON is a virtual instruction for the data-flow graph
                        //it will be handled like a MOV from and to the same register

                        //local rule
                        if(data1_in_link && !data2_in_link && !const_in_link){
                            for(int i = 0; i < 32; i++){
                                data1_in_link->local_mask.at(i) = m_graph.get_new_symbol();
                                out_link->local_mask.at(i) = m_graph.get_current_symbol();
                            }
                        }

                        break;
                    }
                    //============================================
                    case MOV: {
                        //all MOV variants have one def only (via out_link)
                        //except uses like cr0 (not considered yet, gp-registers only)
                        if(instr_node->out_links.size() != 1 || !out_link){
                            LOG << "Instruction mask rule MOV at instruction " << std::dec << instr_node->instr.instr << " with absolute address 0x" << std::hex << instr_node->instr.instr_absolute << " failed: Inappropriate defs. Inject all bits." << endl;

                            do_inject_all_mask_rule(instr_node);
                            break;
                        }

                        //local rule
                        if(data1_in_link && !data2_in_link && !const_in_link){
                            for(int i = 0; i < 32; i++){
                                data1_in_link->local_mask.at(i) = m_graph.get_new_symbol();
                                out_link->local_mask.at(i) = m_graph.get_current_symbol();
                            }

                        }else if(const_in_link && !data1_in_link && !data2_in_link){
                            for(int i = 0; i < 32; i++){
                                out_link->local_mask.at(i) = m_graph.get_new_symbol();
                            }

                        }else{
                            LOG << "Instruction mask rule MOV at instruction " << std::dec << instr_node->instr.instr << " with absolute address 0x" << std::hex << instr_node->instr.instr_absolute << " failed: Inappropriate uses. Inject all bits." << endl;

                            do_inject_all_mask_rule(instr_node);
                        }

                        break;
                    }
                    //============================================
                    case XOR: {
                        if(instr_node->out_links.size() != 2 || !out_link || !flags_out_link){
                            LOG << "Instruction mask rule XOR at instruction " << std::dec << instr_node->instr.instr << " with absolute address 0x" << std::hex << instr_node->instr.instr_absolute << " failed: Inappropriate defs. Inject all bits." << endl;

                            do_inject_all_mask_rule(instr_node);
                            break;
                        }

                        //local rule
                        //data1_in_link only means instructions like
                        //xor %eax, %eax
                        if(data1_in_link && !data2_in_link && !const_in_link){
                            //for(int i = 0; i < 32; i++){
                                //data1_in_link->local_mask.at(i) = m_graph.get_new_symbol();
                                //out_link->local_mask.at(i) = m_graph.get_current_symbol();
                            //}

                            //local equivalences bitwise but for propagation purposes
                            // it is necessary to separate the input and output value of the register 
                            do_inject_all_mask_rule(instr_node);

                        }else if(data1_in_link && data2_in_link && !const_in_link){
                            for(int i = 0; i < 32; i++){
                                data1_in_link->local_mask.at(i) = m_graph.get_new_symbol();
                                data2_in_link->local_mask.at(i) = m_graph.get_current_symbol();
                                out_link->local_mask.at(i) = m_graph.get_current_symbol();
                            }

                        }else if(const_in_link && data1_in_link && !data2_in_link) {
                            for(int i = 0; i < 32; i++){
                                data1_in_link->local_mask.at(i) = m_graph.get_new_symbol();
                                out_link->local_mask.at(i) = m_graph.get_current_symbol();
                            }

                        }else{
                            LOG << "Instruction mask rule XOR at instruction " << std::dec << instr_node->instr.instr << " with absolute address 0x" << std::hex << instr_node->instr.instr_absolute << " failed: Inappropriate uses. Inject all bits." << endl;

                            do_inject_all_mask_rule(instr_node);
                        }

                        for(int i = 0; i < 32; i++){
                            flags_out_link->local_mask.at(i) = m_graph.get_new_symbol();
                        }

                        break;
                    }
                    //============================================
                    case AND: {
                        if(instr_node->out_links.size() != 2 || !out_link || !flags_out_link){
                            LOG << "Instruction mask rule AND at instruction " << std::dec << instr_node->instr.instr << " with absolute address 0x" << std::hex << instr_node->instr.instr_absolute << " failed: Inappropriate defs. Inject all bits." << endl;

                            do_inject_all_mask_rule(instr_node);
                            break;
                        }

                        if(data1_in_link && data2_in_link && !const_in_link){
                            for(int i = 0; i < 32; i++){
                                //MSB bit first
                                bool data1_data_bit = (data1_in_link->from->data.value >> (31-i)) & 1U;
                                bool data2_data_bit = (data2_in_link->from->data.value >> (31-i)) & 1U;

                                symbol_t& data1_mask_bit = data1_in_link->local_mask.at(i);
                                symbol_t& data2_mask_bit = data2_in_link->local_mask.at(i);
                                symbol_t& out_mask_bit = out_link->local_mask.at(i);

                                //local rule
                                if(!data1_data_bit && !data2_data_bit){
                                    data1_mask_bit = m_graph.get_new_symbol();
                                    data2_mask_bit = m_graph.get_current_symbol();
                                    out_mask_bit = m_graph.get_new_symbol();

                                }else if(!data1_data_bit && data2_data_bit){
                                    data1_mask_bit = m_graph.get_new_symbol();
                                    out_mask_bit = m_graph.get_current_symbol();
                                    data2_mask_bit = m_graph.get_new_symbol();

                                }else if(data1_data_bit && !data2_data_bit){
                                    data1_mask_bit = m_graph.get_new_symbol();
                                    data2_mask_bit = m_graph.get_new_symbol();
                                    out_mask_bit = m_graph.get_current_symbol();

                                }else{ //data1_data_bit && data2_data_bit
                                    data1_mask_bit = m_graph.get_new_symbol();
                                    data2_mask_bit = m_graph.get_current_symbol();
                                    out_mask_bit = m_graph.get_current_symbol();
                                }
                            }

                        }else if (const_in_link && data1_in_link && !data2_in_link){
                            for(int i = 0; i < 32; i++){
                                //MSB bit first
                                bool const_data_bit = (const_in_link->from->data.value >> (31-i)) & 1U;

                                symbol_t& data1_mask_bit = data1_in_link->local_mask.at(i);
                                symbol_t& out_mask_bit = out_link->local_mask.at(i);

                                //local rule
                                if(!const_data_bit){//!data1_data_bit && !const_data_bit || data1_data_bit && !const_data_bit
                                    data1_mask_bit = m_graph.get_new_symbol();
                                    out_mask_bit = m_graph.get_new_symbol();

                                }else{ //data1_data_bit && const_data_bit || !data1_in_link && const_data_bit
                                    data1_mask_bit = m_graph.get_new_symbol();
                                    out_mask_bit = m_graph.get_current_symbol();
                                }
                            }

                        }else{
                            LOG << "Instruction mask rule AND at instruction " << std::dec << instr_node->instr.instr << " with absolute address 0x" << std::hex << instr_node->instr.instr_absolute << " failed: Inappropriate uses. Inject all bits." << endl;

                            do_inject_all_mask_rule(instr_node);
                        }

                        for(int i = 0; i < 32; i++){
                            flags_out_link->local_mask.at(i) = m_graph.get_new_symbol();
                        }

                        break;
                    }
                    //============================================
                    case OR: {
                        if(instr_node->out_links.size() != 2 || !out_link || !flags_out_link){
                            LOG << "Instruction mask rule OR at instruction " << std::dec << instr_node->instr.instr << " with absolute address 0x" << std::hex << instr_node->instr.instr_absolute << " failed: Inappropriate defs. Inject all bits." << endl;

                            do_inject_all_mask_rule(instr_node);
                            break;
                        }

                        if(data1_in_link && data2_in_link && !const_in_link){
                            for(int i = 0; i < 32; i++){
                                //MSB bit first
                                bool data1_data_bit = (data1_in_link->from->data.value >> (31-i)) & 1U;
                                bool data2_data_bit = (data2_in_link->from->data.value >> (31-i)) & 1U;

                                symbol_t& data1_mask_bit = data1_in_link->local_mask.at(i);
                                symbol_t& data2_mask_bit = data2_in_link->local_mask.at(i);
                                symbol_t& out_mask_bit = out_link->local_mask.at(i);

                                //local rule
                                if(!data1_data_bit && !data2_data_bit){
                                    data1_mask_bit = m_graph.get_new_symbol();
                                    data2_mask_bit = m_graph.get_current_symbol();
                                    out_mask_bit = m_graph.get_current_symbol();

                                }else if(!data1_data_bit && data2_data_bit){
                                    data1_mask_bit = m_graph.get_new_symbol();
                                    data2_mask_bit = m_graph.get_new_symbol();
                                    out_mask_bit = m_graph.get_current_symbol();

                                }else if(data1_data_bit && !data2_data_bit){
                                    data1_mask_bit = m_graph.get_new_symbol();
                                    out_mask_bit = m_graph.get_current_symbol();
                                    data2_mask_bit = m_graph.get_new_symbol();

                                }else{ //data1_data_bit && data2_data_bit
                                    data1_mask_bit = m_graph.get_new_symbol();
                                    data2_mask_bit = m_graph.get_current_symbol();
                                    out_mask_bit = m_graph.get_new_symbol();
                                }
                            }

                        }else if(const_in_link && data1_in_link && !data2_in_link){
                            for(int i = 0; i < 32; i++){
                                //MSB bit first
                                bool const_data_bit = (const_in_link->from->data.value >> (31-i)) & 1U;

                                symbol_t& data1_mask_bit = data1_in_link->local_mask.at(i);
                                symbol_t& out_mask_bit = out_link->local_mask.at(i);

                                //local rule
                                if(!const_data_bit){//!data1_data_bit && !const_data_bit || data1_data_bit && !const_data_bit
                                    data1_mask_bit = m_graph.get_new_symbol();
                                    out_mask_bit = m_graph.get_current_symbol();

                                }else{ //data1_data_bit && const_data_bit || !data1_in_link && const_data_bit
                                    data1_mask_bit = m_graph.get_new_symbol();
                                    out_mask_bit = m_graph.get_new_symbol();
                                }
                            }

                        }else{
                            LOG << "Instruction mask rule OR at instruction " << std::dec << instr_node->instr.instr << " with absolute address 0x" << std::hex << instr_node->instr.instr_absolute << " failed: Inappropriate uses. Inject all bits." << endl;

                            do_inject_all_mask_rule(instr_node);
                        }

                        for(int i = 0; i < 32; i++){
                            flags_out_link->local_mask.at(i) = m_graph.get_new_symbol();
                        }

                        break;
                    }
                    //============================================
                    case ADD: {
                        if(instr_node->out_links.size() != 2 || !out_link || !flags_out_link){
                            LOG << "Instruction mask rule ADD at instruction " << std::dec << instr_node->instr.instr << " with absolute address 0x" << std::hex << instr_node->instr.instr_absolute << " failed: Inappropriate defs. Inject all bits." << endl;

                            do_inject_all_mask_rule(instr_node);
                            break;
                        }

                        //local rule
                        if(data1_in_link && data2_in_link && !const_in_link){
                            for(int i = 0; i < 32; i++){
                                //MSB bit first
                                bool data1_data_bit = (data1_in_link->from->data.value >> (31-i)) & 1U;
                                bool data2_data_bit = (data2_in_link->from->data.value >> (31-i)) & 1U;
                                bool out_data_bit = (out_link->to->data.value >> (31-i)) & 1U;

                                symbol_t& data1_mask_bit = data1_in_link->local_mask.at(i);
                                symbol_t& data2_mask_bit = data2_in_link->local_mask.at(i);
                                symbol_t& out_mask_bit = out_link->local_mask.at(i);

                                //eight possible equivalence intervalls
                                //internally carries musst be considered
                                //  a and b stand for different eq intervalls
                                //  + stands for creating internal carry
                                //
                                //no carry
                                //in_bit1 a0  a0  a1  a1
                                //in_bit2 a0  b1  b0  a1
                                //out_bit a0  b1  a1  b0+
                                //
                                //+ carry
                                //in_bit1 a0  a0  a1  a1
                                //in_bit2 a0  b1  b0  a1
                                //in_bit3 b1  a0+ b0+ a1+

                                //no carry
                                if(!data1_data_bit && !data2_data_bit && !out_data_bit){
                                    data1_mask_bit = m_graph.get_new_symbol();
                                    data2_mask_bit = m_graph.get_current_symbol();
                                    out_mask_bit = m_graph.get_current_symbol();

                                }else if(!data1_data_bit && data2_data_bit && out_data_bit){
                                    data1_mask_bit = m_graph.get_new_symbol();
                                    data2_mask_bit = m_graph.get_new_symbol();
                                    out_mask_bit = m_graph.get_current_symbol();

                                }else if(data1_data_bit && !data2_data_bit && out_data_bit){
                                    data2_mask_bit = m_graph.get_new_symbol();
                                    data1_mask_bit = m_graph.get_new_symbol();
                                    out_mask_bit = m_graph.get_current_symbol();

                                }else if(data1_data_bit && data2_data_bit && !out_data_bit){
                                    data1_mask_bit = m_graph.get_new_symbol();
                                    data2_mask_bit = m_graph.get_current_symbol();
                                    out_mask_bit = m_graph.get_new_symbol();

                                //+ carry
                                }else if(!data1_data_bit && !data2_data_bit && out_data_bit){
                                    data1_mask_bit = m_graph.get_new_symbol();
                                    data2_mask_bit = m_graph.get_current_symbol();
                                    out_mask_bit = m_graph.get_new_symbol();

                                }else if(!data1_data_bit && data2_data_bit && !out_data_bit){
                                    data2_mask_bit = m_graph.get_new_symbol();
                                    data1_mask_bit = m_graph.get_new_symbol();
                                    out_mask_bit = m_graph.get_current_symbol();

                                }else if(data1_data_bit && !data2_data_bit && !out_data_bit){
                                    data1_mask_bit = m_graph.get_new_symbol();
                                    data2_mask_bit = m_graph.get_new_symbol();
                                    out_mask_bit = m_graph.get_current_symbol();

                                }else { //data1_data_bit && data2_data_bit && out_data_bit){
                                    data1_mask_bit = m_graph.get_new_symbol();
                                    data2_mask_bit = m_graph.get_current_symbol();
                                    out_mask_bit = m_graph.get_current_symbol();
                                }
                            }

                        }else if(const_in_link && data1_in_link && !data2_in_link) {
                            for(int i = 0; i < 32; i++){
                                //MSB bit first
                                bool const_data_bit = (const_in_link->from->data.value >> (31-i)) & 1U;
                                bool data1_data_bit = (data1_in_link->from->data.value >> (31-i)) & 1U;
                                bool out_data_bit = (out_link->to->data.value >> (31-i)) & 1U;

                                symbol_t& data1_mask_bit = data1_in_link->local_mask.at(i);
                                symbol_t& out_mask_bit = out_link->local_mask.at(i);

                                //same rules for adds with const
                                //no carry
                                //con_bit a0  a0  a1  a1
                                //in_bit  a0  b1  b0  a1
                                //out_bit a0  b1  a1  b0+
                                //
                                //+ carry
                                //con_bit a0  a0  a1  a1
                                //in_bit  a0  b1  b0  a1
                                //out_bit b1  a0+ b0+ a1+

                                //no carry
                                if(!const_data_bit && !data1_data_bit && !out_data_bit){
                                    data1_mask_bit = m_graph.get_new_symbol();
                                    out_mask_bit = m_graph.get_current_symbol();

                                }else if(!const_data_bit && data1_data_bit && out_data_bit){
                                    data1_mask_bit = m_graph.get_new_symbol();
                                    out_mask_bit = m_graph.get_current_symbol();

                                }else if(const_data_bit && !data1_data_bit && out_data_bit){
                                    data1_mask_bit = m_graph.get_new_symbol();
                                    out_mask_bit = m_graph.get_new_symbol();

                                }else if(const_data_bit && data1_data_bit && !out_data_bit){
                                    data1_mask_bit = m_graph.get_new_symbol();
                                    out_mask_bit = m_graph.get_new_symbol();

                                //+ carry
                                }else if(!const_data_bit && !data1_data_bit && out_data_bit){
                                    data1_mask_bit = m_graph.get_new_symbol();
                                    out_mask_bit = m_graph.get_new_symbol();

                                }else if(!const_data_bit && data1_data_bit && !out_data_bit){
                                    data1_mask_bit = m_graph.get_new_symbol();
                                    out_mask_bit = m_graph.get_new_symbol();

                                }else if(const_data_bit && !data1_data_bit && !out_data_bit){
                                    data1_mask_bit = m_graph.get_new_symbol();
                                    out_mask_bit = m_graph.get_current_symbol();

                                }else{// const_data_bit && data1_data_bit && out_data_bit
                                    data1_mask_bit = m_graph.get_new_symbol();
                                    out_mask_bit = m_graph.get_current_symbol();
                                }
                            }

                        }else{
                            LOG << "Instruction mask rule ADD at instruction " << std::dec << instr_node->instr.instr << " with absolute address 0x" << std::hex << instr_node->instr.instr_absolute << " failed: Inappropriate uses. Inject all bits." << endl;

                            do_inject_all_mask_rule(instr_node);
                        }

                        for(int i = 0; i < 32; i++){
                            flags_out_link->local_mask.at(i) = m_graph.get_new_symbol();
                        }
                        break;
                    }
                    //============================================

                    //OTHER
                    default: {
                        //inject every single bit
                        do_inject_all_mask_rule(instr_node);
                    }
                }
            }

            //set global symbols initially -> inject all
            instr_node->set_initial_global_symbols();

            if(++counter % 10000 == 0){
                LOG << std::dec << counter << " local rules done." << endl;
            }
        }
    }

    return true;
}


bool DataFlowPruner::do_inject_all_mask_rule(DataFlowGraph::DFNode* instr_node){

    for(DFLink* l : instr_node->in_links){
        if(l->from->data.datatype != CONSTANT){
            for(int i = 0; i < 32; i++){
                l->local_mask.at(i) = m_graph.get_new_symbol();
            }
        }
    }

    for(DFLink* l : instr_node->out_links){
        for(int i = 0; i < 32; i++){
            l->local_mask.at(i) = m_graph.get_new_symbol();
        }
    }

    return true;
}


bool DataFlowPruner::do_pointer_mask_rule(DFLink* link_to_ptr, int memory_access_offset){

    //the most simple rule: inject all
    for(int i = 0; i < 32; i++){
        link_to_ptr->local_mask.at(i) = m_graph.get_new_symbol();
    }

    return true;
}


bool DataFlowPruner::do_global_mask_rules(){
    LOG << "starting global rules" << endl;
    unsigned long counter = 0;

    std::queue<DFNode*> q;
    std::unordered_set<DFNode*> q_set; //for uniqueness of the queues nodes

    //init: insert nodes without successor into the queue
    for(DFNode* instr_node : m_graph.nodes_instr){
        if(instr_node->out_links.size() == 0){
            q.push(instr_node);
            q_set.insert(instr_node);
        }
    }

    std::map<address_t, DFNode*> newest_data_nodes;
    for(DFNode* data_node : m_graph.nodes_data){
        //is this the last write instruction?
        if(data_node->out_links.size() == 0){
            //then injection is not necessary due to ineffective fault space
            for(symbol_t& sym : data_node->in_links[0]->global_mask){
                sym = 0;
            }

            //determine the newest (max birth_time) data node due to each address
            auto data_node_found = newest_data_nodes.find(data_node->data.address);
            if(data_node_found == newest_data_nodes.end()){
                newest_data_nodes.insert(std::make_pair(data_node->data.address, data_node));

            }else{
                if(data_node_found->second->data.birth_time < data_node->data.birth_time){
                    newest_data_nodes.erase(data_node_found);
                    newest_data_nodes.insert(std::make_pair(data_node->data.address, data_node));
                }
            }

            q.push(data_node);
            q_set.insert(data_node);
        }
    }

    //recovering symbols for newest data nodes
    for(auto& node_pair : newest_data_nodes){
        node_pair.second->set_initial_global_symbols();
    }

    //loop: while (data or instruction) nodes in queue,
    //      set global masks for every incoming and outcoming
    //      link of every node
    while(!q.empty()){

        DFNode* node = q.front();
        q.pop();
        q_set.erase(node);

        //node is already done, nothing to do
        if(node->visited){
            continue;
        }

        //if no predecessor nodes, nothing to do
        if(node->in_links.size() == 0){
            node->visited = true;
            continue;
        }

        //queue all predecessor nodes
        for(DFLink* in_link : node->in_links){
            if(!in_link->from->visited){
                if(q_set.find(in_link->from) == q_set.end()){
                    q.push(in_link->from);
                    q_set.insert(in_link->from);
                }
            }
        }

        //if no successors, nothing to do
        //(but predecessors for further processing queued)
        if(node->out_links.size() == 0){
            node->visited = true;
            continue;
        }

        //successors must be done before
        bool successors_done = true;
        for(DFLink* out_link : node->out_links){
            if(!out_link->to->visited){
                successors_done = false;

                if(q_set.find(node) == q_set.end()){
                    q.push(node);
                    q_set.insert(node);
                }

                break;
            }
        }

        if(successors_done){
            if(node->is_instr){
                //if(node->instr.masking_rule == EPSILON){
                    //for(int i = 0; i < 32; i++){
                        //node->in_links[0]->global_mask.at(i) = node->out_links[0]->global_mask.at(i);
                    //}

                //}else{
                    std::map<symbol_t, symbol_t> symbol_map;
                    //mapping def symbols to all use symbols
                    for(DFLink* out_link : node->out_links){
                        for(int i = 0; i < 32; i++){
                            symbol_t& out_symbol_local = out_link->local_mask.at(i);
                            symbol_t& out_symbol_global = out_link->global_mask.at(i);

                            for(DFLink* in_link : node->in_links){
                                for(int j = 0; j < 32; j++){
                                    if(in_link->local_mask.at(j) == out_symbol_local){
                                        //need only one element in the map, because in1->out (inserted one) and in2->out
                                        //means in1=out and in2=out as well as in1=in2=out
                                        if(symbol_map.find(in_link->global_mask.at(j)) == symbol_map.end()
                                                && in_link->global_mask.at(j) != out_symbol_global){
                                            symbol_map.insert(std::make_pair(in_link->global_mask.at(j), out_symbol_global));
                                        }
                                    }
                                }
                            }
                        }
                    }

                    //map symbols in uses
                    for(DFLink* in_link : node->in_links){
                        if(in_link->from->out_links.size() == 1){

                            DFNode* value_node;
                            for(DFLink* l : node->out_links){
                                if(l->to->data.address != FLAGS_REGISTER_ADDRESS){
                                    value_node = l->to;
                                }
                            }

                            //forked value (in value_node) does not live alone
                            if(in_link->from->data.death_time > value_node->data.death_time
                                    || in_link->from->data.death_time == 0){
                                break;
                            }

                            for(symbol_t& sym : in_link->global_mask){
                                if(symbol_map.find(sym) != symbol_map.end()){
                                    sym = symbol_map.at(sym);
                                }
                            }

                        }else{ //in_link->from->out_links.size() == 2
                            DFLink* neighbor_link;
                            for(DFLink* l : in_link->from->out_links){
                                if(l != in_link){
                                    neighbor_link = l;
                                    break;
                                }
                            }

                            for(int i = 0; i < 32; i++){
                                symbol_t& sym = in_link->global_mask.at(i);

                                if(neighbor_link->global_mask.at(i) == 0){
                                    if(symbol_map.find(sym) != symbol_map.end()){
                                        sym = symbol_map.at(sym);
                                    }
                                }
                            }
                        }
                    }
                //}

            }else{ //data node
                switch(node->out_links.size()){
                    //case 0: {
                        //for(int i = 0; i < 32; i++){
                            //node->in_links[0]->global_mask.at(i) = 0;
                        //}
                        //LOG << "0 out_links!" << endl;
                        //break;
                    //}

                    case 1: {
                        for(int i = 0; i < 32; i++){
                            node->in_links[0]->global_mask.at(i) = node->out_links[0]->global_mask.at(i);
                        }
                        break;
                    }

                    case 2: {
                        for(int i = 0; i < 32; i++){
                            symbol_t& in_symbol = node->in_links[0]->global_mask.at(i);
                            symbol_t& out_symbol_1 = node->out_links[0]->global_mask.at(i);
                            symbol_t& out_symbol_2 = node->out_links[1]->global_mask.at(i);

                            if(out_symbol_1 == out_symbol_2){
                                in_symbol = out_symbol_1;

                            }else if(out_symbol_1 == 0){
                                in_symbol = out_symbol_2;

                            }else if(out_symbol_2 == 0){
                                in_symbol = out_symbol_1;
                            }
                        }
                        break;
                    }

                    default: {
                        LOG << "Invalid number (>2) of outgoing links. Is something wrong in the graph construction? Abort." << endl;
                        return false;
                    }

                }
            }

            if(++counter % 1000 == 0){
                LOG << std::dec << counter << " global rules done. (q size = " << q.size() << ")" << endl;
            }

            node->visited = true;
        }//successors_done
    }//while !q.empty()

    return true;
}


bool DataFlowPruner::create_tables(){
    std::string create_statement =
        "CREATE TABLE IF NOT EXISTS fsppilot_dataflow ("
        "	variant_id int(11) NOT NULL,"
        "	symbol int(10) unsigned NOT NULL,"
        "	instr2 int(10) unsigned NOT NULL," //dynamic_instr_t
        "	data_address int(10) unsigned NOT NULL,"
        "	bitoffset int(1) unsigned NOT NULL,"
        "	PRIMARY KEY (variant_id, symbol, instr2, data_address, bitoffset)"
        "	)engine=MyISAM";

    if(!(bool)db->query(create_statement.c_str())){
        LOG << "Creating table failed. Abort." << endl;
        return false;
    }

    create_statement =
        "CREATE TABLE IF NOT EXISTS fspgroup_dataflow ("
        "	variant_id int(11) NOT NULL,"
        "	symbol int(10) unsigned NOT NULL,"
        "	instr2 int(10) unsigned NOT NULL," //dynamic_instr_t
        "	data_address int(10) unsigned NOT NULL,"
        "	bitoffset int(1) unsigned NOT NULL,"
        "	original_value int(10) unsigned NOT NULL,"
        "	PRIMARY KEY (variant_id, instr2, data_address, bitoffset)"
        "	)engine=MyISAM";

    if(!(bool)db->query(create_statement.c_str())){
        LOG << "Creating table failed. Abort." << endl;
        return false;
    }

    LOG << "Tables fsppilot_dataflow and fspgroup_dataflow created." << endl;
    return true;
}


bool DataFlowPruner::export_injections(variant_t& variant){

    std::stringstream insert_groups_statement_stream;
    insert_groups_statement_stream
        << "INSERT INTO fspgroup_dataflow "
        << "(variant_id,symbol,instr2,data_address,bitoffset,original_value) "
        << "VALUES ";

    unsigned long insert_count = 0;

    for(DFNode* n : m_graph.nodes_instr){
        if(n->instr.masking_rule != EPSILON){
            for(DFLink* in_link : n->in_links){
                if(in_link->from->data.datatype == CONSTANT){
                    continue;
                }

                for(int i = 0; i < 32; i++){
                    if(++insert_count % 1000 == 0){
                        LOG << std::dec << insert_count << " fspgroup_dataflow rows inserted. " << endl;

                        std::string insert_statement_string = insert_groups_statement_stream.str();
                        insert_statement_string.pop_back();
                        insert_statement_string.push_back(';');

                        if(!(bool)db->query(insert_statement_string.c_str())){
                            LOG << "Inserting dataflow group data to data base failed. Abort." << endl;
                            return false;
                        }

                        insert_groups_statement_stream.str("");
                        insert_groups_statement_stream.clear();
                        insert_groups_statement_stream
                            << "INSERT INTO fspgroup_dataflow "
                            << "(variant_id,symbol,instr2,data_address,bitoffset,original_value) "
                            << "VALUES ";
                    }

                    insert_groups_statement_stream << "("
                        << variant.id << ","
                        << in_link->global_mask.at(i) << ","
                        << n->instr.instr << ","
                        << in_link->from->data.address + (in_link->global_mask.size() - 1)/8 - i/8 << "," //data_address little-endian byte order
                        << 7 - i%8 << ","
                        << in_link->from->data.value << "),";
                }
            }
        }
    }

    std::string insert_statement_string = insert_groups_statement_stream.str();
    if(insert_statement_string.back() == ','){ //means at least one data tuple exists
        insert_statement_string.pop_back();
        insert_statement_string.push_back(';');

        if(!(bool)db->query(insert_statement_string.c_str())){
            LOG << "Inserting dataflow group data to data base failed. Abort." << endl;
            return false;
        }
    }


    std::stringstream insert_pilots_statement_stream;
    insert_pilots_statement_stream
        << "INSERT INTO fsppilot_dataflow "
        << "(variant_id,symbol,instr2,data_address,bitoffset) "
        << "SELECT variant_id,symbol,instr2,data_address,bitoffset "
        << "FROM fspgroup_dataflow "
        << "WHERE variant_id=" << variant.id << " "
        << "GROUP BY symbol;";

    if(!(bool)db->query(insert_pilots_statement_stream.str().c_str())){
        LOG << "Inserting dataflow pilot data to data base failed. Abort." << endl;
        return false;
    }

    return true;
}


void DataFlowPruner::create_dot_file(const std::string& var_str){

    if(cmd[DOT] && cmd[DOT_FULL]){
        LOG << "Parameters --dot " << std::stoul(cmd[DOT].first()->arg) << " and --dot-full detected. Executing --dot " << std::stoul(cmd[DOT].first()->arg) << " only." << endl;
    }

    std::string filename = "dataflowgraph-" + var_str + ".dot";
    std::replace(filename.begin(), filename.end(), '/', '-');
    std::ofstream file(filename, std::ofstream::out | std::ofstream::trunc);
    std::stringstream node_stream;
    std::stringstream link_stream;
    std::set<unsigned long> known_nodes;
    unsigned long from, to;

    unsigned int link_dot_start = 0;
    if(cmd[DOT_START_AT]){
        link_dot_start = std::stoul(cmd[DOT_START_AT].first()->arg);
    }

    unsigned int link_dot_counter = m_graph.links.size();
    if(cmd[DOT]){
        link_dot_counter = std::stoul(cmd[DOT].first()->arg);
    }

    unsigned int number_of_printed_links;
    if (link_dot_start + link_dot_counter >= m_graph.links.size()){
        number_of_printed_links = m_graph.links.size() - link_dot_start;

    }else{
        number_of_printed_links = link_dot_counter;
    }

    LOG << "creating DOT file with " << std::dec << number_of_printed_links << " of " << m_graph.links.size() << " possible links" << endl;

    if(cmd[DOT_MASKS]){
        LOG << "adding masks to DOT file." << endl;
    }

    for(unsigned int i = link_dot_start;
            i < m_graph.links.size() && i < link_dot_start + link_dot_counter;
            i++){
        DFLink* link = m_graph.links.at(i);

        from = (unsigned long) link->from;
        to = (unsigned long) link->to;

        if(known_nodes.find(from) == known_nodes.end()){
            known_nodes.insert(from);

            if(link->from->is_instr){
                if(link->from->instr.masking_rule == EPSILON){
                    node_stream
                        << from
                        << " [shape=circle "
                        << "label=\""
                        << "t: " << std::dec << link->from->instr.instr << "\\n"
                        << "eps" << "\""
                        << "];" << endl;
                }else{
                    node_stream
                        << from
                        << " [shape=circle "
                        << "label=\""
                        << "INSTR " << link->from->instr.instr << "\\n"
                        << link->from->instr.disassemble << "\\n"
                        << "memory offset: 0x" << std::hex << link->from->instr.memory_access_offset << "\\n"
                        << "masking rule: " << std::dec << link->from->instr.masking_rule << "\\n"
                        << "instr_abs: 0x" << std::hex << link->from->instr.instr_absolute << "\\n"
                        << "simtime: " << std::dec << link->from->instr.time << "\\n"
                        << "is_cond: " << link->from->instr.is_cond << "\""
                        << "];" << endl;
                }
            }else{
                if(link->from->data.datatype == CONSTANT){
                    node_stream
                        << from
                        << " [shape=box "
                        << "label=\""
                        << "CONSTANT" << "\\n"
                        << "value: 0x" << std::hex << link->from->data.value << "\\n"
                        << std::dec << "\"];" << endl;
                }else{
                    if(link->from->data.datatype == MEMORY){
                        node_stream
                            << from
                            << " [shape=box "
                            << "label=\""
                            << "MEMORY" << "\\n"
                            << "address: 0x" << std::hex << link->from->data.address << "\\n"
                            << "birth_t: " << std::dec << link->from->data.birth_time << "\\n"
                            << "death_t: " << std::dec << link->from->data.death_time << "\\n"
                            << "value: 0x" << std::hex << link->from->data.value << "\\n"
                            << std::dec << "\"];" << endl;
                    }else{
                        node_stream
                            << from
                            << " [shape=box "
                            << "label=\""
                            << "REGISTER" << "\\n"
                            << "address: 0x" << std::hex << link->from->data.address << "\\n"
                            << "birth_t: " << std::dec << link->from->data.birth_time << "\\n"
                            << "death_t: " << std::dec << link->from->data.death_time << "\\n"
                            << "value: 0x" << std::hex << link->from->data.value << "\\n"
                            << std::dec << "\"];" << endl;
                    }
                }
            }
        }

        if(known_nodes.find(to) == known_nodes.end()){
            known_nodes.insert(to);

            if(link->to->is_instr){
                if(link->to->instr.masking_rule == EPSILON){
                    node_stream
                        << to
                        << " [shape=circle "
                        << "label=\""
                        << "t: " << std::dec << link->to->instr.instr << "\\n"
                        << "eps" << "\""
                        << "];" << endl;
                }else{
                    node_stream
                        << to
                        << " [shape=circle "
                        << "label=\""
                        << "INSTR " << link->to->instr.instr << "\\n"
                        << link->to->instr.disassemble << "\\n"
                        << "memory offset: 0x" << std::hex << link->to->instr.memory_access_offset << "\\n"
                        << "masking rule: " << std::dec << link->to->instr.masking_rule << "\\n"
                        << "instr_abs: 0x" << std::hex << link->to->instr.instr_absolute << "\\n"
                        << "simtime: " << std::dec << link->to->instr.time << "\\n"
                        << "is_cond: " << link->to->instr.is_cond << "\""
                        << "];" << endl;
                }
            }else{
                if(link->to->data.datatype == MEMORY){
                    node_stream
                        << to
                        << " [shape=box "
                        << "label=\""
                        << "MEMORY" << "\\n"
                        << "address: 0x" << std::hex << link->to->data.address << "\\n"
                        << "birth_t: " << std::dec << link->to->data.birth_time << "\\n"
                        << "death_t: " << std::dec << link->to->data.death_time << "\\n"
                        << "value: 0x" << std::hex << link->to->data.value << "\\n"
                        << std::dec << "\"];" << endl;
                }else{
                    node_stream
                        << to
                        << " [shape=box "
                        << "label=\""
                        << "REGISTER" << "\\n"
                        << "address: 0x" << std::hex << link->to->data.address << "\\n"
                        << "birth_t: " << std::dec << link->to->data.birth_time << "\\n"
                        << "death_t: " << std::dec << link->to->data.death_time << "\\n"
                        << "value: 0x" << std::hex << link->to->data.value << "\\n"
                        << std::dec << "\"];" << endl;
                }
            }
        }

        if(cmd[DOT_MASKS]){
            if(!link->from->is_instr){
                //no injection to constants
                //ignore output of this link
                if(link->from->data.datatype == CONSTANT){
                    link_stream << from << " -> " << to << ";" << endl;
                    continue;
                }
            }else{
                if(link->from->instr.masking_rule == EPSILON){
                    //link_stream << from << " -> " << to << ";" << endl;
                    link_stream << from << " -> " << to << " [label=\"as_ptr=" << link->as_pointer << "\ndyn_instr: " << link->instr << "\nl: " << link->print_local_mask() << "\ng: " << link->print_mask() << "\"];" << endl;
                    continue;
                }
            }

            if(link->to->is_instr){
                //if(link->to->instr.masking_rule == EPSILON){
                    //link_stream << from << " -> " << to << ";" << endl;

                //}else{
                    link_stream << from << " -> " << to << " [label=\"as_ptr=" << link->as_pointer << "\ndyn_instr: " << link->instr << "\nl: " << link->print_local_mask() << "\ng: " << link->print_mask() << "\"];" << endl;
                //}
            }else{
                link_stream << from << " -> " << to << " [label=\"instr: " << link->instr << "\nl: " << link->print_local_mask() << "\ng: " << link->print_mask() << "\"];" << endl;
            }

        }else{
            link_stream << from << " -> " << to << endl;
        }
    }

    file << "digraph dataflow { " << endl
         << "{" << endl
         << node_stream.str()
         << "}" << endl
         << link_stream.str()
         << "}" << endl;

    file.close();
}

void DataFlowPruner::print_stats(){
    symbol_t bits = 0;
    symbol_t max_l = 2, min_l = std::numeric_limits<symbol_t>::max();
    symbol_t max_g = 2, min_g = std::numeric_limits<symbol_t>::max();
    std::unordered_set<symbol_t> symbol_set_l;
    std::unordered_set<symbol_t> symbol_set_g;
    std::unordered_set<symbol_t> symbol_set_g_register;
    std::unordered_set<symbol_t> symbol_set_g_memory;
    unsigned int number_of_data_accesses = 0;
    unsigned int number_of_consts = 0;
    unsigned int number_of_reg_reads = 0;
    unsigned int number_of_reg_writes = 0;
    unsigned int number_of_reg_both = 0;
    unsigned int number_of_mem_reads = 0;
    unsigned int number_of_mem_writes = 0;
    unsigned int number_of_mem_both = 0;
    unsigned int number_of_instr = 0;

    for(DFLink* l : m_graph.links){
        if(l->local_mask.at(0) > 2){
            bits += 32;
        }
    }

    for(DFNode* i : m_graph.nodes_instr){
        if(i->instr.masking_rule != EPSILON){
            number_of_instr++;
        }
    }

    for(DFLink* l : m_graph.links){
        for(symbol_t s : l->local_mask){
            if(s != 0 && s != 1){
                if(symbol_set_l.find(s) == symbol_set_l.end()){
                    symbol_set_l.insert(s);
                }
                if(s > max_l) max_l = s;
                if(s < min_l) min_l = s;
            }
        }

        if(l->to->is_instr){
            if(l->to->instr.masking_rule == EPSILON){
                continue;
            }

            if(l->from->data.datatype == REGISTER){
                number_of_reg_reads++;
                for(DFLink* ll : l->to->out_links){// l-> to = instr
                    if(l->from->data.address == ll->to->data.address){
                        //read and write at the same address during one instruction
                        number_of_reg_both++;
                    }
                }
            }

            else if(l->from->data.datatype == MEMORY){
                number_of_mem_reads++;

                for(DFLink* ll : l->to->out_links){// l-> to = instr
                    if(l->from->data.address == ll->to->data.address){
                        //read and write at the same address during one instruction
                        number_of_mem_both++;
                    }
                }
            }

            else if(l->from->data.datatype == CONSTANT){
                number_of_consts++;
            }

        }else if(l->from->is_instr){
            if(l->from->instr.masking_rule == EPSILON){
                continue;
            }

            if(l->to->data.datatype == REGISTER){
                number_of_reg_writes++;
            }

            else if(l->to->data.datatype == MEMORY){
                number_of_mem_writes++;
            }
        }

        number_of_data_accesses++;
    }

    for(DFNode* d : m_graph.nodes_data){
        //read equivalence sets only
        //ignore constants
        //ignore data nodes without outgoing links
        //-> will be never read
        if(d->data.datatype == CONSTANT
            || d->out_links.size () == 0){
            continue;
        }

        for(DFLink* l : d->out_links){
            for(symbol_t s : l->global_mask){
                if(s != 0 && s != 1){
                    if(symbol_set_g.find(s) == symbol_set_g.end()){
                        symbol_set_g.insert(s);
                    }

                    if(d->data.address >= FIRST_MEMORY_ADDRESS
                            && symbol_set_g_memory.find(s) == symbol_set_g_memory.end()){
                        symbol_set_g_memory.insert(s);
                    }

                    //sanity check
                    if(d->data.address < FIRST_MEMORY_ADDRESS
                            && symbol_set_g_register.find(s) == symbol_set_g_register.end()){
                        symbol_set_g_register.insert(s);
                    }

                    if(s > max_g) max_g = s;
                    if(s < min_g) min_g = s;
                }
            }
        }
    }

    float local_symbols = symbol_set_l.size();
    float global_symbols = symbol_set_g.size();
    float global_symbols_register = symbol_set_g_register.size();
    float global_symbols_memory = symbol_set_g_memory.size();

    LOG << " === STATS ===" << endl;
    LOG << "number of instruction nodes: " << m_graph.nodes_instr.size() << endl;
    LOG << "number of data nodes: " << m_graph.nodes_data.size() << endl;
    LOG << "number of links: " << m_graph.links.size() << endl;
    LOG << " ---" << endl;
    LOG << "number of instructions: " << number_of_instr << endl;
    LOG << "number of #bits in masks: " << bits << endl;
    LOG << " ---" << endl;
    LOG << "number of data accesses: " << number_of_data_accesses << endl;
    LOG << "-> constants used: " << number_of_consts << endl;
    LOG << "-> register reads: " << number_of_reg_reads << endl;
    LOG << "-> register writes: " << number_of_reg_writes << endl;
    LOG << "-> register r/w in same instr: " << number_of_reg_both << endl;
    LOG << "-> memory reads: " << number_of_mem_reads << endl;
    LOG << "-> memory writes: " << number_of_mem_writes << endl;
    LOG << "-> memory r/w in same instr: " << number_of_mem_both << endl;
    LOG << " ---" << endl;
    if(cmd[NO_LOCAL_RULES]){
        LOG << "number of local symbols: " << local_symbols << " (" << (local_symbols/bits) * 100 << "\% of #bits) | --no-local-semantics" << endl;
    }else{
        LOG << "number of local symbols: " << local_symbols << " (" << (local_symbols/bits) * 100 << "\% of #bits)" << endl;
    }
    LOG << "lowest local symbol: " << min_l << endl;
    LOG << "highest local symbol: " << max_l << endl;
    LOG << " ---" << endl;
    LOG << "number of global symbols overall: " << global_symbols << " (" << (global_symbols/local_symbols) * 100 << "\% of local symbols; " << (global_symbols/bits) * 100 << "\% of #bits)" << endl;
    LOG << "-> in register: " << global_symbols_register << " (" << (global_symbols_register/local_symbols) * 100 << "\% of local symbols; " << (global_symbols_register/bits) * 100 << "\% of #bits)" << endl;
    LOG << "-> in memory: " << global_symbols_memory << " (" << (global_symbols_memory/local_symbols) * 100 << "\% of local symbols; " << (global_symbols_memory/bits) * 100 << "\% of #bits)" << endl;
    LOG << "lowest global symbol: " << min_g << endl;
    LOG << "highest global symbol: " << max_g << endl << endl;
}
