#PREAMBLE
cmake_minimum_required(VERSION 3.20)
project(geocold VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
# use c++20 compulsory
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# to set up necessities on the side and also to detect cuda.  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#include(ConfigSafeGuards)

include(CTest) #for compile time warnings if( MSVC ) 
if(MSVC)
	add_compile_options(/W4 /w14640 /w14242 /w14254 
	/w14265 /w14263 /w14287 /we4289 /w14296 /w14311 /w14545 /w14546 /w14547 /w14549 
	/w14555 /w14619 /w14640 /w14826 /w14905 /w14906 /w14928 )
else() 
		add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast 
												-Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion 
												-Wsign-conversion -Wdouble-promotion -Wformat=2)
endif()
# haven't put -Werror cause apparently it's sh**


function (CHECK_EXTERNAL NAME DIR)
  if (NOT IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/external/${DIR}/")
    message (FATAL_ERROR "The ${NAME} submodule directory is missing! "
      "Either that submodule was recently added to pbrt or you did not clone the project with --recursive. "
      "In order to update the submodules, run:\n"
      "  \"git submodule update --init --recursive\"")
  endif ()
endfunction ()

CHECK_EXTERNAL ("glad" "glad/src")
CHECK_EXTERNAL ("glfw" "glfw/src")
CHECK_EXTERNAL ("glm" "glm/glm")
CHECK_EXTERNAL ("imgui" "imgui/backends")



# find_package(Sanitizers)
find_package(Threads)
find_package(OpenGL REQUIRED)
find_package(Vulkan REQUIRED FATAL_ERROR)
enable_testing()
enable_language(CUDA)

# include (CheckLanguage)
#
# check_language(CUDA)
#
# if (CMAKE_CUDA_COMPILER)
# 	if (CUDA_VERSION_MAJOR LESS 11)
# 		message(WARNING "geocold requires cuda version 11.0 or later but ${CUDA_VERSION_MAJOR}.${CUDA_VERSION_MINOR}\
# 		was found. GPU support is disabled.")
#
# 	else()
# 		find_package(CUDA REQUIRED)
#
# 		if (${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.20.0")
# 			set (CMAKE_CUDA_STANDARD 17)
# 		endif()
#
# 		if (NOT CUDA_VERSION_PATCH)
# 			if (CUDA_NVCC_EXECUTABLE AND
# 					CUDA_NVCC_EXECUTABLE STREQUAL CMAKE_CUDA_COMPILER AND
# 					CMAKE_CUDA_COMPILER_VERSION MATCHES [=[([0-9]+)\.([0-9]+)\.([0-9]+)]=])
# 					set (CUDA_VERSION_PATC "${CMAKE_MATCH_3}")
# 				elseif (CUDA_NVCC_EXECUTABLE) 
# 					execute_process (COMMAND ${CUDA_NVCC_EXECUTABLE} "--version" OUTPUT_VARIABLE NOUT)
# 					if (NOUT MATCHES  [=[ V([0-9]+)\.([0-9]+)\.([0-9]+)]=])
# 						set (CUDA_VERSION_PATCH "${CMAKE_MATCH_3}")
# 					endif()
# 			endif()
# 		endif()
#
# endif()

find_package(CUDA) 
if (CUDA_FOUND)
	set (OUTPUTFILE ${CMAKE_CURRENT_SOURCE_DIR}/build/cuda_script)
	set (CUDAFILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/cudadetect.cu)
	execute_process(COMMAND nvcc -lcuda ${CUDAFILE} -o ${OUTPUTFILE})
	execute_process(COMMAND ${OUTPUTFILE}
			RESULT_VARIABLE CUDA_RETURN_CODE
			OUTPUT_VARIABLE ARCH)
	if(${CUDA_RETURN_CODE} EQUAL 0)
		set(CUDA_SUCCESS "True")
	else ()
		set (CUDA_SUCCESS "False")
	endif ()

	if (${CUDA_SUCCESS})
		message(STATUS "CUDA Architecture: ${ARCH}")
		message(STATUS "CUDA Version: ${CUDA_VERSION_STRING}")
		message(STATUS "CUDA Path: " ${CDUA_TOOLKIT_ROOT_DIR})
		message(STATUS "CUDA Libraries: ${CUDA_LIBRARIES}")
		message(STATUS "CUDA Performance Primitives: ${CUDA_npp_LIBRARY}")

		set (CUDA_NVCC_FLAGS "${ARCH}")
		add_definitions(-DGPU)
	else()
		message(WARNING ${ARCH})
	endif()
endif()


################################################
# setting the headers and sources of our library

set (GEOCOLD_HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/include/light.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/line.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/point.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/ray.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/vec3.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/geocold.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/define.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/rendererapplication.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/common.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/normal.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/objloader.hpp

	#${CMAKE_CURRENT_SOURCE_DIR}/include/rendererwindow.hpp
)

set (GEOCOLD_SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/include/rendererapplication.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/objloader.cpp
	#	${CMAKE_CURRENT_SOURCE_DIR}/include/rendererwindow.cpp
	)

	

# set (GEOCOLD_TEST_SOURCES
# 	testbench/firsttest.cpp
# 	testbench/firstbench.cpp
#
# )

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/glfw)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/glad)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/glm)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/googletest)
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/benchmark)

set(GLFW_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/include)
set(GLAD ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include)
set(GOOGLETEST ${CMAKE_CURRENT_SOURCE_DIR}/external/googletest/googletest/include)

set(GEOCOLD_MAIN_SOURCES
	main/main.cpp
)


set(GEOCOLD_TEST_SOURCES
	testbench/firsttest.cpp)

# add_executable(geocold_test ${GEOCOLD_TEST_SOURCES})


add_library(geocold_lib STATIC 
	${GEOCOLD_HEADERS}
	${GEOCOLD_SOURCES}
	)

# target_include_directories(geocold_lib PUBLIC	
# 	include
# )

# target_include_directories(geocold_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/include)

# set_property(GLOBAL PROPERTY USE_FOLDERS ON)


set (BUILD_SHARED_LIBS OFF)

# add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/external)

target_include_directories(geocold_lib PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${GLFW_INCLUDE}
	${GLAD}
	${VULKAN_INCLUDE_DIRS}
	)

set (ALL_GEOCOLD_LIBS
	geocold_lib
	glfw
	Vulkan::Vulkan
	glad
	OpenGL::GL
	) 

add_executable(geocold_main ${GEOCOLD_MAIN_SOURCES}) #${GEOCOLD_HEADERS})
target_link_libraries(geocold_main ${ALL_GEOCOLD_LIBS})
target_include_directories(geocold_main PUBLIC ${VULKAN_INCLUDE_DIRS})
target_include_directories(geocold_main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(geocold_test ${GEOCOLD_TEST_SOURCES})
target_link_libraries(geocold_test ${ALL_GEOCOLD_LIBS} gtest_main)
target_include_directories(geocold_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(geocold_test PUBLIC ${GOOGLETEST})


