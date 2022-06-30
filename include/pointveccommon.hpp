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

template <typename T>
Vec3<T> CrossProduct(const Vec3<T>& v1, const Vec3<T>& v2) {
    auto vec1x = v1.x();
    auto vec1y = v1.y();
    auto vec1z = v1.z();

    auto vec2x = v2.x();
    auto vec2y = v2.y();
    auto vec2z = v2.z();

    return Vec3<T>((vec1y*vec2z) - (vec1z*vec2y), 
        (vec1z * vec2x) - (vec1x * vec2z),
        (vec1x * vec2y) -  (vec1y * vec2x)
        );
  }



//construct a local coordinate system given only a single vector.
template <typename T>
Vec3<T> CoordinateSystem(const Vec3<T>& v1, Vec3<T>* v2, Vec3<T>* v3) {

  if (std::abs(v1.x()) > std::abs(v1.y)) {
    *v2 = Vec3<T>(-v1.z(), 0, v1.x()) /
          std::sqrt(v1.x() * v1.x() + v1.z() * v1.z());
  } else {
    *v2 = Vec3<T>(0, v1.z(), -v1.y()) /
          std::sqrt(v1.y() * v1.y() + v1.z() * v1.z());
  }

  *v3 = CrossProduct(v1, *v2);
}


} //namespace geocold










#endif

