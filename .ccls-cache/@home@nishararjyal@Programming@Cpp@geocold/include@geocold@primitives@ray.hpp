#ifndef GEOCOLD_INCLUDE_PRIMITIVES_RAY_HPP 
#define GEOCOLD_INCLUDE_PRIMITIVES_RAY_HPP 

#include "point.hpp"

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
  Point3<T> direction;
  T tmin; // based on directX ray tracer
  T tmax;
   

public:
  // p(t) = e + t(s-e)
  Point3<T> operator()(T param) {
    return (origin + param * direction);
  }

};






} //namespace geocold;

#endif
