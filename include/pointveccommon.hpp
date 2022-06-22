#ifndef GEOCOLD_INCLUDE_POINT_VEC_COMMON_HPP
#define GEOCOLD_INCLUDE_POINT_VEC_COMMON_HPP


#include "point.hpp"
#include "vec3.hpp"

namespace geocold {

template <typename T>
Point3<T> operator+(const Point3<T>& point, const Vec3<T>& vec) noexcept {
  return Point3<T>(point.x() + vec.x(), point.y() + vec.y(), point.z() + vec.z());
}

template <typename T>
Point3<T> operator-(const Point3<T>& point, const Vec3<T>& vec) noexcept {
  return Point3<T>(point.x() - vec.x(), point.y() - vec.y(), point.z() - vec.z());
}

} //namespace geocold










#endif

