#ifndef GEOCOLD_INCLUDE_POINT_VEC_COMMON_HPP
#define GEOCOLD_INCLUDE_POINT_VEC_COMMON_HPP


#include <cmath>
#include <algorithm>
#include <optional>
#include <tuple>

//#include "bounding_boxes.hpp"
//#include "point.hpp" 
//#include "vec3.hpp" 
//#include "normal.hpp"


namespace geocold {

template <typename T>
class Point3;

template <typename T>
struct BoundingBox3D;

template <typename T>
class Vec3;

template <typename T>
  class Normal3;

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
Vec3<T> cross_product(const Vec3<T>& v1, const Vec3<T>& v2) {
    auto vec1x = v1.x();
    auto vec1y = v1.y();
    auto vec1z = v1.z();

    auto vec2x = v2.x();
    auto vec2y = v2.y();
    auto vec2z = v2.z();

    return Vec3<T>{(vec1y*vec2z) - (vec1z*vec2y), 
        (vec1z * vec2x) - (vec1x * vec2z),
        (vec1x * vec2y) - (vec1y * vec2x)
    };
  }



//construct a local coordinate system given only a single vector.
template <typename T>
std::tuple<Vec3<T>, Vec3<T>> CoordinateSystem(const Vec3<T>& e1_) {
  Vec3<T> e2_;

  if ( std::abs(e1_.x()) > std::abs(e1_.y()) ) {
    auto inv_len = 1.0 / std::sqrt(e1_.x() * e1_.x() + e1_.z() * e1_.z() );
    e2_ = Vec3<T>{-e1_.z() * inv_len, 0.0, e1_.x() * inv_len};
  } else {
    auto inv_len = 1.0 / std::sqrt(e1_.y() * e1_.y() + e1_.z() * e1_.z());
    e2_ = Vec3<T>{0.0, e1_.z() * inv_len, -e1_.y() * inv_len};
  }

  Vec3<T> e3_ = cross_product(e1_, e2_);
  return std::make_tuple(e2_, e3_);
}

template <typename T>
T dot(const Normal3<T>& normal, const Vec3<T>& vec) {
  Vec3<T> left {normal};
  return left.dot(vec);
}

template <typename T>
T dot(const Vec3<T>& vec, const Normal3<T>& normal) {
  return dot(normal, vec);
}

template <typename T>
BoundingBox3D<T> box_union(const BoundingBox3D<T>& box1, const BoundingBox3D<T>& box2) {
  return BoundingBox3D<T>{
      Point3<T>{ 
          std::min(box1.pmin_.x(), box2.pmin_.x()),
          std::min(box1.pmin_.y(), box2.pmin_.y()),
          std::min(box1.pmin_.z(), box2.pmin_.z())
      },
      Point3<T>{
          std::max(box1.pmax_.x(), box2.pmax_.x()),
          std::max(box1.pmax_.y(), box2.pmax_.y()),
          std::max(box1.pmax_.z(), box2.pmax_.z())
      }
  };
}

template <typename T>
BoundingBox3D<T> box_intersection(const BoundingBox3D<T>& box1, const BoundingBox3D<T>& box2) {
  return BoundingBox3D<T>{
      Point3<T>{ 
          std::max(box1.pmin_.x(), box2.pmin_.x()),
          std::max(box1.pmin_.y(), box2.pmin_.y()),
          std::max(box1.pmin_.z(), box2.pmin_.z())
      },
      Point3<T>{
          std::min(box1.pmax_.x(), box2.pmax_.x()),
          std::min(box1.pmax_.y(), box2.pmax_.y()),
          std::min(box1.pmax_.z(), box2.pmax_.z())
      }
  };
}

//overlap test between bounding boxes in all three dimensions
template <typename T>
bool overlap(const BoundingBox3D<T>& box1, const BoundingBox3D<T>& box2) {
  bool x = (box1.pmax_.x() >= box2.pmin_.x()) && (box1.pmin_.x() <= box2.pmax_.x());
  bool y = (box1.pmax_.y() >= box2.pmin_.y()) && (box1.pmin_.y() <= box2.pmax_.y());
  bool z = (box1.pmax_.z() >= box2.pmin_.z()) && (box1.pmin_.z() <= box2.pmax_.z());
  return (x && y && z);
}

//containment test of point inside a boundin box
template <typename T>
bool contains(const BoundingBox3D<T>& box, const Point3<T>& point) {
  return (point.x() >= box.pmin_.x() && point.x() <= box.pmax_.x() &&
          point.y() >= box.pmin_.y() && point.y() <= box.pmax_.y() &&
          point.z() >= box.pmin_.z() && point.z() <= box.pmax_.z());
}

template <typename T, typename S>
inline BoundingBox3D<T> expand(const BoundingBox3D<T>& box, const S& delta) {
  return BoundingBox3D<T> {
    Point3<T>{box.pmin_ - Vec3<T>{delta, delta, delta}},
    Point3<T>{box.pmax_ + Vec3<T>{delta, delta, delta}}
  };
}

///linearly interpolate between 'a' and 'b' 
///at some distance 't' where t belongs to [0,1].

template <typename T>
inline T linearinterpolate(float t, const T& a, const T& b) {
  return a * (1.0 - t) + b * t;
}


//returns two real roots to a*x^2 + bx + c = 0 if it exists 
//or else, it returns nullopt;
std::optional<std::tuple<float, float>> solve_quadratic(float a, float b, float c) {
  auto discr_sq = b*b - 4.0*a*c;
  if ( discr_sq < 0.0 ) {
    return std::nullopt;
  } else {
    auto discr = std::sqrt(discr_sq);
    auto root1 = 0.5f * (discr - b);
    auto root2 = 0.5f * (-discr - b);
    return std::optional(std::make_tuple(root1, root2));
  }
}







} //namespace geocold


#endif

