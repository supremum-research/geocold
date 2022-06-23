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

template <typename T>
Vec3<T> operator*(T scalar, const Vec3<T>& vec) {
  return vec * scalar;
}

template <typename T>
Vec3<T> normalize(const Vec3<T>& vec) {
  return vec / vec.norm();
} 

template <typename T>
T mincomp(const Vec3<T>& vec) { return std::min(vec.x(), std::min(vec.y(), vec.z())); }

template <typename T>
T maxcomp(const Vec3<T>& vec) { return std::max(vec.x(), std::min(vec.y(), vec.z())); }


//construct a local coordinate system given only a single vector.
template <typename T>
Vec3<T> CoordinateSystem() {

}


} //namespace geocold










#endif

