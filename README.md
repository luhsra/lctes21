# LCTES '21 - Data-Flow–Sensitive Fault-Space Pruning for the Injection of Transient Hardware Faults

Autors: Oskar Pusz and Christian Dietrich and Daniel Lohmann

Submission #28

We provide the data-flow pruner (DFP) presented in our paper.
First, we would like to describe the concrete evaluation scenario shortly.
We use the fault-injection tool FAIL* (https://github.com/danceos/fail) and have extended it with our pruner.
To evaluate DFP we ran FAIL* with a generic experiment after pruning the fault space with the well-known def-use pruner which is already implemented in FAIL*.
After the execution of the campaign, FAIL* created a database with all relevant information about the programs under investigation as well as the results of the fault-injection campaign.
The databases are the baseline of our evaluation and can be found in the database-dump/ directory.


# Description

### benchmarks/
Contains all benchmark data for the evaluation of the DFP: ELF (the benchmark) + trace.pb (golden trace file).

### database-dumps/
You find two database dumps of the databases after running FAIL*'s fault-injection campaigns with def-use pruning (that is the baseline data).
The data is split into a database with _micro_ fault-injection campaign data and a database with _mibench_ data.
Executing the pruning or SQL scripts extend the data of the current database.
If needed, the reset\_*\_database.sh scripts reset and creates the current database.

### evaluation-queries/
You find two SQL scripts here: _analysis.sql_ produce the data used in the paper. _validate.sql_ does the validation of the DFP.

### failstar/
That is the fault-injection tool FAIL* directory.
Install all relevant libs and tools as in doc/how-to-build.txt described.
We extended FAIL* by the DFP (tools/prune-trace/DataFlowPruner.\*) and some configurations (for instance configurations/x86_pruning_capstone.sh) to make the building process more compact.
The directory build-prebuild consist an already compiled version of FAIL*.
The binary which includes the DFP is prune-trace (failstar/build-prebuild/bin/prune-trace).

### pruning-scripts/
The scripts in this directory execute the pruning with the DFP, one for the micro data and one for the MiBench data.


# Step-by-Step Instructions

We describe the building process of FAIL* and the execution of the DFP as well as the reproducing of the evaluation data.


## Building FAIL*

Go to failstar directory and create a new directory for the build process and cd into it
```
    cd ~/failstar
    mkdir build
    cd build
```
Configure to build the "generic-tracing" experiment using the capstone disassembler
```
   ../configurations/x86_pruning_capstone.sh generic-tracing
```
Compile it with make
```
    make
```
Done! The binary needed for data-flow--sensitive pruning is build/bin/prune-trace



## Micro Benchmarks

Make sure the database _micro_ is imported to mysql and used.

Execute the script pruning-scripts/dataflow_pruning_micro.sh
   At the end of the step, you will find dataflow tables in the _micro_ database.
```
   ./pruning-scripts/dataflow_pruning_micro.sh
```
   The path to the binary in the script refer to the prebuild prune-trace and can be changed if needed.
   Feel free to change it to your freshly build prune-trace binary if you want.
   (Hint: If you execute the pruner more then one time you will get sql errors because the data already exists.
    You can reset the database, as already mentioned, to do the pruning step again.)

Execute the analysis query evaluation-queries/analysis.sql
   At the end of the step, you will find the data of the paper on the terminal.
```
   mysql -t < evaluation-queries/analysis.sql | less
```   
   (-t for pretty tables; piping the output into less could be more readable)

   This script produce several new tables/views for further evaluation and to improve the query speed.

Execute the validation query evaluation-queries/validate.sh
   At the end of the step, you should get empty tables and text output only.
```
   mysql -t < evaluation-queries/validate.sql
```
   This query checks if DFP produced a result for every single def-use equivalence set (ES)
   and if the resulttypes of the ESs differ.
   No table output means no differences due to the results.
   So, the DFP works correctly and the validation was positive.


## MiBench Benchmarks

Basicly, follow the same steps like for the _micro_ benchmarks but import and use the database _mibench_.
