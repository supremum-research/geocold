#ifndef GEOCOLD_INCLUDE_POINT_VEC_COMMON_HPP
#define GEOCOLD_INCLUDE_POINT_VEC_COMMON_HPP


#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>
#include <limits>
#include <optional>
#include <tuple>

#include "definitions.hpp"

//#include "bounding_boxes.hpp"
//#include "point.hpp" 
//#include "vec3.hpp" 
//#include "normal.hpp"

namespace geocold {

Point3 operator+(const Point3& point, const Vec3& vec) noexcept {
  return Point3(point.x() + vec.x(), point.y() + vec.y(), point.z() + vec.z());
}

Point3 operator-(const Point3& point, const Vec3& vec) noexcept {
  return Point3(point.x() - vec.x(), point.y() - vec.y(), point.z() - vec.z());
}

Vec3 operator*(float scalar, Vec3 vec) {
  return vec * scalar;
}

Vec3 normalize(Vec3 vec) {
  return vec / vec.norm();
} 

float mincomp(const Vec3& vec) { return std::min(vec.x(), std::min(vec.y(), vec.z())); }

float maxcomp(const Vec3& vec) { return std::max(vec.x(), std::min(vec.y(), vec.z())); }

Vec3 cross_product(const Vec3& v1, const Vec3& v2) {
    auto vec1x = v1.x();
    auto vec1y = v1.y();
    auto vec1z = v1.z();

    auto vec2x = v2.x();
    auto vec2y = v2.y();
    auto vec2z = v2.z();

    return Vec3{(vec1y*vec2z) - (vec1z*vec2y), 
        (vec1z * vec2x) - (vec1x * vec2z),
        (vec1x * vec2y) - (vec1y * vec2x)
    };
  }



//construct a local coordinate system given only a single vector.
std::tuple<Vec3, Vec3> CoordinateSystem(const Vec3& e1_) {
  Vec3 e2_;

  if ( std::abs(e1_.x()) > std::abs(e1_.y()) ) {
    auto inv_len = 1.0 / std::sqrt(e1_.x() * e1_.x() + e1_.z() * e1_.z() );
    e2_ = Vec3{-e1_.z() * inv_len, 0.0, e1_.x() * inv_len};
  } else {
    auto inv_len = 1.0 / std::sqrt(e1_.y() * e1_.y() + e1_.z() * e1_.z());
    e2_ = Vec3{0.0, e1_.z() * inv_len, -e1_.y() * inv_len};
  }

  Vec3 e3_ = cross_product(e1_, e2_);
  return std::make_tuple(e2_, e3_);
}

float dot(const Normal3& normal, const Vec3& vec) {
  Vec3 left {normal};
  return left.dot(vec);
}

float dot(const Vec3& vec, const Normal3& normal) {
  return dot(normal, vec);
}

///get a box that spans the passed point by expanding
inline BoundingBox3D point_union(const BoundingBox3D& box, const Point3& point) {
  return BoundingBox3D{
      Point3{ 
        std::min(box.pmin_.x(), point.x()),
        std::min(box.pmin_.y(), point.y()),
        std::min(box.pmin_.z(), point.z())
      },
      Point3{
          std::max(box.pmax_.x(), point.x()), 
          std::max(box.pmax_.y(), point.y()), 
          std::max(box.pmax_.z(), point.z()) 
      }
  };
}

BoundingBox3D box_union(const BoundingBox3D& box1, const BoundingBox3D& box2) {
  return BoundingBox3D{
      Point3{ 
          std::min(box1.pmin_.x(), box2.pmin_.x()),
          std::min(box1.pmin_.y(), box2.pmin_.y()),
          std::min(box1.pmin_.z(), box2.pmin_.z())
      },
      Point3{
          std::max(box1.pmax_.x(), box2.pmax_.x()),
          std::max(box1.pmax_.y(), box2.pmax_.y()),
          std::max(box1.pmax_.z(), box2.pmax_.z())
      }
  };
}

BoundingBox3D box_intersection(const BoundingBox3D& box1, const BoundingBox3D& box2) {
  return BoundingBox3D{
      Point3{ 
          std::max(box1.pmin_.x(), box2.pmin_.x()),
          std::max(box1.pmin_.y(), box2.pmin_.y()),
          std::max(box1.pmin_.z(), box2.pmin_.z())
      },
      Point3{
          std::min(box1.pmax_.x(), box2.pmax_.x()),
          std::min(box1.pmax_.y(), box2.pmax_.y()),
          std::min(box1.pmax_.z(), box2.pmax_.z())
      }
  };
}

//overlap test between bounding boxes in all three dimensions
bool overlap(const BoundingBox3D& box1, const BoundingBox3D& box2) {
  bool x = (box1.pmax_.x() >= box2.pmin_.x()) && (box1.pmin_.x() <= box2.pmax_.x());
  bool y = (box1.pmax_.y() >= box2.pmin_.y()) && (box1.pmin_.y() <= box2.pmax_.y());
  bool z = (box1.pmax_.z() >= box2.pmin_.z()) && (box1.pmin_.z() <= box2.pmax_.z());
  return (x && y && z);
}

//containment test of point inside a boundin box
bool contains(const BoundingBox3D& box, const Point3& point) {
  return (point.x() >= box.pmin_.x() && point.x() <= box.pmax_.x() &&
          point.y() >= box.pmin_.y() && point.y() <= box.pmax_.y() &&
          point.z() >= box.pmin_.z() && point.z() <= box.pmax_.z());
}

inline BoundingBox3D expand(const BoundingBox3D& box, const float& delta) {
  return BoundingBox3D{
    Point3{box.pmin_ - Vec3{delta, delta, delta}},
    Point3{box.pmax_ + Vec3{delta, delta, delta}}
  };
}

///linearly interpolate between 'a' and 'b' 
///at some distance 't' where t belongs to [0,1].

inline float linearinterpolate(float t, const float& a, const float& b) {
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



inline float to_radians(float degree) {
  return M_PI / 180.0 * degree;
}

inline float gamma(int n) {
  auto machine_eps = std::numeric_limits<float>::epsilon();
  return (n * machine_eps) / (1 - n * machine_eps);
}


constexpr Point3 vec_to_point(const Vec3& vec) noexcept {
  return Point3{
    vec.x_,
    vec.y_,
    vec.z_
  };
}




} //namespace geocold


#endif

