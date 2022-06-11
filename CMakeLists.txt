#PREAMBLE
cmake_minimum_required(VERSION 3.20)
project(geocold VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CURRENT_SOURCE_DIR ON)
# use c++20 compulsory
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# to set up necessities on the side and also to detect cuda.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#include(ConfigSafeGuards)

include(CTest)

#for compile time warnings
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


function (CHECK_EXTERNAL NAME DIR)
  if (NOT IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/external/${DIR}")
    message (FATAL_ERROR "The ${NAME} submodule directory is missing! "
      "Either that submodule was recently added to pbrt or you did not clone the project with --recursive. "
      "In order to update the submodules, run:\n"
      "  \"git submodule update --init --recursive\"")
  endif ()
endfunction ()

CHECK_EXTERNAL ("glad" "glad/include")
CHECK_EXTERNAL ("glfw" "glfw/docs")
CHECK_EXTERNAL ("glm" "glm/glm")
CHECK_EXTERNAL ("imgui" "imgui/examples")
CHECK_EXTERNAL ("glad" "glad/include")

enable_testing()

find_package(Sanitizers)
find_package(Threads)
find_package(OpenGL REQUIRED)





find_package(OpenGL REQUIRED)
#find_package(benchmark REQUIRED)

target_include_directories(geocold INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})


include_directories(include)
add_subdirectory(external/glfw)
add_subdirectory(external/glad)
add_subdirectory(external/glm)
# add_subdirectory(external/benchmark)
add_subdirectory(external/googletest)
add_subdirectory(include)

add_subdirectory(bench)
add_subdirectory(unittests)
add_subdirectory(main)




