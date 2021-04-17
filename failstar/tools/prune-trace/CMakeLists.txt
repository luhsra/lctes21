set(SRCS
  Pruner.cc
  BasicPruner.cc
  FESamplingPruner.cc
  SamplingPruner.cc
  BasicBlockPruner.cc
  CallRegionPruner.cc
  DataFlowPruner.cc
)

find_package(MySQL REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MYSQL_CFLAGS}")

## This is the example's campaign server distributing experiment parameters
add_executable(prune-trace main.cc ${SRCS})

## For DataFlowPruner
#if (BUILD_LLVM_DISASSEMBLER)
#  include(FindLLVM)
#  target_link_libraries(prune-trace
#    fail-llvmdisassembler
#    fail-sal
#    ${LLVM_LIBS}
#    ${LLVM_LDFLAGS}
#    ${Boost_LIBRARIES}
#  )
#endif (BUILD_LLVM_DISASSEMBLER)

target_link_libraries(prune-trace ${MYSQL_LIBRARIES} fail-util)

install(TARGETS prune-trace RUNTIME DESTINATION bin)
