#PREAMBLE
cmake_minimum_required(VERSION 3.13)
# minimum version
#set(projectName DSA)
#make it necessary to use c++17
project(geocold VERSION 0.0.1 LANGUAGES CXX)
# set up the project command with name, version and languages used.

#enable_testing()
#PREAMBLE

#Project wide setup

set(CMAKE_CXX_STANDARD 20)
# use c++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
include(ConfigSafeGuards)

include(CTest)


set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Enable benchmark self-testing?")

# Fix dependency download
# https://github.com/google/benchmark/issues/564
#
set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON CACHE BOOL "Download dependencies?")

if( MSVC ) 
	add_compile_options(/W4 /w14640 /w14242 /w14254 
	/w14265 /w14263 /w14287 /we4289 /w14296 /w14311 /w14545 /w14546 /w14547 /w14549 
	/w14555 /w14619 /w14640 /w14826 /w14905 /w14906 /w14928 )
else() 
	add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast 
											-Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion 
											-Wsign-conversion -Wdouble-promotion -Wformat=2)
	# add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic 
	#-Wold-style-cast -Wunused -Wcast-align -Woverloaded-virtual -Wconversion -Wsign-conversion 
	#-Wmisleading-indentation -Wnull-dereference -Wuseless-cast)
endif()
# haven't put -Werror cause apparently it's sh**

#llvm stuff
#-----------------------x----------------------#
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})
#-----------------------x----------------------#


# add the StaticArray interface libray
#src/DSTK/StaticArray.cpp)

	# add_executable(main_executable main/main.cpp)

llvm_map_components_to_libnames(llvm_libs support core irreader)

include(ConfigGBench)
# add_subdirectory(main)
add_subdirectory(include)
add_subdirectory(bench)
add_subdirectory(unittests)
