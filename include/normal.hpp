#ifndef GEOCOLD_INCLUDE_PRIMITIVES_NORMAL_HPP 
#define GEOCOLD_INCLUDE_PRIMITIVES_NORMAL_HPP 

#include <cassert>
#include "vec3.hpp"


//A good ray tracer should separate the difference between a normal, a vector,
//a point and a ray.
template <typename T>
class Normal3 {
  private: 
    T x_;
    T y_;
    T z_;

  public:
    constexpr explicit Normal3(const Vec3<T>& vec) noexcept : x_{vec.x()}, y_{vec.y()}, z_{vec.z()} {}

};




#endif
