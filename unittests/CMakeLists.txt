
enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/master.zip 
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

list (APPEND L_UNITTESTS
	testsarray
	)

include(GoogleTest)

foreach(unittest IN LISTS L_UNITTESTS)
	add_executable(${unittest} ${unittest}.cpp)
	target_link_libraries(${unittest} PUBLIC StaticArray SortingAlgorithms ${llvm_libs} gtest_main)#${PROJECT_NAME} gtest_main)
	gtest_discover_tests(${unittest})
endforeach()


#add_executable(testsarray testsarray.cpp)
#target_link_libraries(testsarray gtest_main)
#gtest_discover_tests(testsarray)
