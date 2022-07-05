#ifndef GEOCOLD_INCLUDE_PRIMITIVES_RAY_HPP 
#define GEOCOLD_INCLUDE_PRIMITIVES_RAY_HPP 



#include <limits>


#include "vec3.hpp"
#include "point.hpp"
#include "common.hpp"

namespace geocold {

/* 
 * According to Shirley in the Fundamentals of 
 * Computer Graphics, a Ray is just a point and a 
 * direction of propagation. In 3d, we use the 
 * parametric equation for this.
 *
 * p(t) = e + t(s-e)
 * */

struct Ray {
  Point3f0 origin_;
  Vec3f0 direction_;
  float tmin;
  float tmax;
  std::size_t depth;
  float time;


  Ray() = default;

  Ray(const Point3f0& origin,
      const Vec3f0& direction,
      float time_
      ) 
    :origin_{origin}
    ,direction_{direction}
    ,tmin{0}
    ,tmax{std::numeric_limits<float>::max()}
    ,depth{0}
    ,time{time_}
    {}

  [[nodiscard]] Point3f0 origin() const {
    return origin_;
  }

  [[nodiscard]] Vec3f0 direction() const {
    return direction_;
  }

  Point3f0 operator()(float param) const {
    return (origin_ + param * direction_);
  }

};






} //namespace geocold;

#endif
