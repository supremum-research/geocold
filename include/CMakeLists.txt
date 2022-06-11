add_subdirectory(algorithms)
add_subdirectory(primitives)

target_include_directories(algorithms INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(primitives INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(geocold INTERFACE 
  geocold.hpp
  )

target_link_libraries(geocold INTERFACE algorithms primitives)
