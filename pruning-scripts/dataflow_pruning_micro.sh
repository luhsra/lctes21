#!/bin/bash
PRUNER=/home/ae/failstar/build-prebuild/bin/prune-trace

BENCHMARKS=(
    micro/fib
    micro/loopsum
    micro/mixed
    micro/qsort
    micro/qsort_iter
)

for b in "${BENCHMARKS[@]}"
do
    BENCHMARK_NAME=$b
    BENCHMARK_PATH=/home/ae/benchmarks/$b

    $PRUNER -p DataFlowPruner -v $BENCHMARK_NAME -b mix -t $BENCHMARK_PATH/trace.pb -e $BENCHMARK_PATH/system.elf --flags
done
