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
  Point3<T> origin_;
  Vec3<T> direction_;
  T tmin; // based on directX ray tracer
  T tmax;

  

   

public:
  Ray() = default;

  Ray(const Point3<T>& origin_,
      const Vec3<T>& direction_,
      T tmin_ = T(0),
      T tmax_ = std::numeric_limits<T>::max) 
    :origin_{origin_}
    ,direction_{direction_}
    ,tmin{tmin_}
    ,tmax{tmax_}
    {}

  Point3<T> origin() const {
    return origin_;
  }

  Vec3<T> direction() const {
    return direction_;
  }

  Point3<T> operator()(T param) const {
    return (origin_ + param * direction_);
  }

};






} //namespace geocold;

#endif
