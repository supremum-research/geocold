add_library(primitives INTERFACE 
  light.hpp
  line.hpp
  point.hpp
  ray.hpp
  vec3.hpp # vector on the CPU
  )

# aside vec3, also need to implement simdvec3 and gpu-cpuvec3 for benchmark later on
