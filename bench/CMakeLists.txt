
  
find_package(Threads REQUIRED)
#include(${CMAKE_SOURCE_DIR}/cmake/GoogleBenchmarks.cmake)

list (APPEND L_BENCH
	benchsarray
	)

foreach (my_bench IN LISTS L_BENCH)
	add_executable(${my_bench} ${my_bench}.cpp)
	target_link_libraries(${my_bench} benchmark::benchmark benchmark::benchmark_main)
	target_link_libraries(${my_bench} ${llvm_libs} StaticArray SortingAlgorithms)
	add_test(Bench_${my_bench} ${my_bench})
endforeach()
