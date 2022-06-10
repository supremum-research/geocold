cmake_minimum_required(VERSION 3.0)
project(glad)
add_library (glad STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c ${CMAKE_CURRENT_SOURCE_DIR}/include/KHR/khrplatform.h ${CMAKE_CURRENT_SOURCE_DIR}/include/glad/glad.h)


# set_property (TARGET glad PROPERTY FOLDER "ext")
