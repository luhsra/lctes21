\! echo "sanity check: every data-flow injection has a result";
# Sanity check: Must return no results
SELECT variant_id, count(df.pilot_id is null), count(df.resulttype is null) FROM data_flow_res df
   where variant_id = @variant_id
     and (df.pilot_id is NULL or df.resulttype is null)
   group by variant_id;
\! echo "... DONE"


\! echo "sanity check: equivalence sets where the two pruning methods differ"
select du.variant, df.instr2,
   df.data_address, df.bitoffset as bit,
   du.pilot_id as du_pilot,
   df.pilot_id as df_pilot,
   du.resulttype as du_resulttype,
   df.resulttype as df_resulttype
from def_use_res du
JOIN data_flow_res df ON
  df.variant_id       = du.variant_id
  and df.data_address = du.data_address
  and df.instr2       = du.instr2
  and df.bitoffset    = du.bitoffset
where
  df.resulttype != du.resulttype
;
\! echo "... DONE"
