find_package(Threads)
enable_testing()

# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/refs/heads/master.zip 
# )
# For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)

list (APPEND L_UNITTESTS
	firsttest	
	)

# include(GoogleTest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

foreach(unittest IN LISTS L_UNITTESTS)
	add_executable(${unittest} ${unittest}.cpp)
	target_link_libraries(${unittest} PUBLIC gtest gtest_main geocold pthread)#${PROJECT_NAME} gtest_main)
endforeach()


#add_executable(testsarray testsarray.cpp)
#target_link_libraries(testsarray gtest_main)
#gtest_discover_tests(testsarray)
