#ifndef GEOCOLD_INCLUDE_PRIMITIVES_RAY_HPP 
#define GEOCOLD_INCLUDE_PRIMITIVES_RAY_HPP 

#include "point.hpp"
#include "vec3.hpp"

namespace geocold {

/* 
 * According to Shirley in the Fundamentals of 
 * Computer Graphics, a Ray is just a point and a 
 * direction of propagation. In 3d, we use the 
 * parametric equation for this.
 *
 * p(t) = e + t(s-e)
 * */

template <typename T>
class Ray {
private:
  Point3<T> origin;
  Vec3<T> direction;
  T tmin; // based on directX ray tracer
  T tmax;

  

   

public:
  Ray() = default;

  Ray(const Vec3<T>& origin_,
      const Vec3<T>& direction_,
      T tmin_ = T(0),
      T tmax_ = std::numeric_limits<T>::max) 
    :origin{origin_}
    ,direction{direction_}
    ,tmin{tmin_}
    ,tmax{tmax_}
    {}

  Point3<T> operator()(T param) {
    return (origin + param * direction);
  }

};






} //namespace geocold;

#endif
