create or replace  view fsppilot_decode as
SELECT p.variant_id, p.id as pilot_id, instr2, data_address, disassemble
FROM fsppilot p
JOIN objdump ON
  objdump.variant_id = p.variant_id
  and p.injection_instr_absolute = objdump.instr_address;

################################################################
# View for Def-Use Pruning
#view1 res -> fsppilot -> fspgroup -> trace
create or replace  view def_use_res as
select 	
		v.id as variant_id,
                v.variant,
                v.benchmark,
                # Adress one bit-height EC interval
		t.instr2, 
		t.data_address, 
		r.bitoffset as bitoffset,
                (t.instr2 - t.instr1 + 1) as weight,
                # Debug information
                t.instr2_absolute,
                # What was the pilot that produced the result
		g.pilot_id as pilot_id,
                # The result
		r.resulttype 
from trace t
join variant v
    on t.variant_id = v.id
join fspmethod fspm
    on fspm.`method` = "basic"
straight_join fspgroup g
    on  t.variant_id = g.variant_id
    and g.fspmethod_id = fspm.id
    and t.instr2 = g.instr2 
    and t.data_address = g.data_address
straight_join fsppilot p
    on  t.variant_id = p.variant_id
    and g.fspmethod_id = p.fspmethod_id
    and g.pilot_id = p.id 
left outer join result_GenericExperimentMessage r
    on r.pilot_id = p.id
where t.instr2_absolute is not NULL 
  and t.accesstype = 'R'
  and (t.data_address < 0x114 or t.data_address > 0x117)
;


################################################################
# View for Data-Flow Pruning
create or replace view data_flow_res as
select 	
		t.variant_id,
                v.variant,
                v.benchmark,
		gd.instr2, 
		gd.data_address, 
		gd.bitoffset,
                # Debug information
                gd.symbol,
                t.instr2_absolute,              
                # gd.symbol as symbol,
		(t.instr2 - t.instr1 + 1) as weight,
                p.id as pilot_id,
                p.injection_instr as pilot_instr,
                p.injection_instr_absolute as pilot_instr_absolute,
                r.resulttype
from trace t
join variant v
    on t.variant_id = v.id
join fspmethod fspm
    on fspm.`method` = "basic"
straight_join fspgroup_dataflow gd
	on  gd.instr2       = t.instr2 
	and gd.data_address = t.data_address 
	and gd.variant_id   = t.variant_id
straight_join fsppilot_dataflow pd 
     on  pd.variant_id      = t.variant_id
     and pd.symbol          = gd.symbol
# Find def-use pilot for data-flow pilot
left outer join fsppilot p
    on  p.fspmethod_id = fspm.id
    and p.variant_id   = t.variant_id
    and p.instr2       = pd.instr2
    and p.data_address = pd.data_address
left outer join result_GenericExperimentMessage r
    on  r.pilot_id  = p.id
    AND r.bitoffset = pd.bitoffset
where t.instr2_absolute is not NULL 
  and t.accesstype = 'R'
  and (t.data_address < 0x114 or t.data_address > 0x117)
;


\! echo "calculating results"
\! echo "... def use"

CREATE OR REPLACE TABLE  def_use_statistic AS
SELECT variant_id, variant, benchmark, resulttype,
       count(distinct pilot_id, bitoffset) as injections,
       sum(weight) as sum_weight
FROM     def_use_res
GROUP BY variant_id, resulttype;

\! echo "... data flow"

CREATE OR REPLACE TABLE  data_flow_statistic AS
SELECT variant_id, variant, benchmark, resulttype,
       count(distinct pilot_id, bitoffset) as injections,
       sum(weight) as sum_weight
FROM data_flow_res
GROUP BY variant_id, resulttype;


\! echo "overall reductions (paper table 2)"
select du.variant,
       sum(df.injections) / sum(du.injections) - 1 as reduction,
       du.sum_weight - df.sum_weight as sum_weight_difference
from data_flow_statistic df
JOIN def_use_statistic du
   ON df.variant_id = du.variant_id AND du.resulttype = df.resulttype
GROUP BY du.variant_id
;

\! echo "statistics about reductions and weights split in result types (paper table 2+3)"
select dus.variant, dus.resulttype,
       (sum(dfs.injections) / sum(dus.injections) - 1) *100 as reduction,
       sum(dus.injections) as inj_du, sum(dus.sum_weight) as sum_w_du,
       sum(dfs.injections) as inj_df, sum(dfs.sum_weight) as sum_w_df,
       sum(dus.sum_weight) - sum(dfs.sum_weight) as diff
from data_flow_statistic dfs
JOIN def_use_statistic dus
     ON dfs.variant_id = dus.variant_id AND dus.resulttype = dfs.resulttype
group by dus.variant_id, dus.resulttype
;

################################################################
# Statistic about equivalence sets
\! echo "statistics about equivalence sets (paper table 2)"
create or replace table df_ec
select df.variant_id, df.variant,
     avg(df.sum_weight) avg_weight,
     # avg(df.locations) as avg_locations,
     sum(df.locations > 1)/count(df.locations) as locations,
     sum(df.ecs > 1)/count(df.ecs) as ecs
from (
       SELECT variant_id, variant, pilot_id, bitoffset,
              sum(weight) as sum_weight,
              count(distinct data_address, bitoffset) as locations,
              count(distinct instr2, data_address, bitoffset) as ecs
       FROM data_flow_res
       #WHERE variant_id = 8
       GROUP BY pilot_id, bitoffset
) as df
group by variant_id
;

create or replace table du_ec
select du.variant_id, du.variant,
     sum(du.sum_weight) as sum_weight,
     avg(du.sum_weight) as avg_weight,
     # avg(du.locations) as avg_locations,
     sum(du.locations > 1)/count(du.locations) as locations,
     sum(du.ecs > 1)/count(du.ecs) as ecs
FROM (
      SELECT variant_id, variant, pilot_id, bitoffset,
            sum(weight) as sum_weight,
            count(distinct data_address, bitoffset) as locations,
            count(distinct instr2, data_address, bitoffset) as ecs
       FROM def_use_res
       #WHERE variant_id = 8
       GROUP BY pilot_id, bitoffset
) as du
group by variant_id;


CREATE OR REPLACE TABLE  ec_statistic AS
SELECT df_ec.variant_id, df_ec.variant,
    du_ec.sum_weight as sum_weight,
    du_ec.avg_weight as du_avg_weight,
    df_ec.avg_weight as df_avg_weight,
    df_ec.locations as df_multi_locations,
    df_ec.ecs as df_multi_nodes
from df_ec
join du_ec on df_ec.variant_id = du_ec.variant_id;
select * from ec_statistic;




CREATE OR REPLACE TABLE  mult_ecs AS
select df.variant_id, df.variant, avg(df.ecs) as avg_mult_ecs
FROM (
      SELECT variant_id, variant, pilot_id, bitoffset,
            sum(weight) as sum_weight,
            count(distinct instr2, data_address, bitoffset) as ecs
       FROM data_flow_res
       GROUP BY pilot_id, bitoffset
) as df
where df.ecs > 1
group by variant_id
;


################################################################
# Trace Statistics
\! echo "instruction statistics of the golden run (paper figure 6)"
CREATE OR REPLACE TABLE instr_statistic AS
select v.variant, mnemonic, count(*) as `count` from
(
  select t.variant_id, instr2, substring_index(o.disassemble, " ", 1) as mnemonic
  FROM trace t
  JOIN objdump o ON o.variant_id = t.variant_id and o.instr_address = t.instr2_absolute
  GROUP BY t.variant_id, instr2
) as T
JOIN variant v ON v.id = T.variant_id
group by variant_id, mnemonic
order by variant_id, count(*)
;
select * from instr_statistic;
