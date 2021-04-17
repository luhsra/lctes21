#ifndef __DATA_FLOW_PRUNER_H__
#define __DATA_FLOW_PRUNER_H__

#include "Pruner.hpp"
#include "comm/TracePlugin.pb.h"
#include "util/capstonedisassembler/CapstoneDisassembler.hpp"
#include "util/CommandLine.hpp"
#include "util/ElfReader.hpp"
#include "util/gzstream/gzstream.h"
#include "util/Logger.hpp"
#include "util/ProtoStream.hpp"
#include <queue>
#include <unordered_set>

class DataFlowPruner : public Pruner{
public:
    using variant_t = fail::Database::Variant;
    using simtime_t = fail::simtime_t;
    using address_t = fail::address_t;

    using dynamic_instr_t   = uint32_t;
    using value_t           = uint64_t;
    using symbol_t          = uint64_t;

    using static_instr_t  = unsigned long;
    using instr_width_t  = unsigned char;

    // hard coded address for first memory address and flags register
    const address_t FIRST_MEMORY_ADDRESS = 4096;
    const address_t FLAGS_REGISTER_ADDRESS = 0x110;

    //EPSILON is a dummy instruction rule which initiates
    //  a new equivalence set due to reading data at least twice
    //OTHER stands for injecting every single bit
    //  in use data and def data
    //arbitrarily expandable
    enum OPERATION {OTHER, EPSILON, MOV, ADD, SUB, AND, OR, XOR};

    //arbitrarily expandable
    OPERATION determine_operation(std::string& op_string){
        if(op_string.compare("mov") == 0)   return MOV;
        if(op_string.compare("movl") == 0)  return MOV;
        if(op_string.compare("add") == 0)   return ADD;
        if(op_string.compare("sub") == 0)   return SUB;
        if(op_string.compare("and") == 0)   return AND;
        if(op_string.compare("or") == 0)    return OR;
        if(op_string.compare("xor") == 0)   return XOR;

        return OTHER;
    }

    enum DATATYPE {CONSTANT, REGISTER, MEMORY};

    struct Data{
        address_t address;
        value_t value;
        DATATYPE datatype;
        //birth_time: value is written and ready to be used
        dynamic_instr_t birth_time;
        //death_time: independent of the data location
        // value is overwritten and gone forever
        // heartfelt condolences :(
        dynamic_instr_t death_time;

        Data() :
            birth_time(0),
            death_time(0)
        {}

        Data& operator=(const Data& rhs){
            address = rhs.address;
            value = rhs.value;
            datatype = rhs.datatype;
            return *this;
        }
    };

    struct Instruction{
        dynamic_instr_t instr;
        address_t instr_absolute;
        simtime_t time;
        bool is_cond;
        OPERATION masking_rule;
        std::string disassemble;
        int memory_access_offset = 0;

        Instruction(bool is_epsilon = false) :
            instr(0),
            instr_absolute(0),
            time(0),
            is_cond(false),
            masking_rule(is_epsilon ? EPSILON : OTHER),
            disassemble(""),
            memory_access_offset(0)
        {}
    };

    struct TraceEventData{
        dynamic_instr_t dynamic_instr;
        static_instr_t  static_instr;
        simtime_t dynamic_time;
        //opcode
        //bool is_cond;
        std::vector<Data> uses;
        std::vector<Data> defs;
    };

    struct DataFlowGraph{
        struct DFLink;
        struct DFNode{
            Instruction instr;
            Data data;
            DataFlowGraph& graph;
            bool is_instr;
            bool visited = false;
            std::vector<DFLink*> in_links;   //linked to uses
            std::vector<DFLink*> out_links;  //linked to defs

            DFNode(Instruction instr, DataFlowGraph& graph) :
                instr(std::move(instr)),
                graph(graph),
                is_instr(true)
            {
                    graph.nodes_instr.push_back(this);
            }

            DFNode(Data data, DataFlowGraph& graph) :
                data(std::move(data)),
                graph(graph),
                is_instr(false)
            {
                    graph.nodes_data.push_back(this);
            }

            void set_initial_global_symbols(){
                for(DFLink* l : in_links)
                    for(int i = 0; i < 32; i++)
                        l->global_mask.at(i) = graph.get_new_symbol();

                for(DFLink* l : out_links)
                    for(int i = 0; i < 32; i++)
                        l->global_mask.at(i) = graph.get_new_symbol();
            }
        };

        struct DFLink{

            // 0 = injection is not necessary
            //     and/or sign for eps nodes
            //     that this bit will not be used
            // 1 = placeholder
            // 2 = placeholder
            // >=3 are symbols
            std::array<symbol_t, 32> local_mask;
            std::array<symbol_t, 32> global_mask;

            DFNode* from;
            DFNode* to;
            dynamic_instr_t instr;
            bool as_pointer = false;

            DFLink(DFNode* f, DFNode* t) :
                from(f),
                to(t)
            {
                if(from->is_instr){
                    if(from->instr.masking_rule == EPSILON){
                        //ignore dummy instruction
                        for(symbol_t& m : local_mask) m = 0;
                        for(symbol_t& m : global_mask) m = 0;

                    }else{
                        //inject all
                        for(symbol_t& m : local_mask) m = 1;
                        for(symbol_t& m : global_mask) m = 1;
                    }

                    //instruction time
                    instr = from->instr.instr;

                }else{
                    if(from->data.datatype == CONSTANT
                            || to->instr.masking_rule == EPSILON){
                        //no injections to constants
                        for(symbol_t& m : local_mask) m = 0;
                        for(symbol_t& m : global_mask) m = 0;

                    }else{
                        //inject all
                        for(symbol_t& m : local_mask) m = 1;
                        for(symbol_t& m : global_mask) m = 1;
                    }

                    //instruction time
                    instr = to->instr.instr;
                }

                from->out_links.push_back(this);
                to->in_links.push_back(this);

                from->graph.links.push_back(this);
            }

            std::string print_local_mask(){
                std::string mask_string;
                for(symbol_t& bit : local_mask){
                    mask_string += std::to_string(bit) + " ";
                }
                return mask_string;
            }

            std::string print_mask(){
                std::string mask_string;
                for(symbol_t& bit : global_mask){
                    mask_string += std::to_string(bit) + " ";
                }
                return mask_string;
            }
        };

        std::list<DFNode*> nodes_instr;
        std::list<DFNode*> nodes_data;
        std::vector<DFLink*> links;

        symbol_t symbols_iter = 2;

        ~DataFlowGraph(){
            for(auto& node : nodes_instr) delete node;
            for(auto& node : nodes_data)  delete node;
            for(auto& link : links)       delete link;
        }

        //defines a new error equivalence class
        symbol_t get_new_symbol(){
            return ++symbols_iter;
        }

        //"assign" to current error equivalence class
        symbol_t get_current_symbol(){
            return symbols_iter;
        }

        DFNode* add_node(Instruction instr){
            return new DFNode(instr, *this);
        }

        DFNode* add_node(Data data){
            return new DFNode(data, *this);
        }

        DFLink* add_link(DFNode* from, DFNode* to){
            return new DFLink(from, to);
        }
    };

    DataFlowPruner() :
        LOG("DataFlowPruner"),
        m_is_disassembled(false)
    {}
    virtual ~DataFlowPruner() {}

    virtual std::string method_name() { return std::string("data-flow"); }
    virtual bool commandline_init();
    virtual bool prune_all();
    void getAliases(std::deque<std::string> *aliases) {
        aliases->push_back("DataFlowPruner");
        aliases->push_back("data-flow");
    }

    std::pair<std::string, std::string> queue_to_str(std::queue<DataFlowGraph::DFNode*> q, std::unordered_set<DataFlowGraph::DFNode*> q_set){
        std::string q_str = "", q_set_str = "";

        while(!q.empty()){
            if(q.front()->is_instr){
                q_str += "INSTR " + std::to_string(q.front()->instr.instr) + " | ";
            }else{
                q_str += "DATA " + std::to_string(q.front()->data.address) + " | ";
            }
            q.pop();
        }

        for(DataFlowGraph::DFNode* n : q_set){
            if(n->is_instr){
                q_set_str += "INSTR " + std::to_string(n->instr.instr) + " | ";
            }else{
                q_set_str += "DATA " + std::to_string(n->data.address) + " | ";
            }
        }

        return std::make_pair(q_str, q_set_str);
    }

protected:
    fail::Logger LOG;
    fail::CommandLine &cmd = fail::CommandLine::Inst();
    fail::CommandLine::option_handle ELF_FILE;
    fail::CommandLine::option_handle FLAGS;
    fail::CommandLine::option_handle NO_LOCAL_RULES;
    fail::CommandLine::option_handle PRINT_TRACE;
    fail::CommandLine::option_handle DOT;
    fail::CommandLine::option_handle DOT_START_AT;
    fail::CommandLine::option_handle DOT_FULL;
    fail::CommandLine::option_handle DOT_MASKS;
    fail::CommandLine::option_handle STATS;

    bool m_is_disassembled;
    fail::ElfReader *m_elf = 0;
    fail::CapstoneToFailTranslator *m_ctof = 0;
    std::unique_ptr<fail::CapstoneDisassembler> m_disas;
    // Data structures for recording failed Capstone -> FAIL* register mappings,
    // including occurrence counts in the trace (to give an estimate on the
    // impact) and instruction addresses (for debugging purposes).
    struct RegNotFound {
        uint64_t count = 0;
        std::set<fail::guest_address_t> address;
    };

    std::map<fail::CapstoneDisassembler::register_t, RegNotFound> m_regnotfound;
    std::map<address_t, std::string> m_disas_string_map;
    fail::CapstoneDisassembler::InstrMap m_instr_map;
    std::map<static_instr_t, instr_width_t> m_instruction_width_map;
    std::set<unsigned> m_register_ids;
    std::list<TraceEventData> m_trace_data_list;
    DataFlowGraph m_graph;

    bool disassemble();
    bool import_objdump(const variant_t& var);
    bool import_trace();
    bool build_data_flow_graph();
    bool process_disassemble_string(DataFlowGraph::DFNode* instr_node);
    bool do_local_mask_rules();
    bool do_pointer_mask_rule(DataFlowGraph::DFLink* link_to_ptr, int memory_access_offset);
    bool do_inject_all_mask_rule(DataFlowGraph::DFNode* instr_node);
    bool do_global_mask_rules();
    bool create_tables();
    bool export_injections(variant_t& variant);

    void create_dot_file(const std::string& var_str);
    void print_stats();
};

#endif
