#ifndef GEOCOLD_INCLUDE_BOUNDING_BOXES_HPP 
#define GEOCOLD_INCLUDE_BOUNDING_BOXES_HPP 

#include <limits>
#include <cmath>
#include <algorithm>

#include "ray.hpp"
#include "common.hpp"


namespace geocold {

enum class Axis {
  X,
  Y,
  Z
};

struct HitInterval {
  float hit0;
  float hit1;

  HitInterval() = default;

  HitInterval(float hitfirst, float hitsecond)
    :hit0{hitfirst}
    ,hit1{hitsecond}
    {}

  HitInterval(const HitInterval& right) = default;

};
  

/// Defines an Axis Aligned Bounding Box with 
/// optimized intrsection test. 
/// Designed for use with 
/// a bounding volume hierarchy.
template <typename T>
struct BoundingBox3D {
    Point3<T> pmin_;
    Point3<T> pmax_;

    BoundingBox3D() noexcept {
        T min_num = std::numeric_limits<T>::lowest();
        T max_num =  std::numeric_limits<T>::max();
        pmin_ = Point3<T>(max_num, max_num, max_num);
        pmin_ = Point3<T>(min_num, min_num, min_num);
    }

    explicit BoundingBox3D(const Point3<T>& point)  
        :pmin_{point}
        ,pmax_{point}
    {}

    BoundingBox3D(const Point3<T>& point1, const Point3<T>& point2) 
        :pmin_{std::min(point1.x(), point2.x()), std::min(point1.y(), point2.y()), std::min(point1.z(), point2.z())}
        ,pmax_{std::max(point1.x(), point2.x()), std::max(point1.y(), point2.y()), std::max(point1.z(), point2.z())}
    {}

    const Point3<T>& operator[](int f_i) const {
        return f_i == 0 ? pmin_ : pmax_;
    }

    Point3<T>& operator[](int f_i) {
        return f_i == 0 ? pmin_ : pmax_;
    }

    BoundingBox3D<T> box_union(const BoundingBox3D<T>& box) const {
        return BoundingBox3D<T>{
            Point3<T>{ 
                std::min((*this).pmin_.x(), box.pmin_.x()),
                std::min((*this).pmin_.y(), box.pmin_.y()),
                std::min((*this).pmin_.z(), box.pmin_.z())
            },
            Point3<T>{
                std::max((*this).pmax_.x(), box.pmax_.x()),
                std::max((*this).pmax_.y(), box.pmax_.y()),
                std::max((*this).pmax_.z(), box.pmax_.z())
            }
        };
    }

    Vec3<T> diagonal() const noexcept {
        return pmax_ - pmin_;
    }

    [[nodiscard]]
    T surfacearea() const noexcept {
        auto d = this->diagonal();
        return 2 * (d.x() * d.y() + d.y() * d.z() + d.x() * d.z());
    }

    [[nodiscard]]
    T volume() const {
        auto d = this->diagonal();
        return d.x() * d.y() * d.z();
    }

    Vec3<T> offset(const Point3<T>& point) const {
        return (point - this->pmin_) / (this->pmax_ - this->pmin_);
    }

    [[nodiscard]] Axis max_extent() const noexcept {
        auto d = this->diagonal();
        if ( d.x() > d.y() && d.x() > d.z() ) {
            return Axis::X;
        } else if ( d.y() > d.z() ) {
            return Axis::Y; 
        } else {
            return Axis::Z;
        }
    }

    //lerp linearly interpolates between corners of the 
    //box by given amount in each dimension.
    [[nodiscard]] Point3<T> lerp(const Point3<T>& t) const {
        return Point3<T>{
            linearinterpolate(t.x(), pmin_.x(), pmax_.x()),
            linearinterpolate(t.y(), pmin_.y(), pmax_.y()),
            linearinterpolate(t.z(), pmin_.z(), pmax_.z())
        };
    }


    [[nodiscard]] bool intersect_ray(Ray& ray, HitInterval* interv) const {
      float t0 = 0;
      float t1 = ray.tmax;
      
      for (int i = 0; i < 3; ++i) {
        float invraydir = 1 / ray.direction_[i];
        float tnear =  (this->pmin_[i] - ray.origin_[i]) * invraydir;
        float tfar = (this->pmax_[i] - ray.origin_[i]) * invraydir;

        if (tnear > tfar) {
          std::swap(tnear, tfar);
        }

        tfar *= 1 + 2 * gamma(3); //i have no clue what this is 
        t0 = tnear > t0 ? tnear : t0;
        t1 = tfar < t1 ? tfar : t1;
        if (t0 > t1) {
          return false;
        }
      }

      interv->hit0 = t0; 
      interv->hit1 = t1;
      return true;
    }

    //This method takes in addition a 
    //vector carrying the inverses of the 
    //ray's direction (to be supplied by precomputing).
    //Also takes data about whether each direction 
    //component is negative
    //this means we can remove comparison
    //between tnear and tfar in earlier method.
    //
    //I definitely didn't write this on my own 
    [[nodiscard]] bool rapidintersect(Ray ray, const Vec3f0 invdir, const int dirisneg[3]) const {
      const BoundingBox3D bounds = *this;
      float tmin = (bounds[dirisneg[0]].x() - ray.origin_.x()) * invdir.x();
      float tmax = (bounds[1 - dirisneg[0]].x() - ray.origin_.x()) * invdir.x();
      float tymin = (bounds[dirisneg[1]].y() - ray.origin_.y()) * invdir.y();
      float tymax = (bounds[1 - dirisneg[1]].y() - ray.origin_.y()) * invdir.y();

      // Update _tMax_ and _tyMax_ to ensure robust bounds intersection
      tmax *= 1 + 2 * gamma(3);
      tymax *= 1 + 2 * gamma(3);
      if (tmin > tymax || tymin > tmax) { 
        return false;
      }
      if (tymin > tmin) {
        tmin = tymin;
      }
      if (tymax < tmax) {
        tmax = tymax;
      }

      // Check for ray intersection against $z$ slab
      float tzmin = (bounds[dirisneg[2]].z() - ray.origin_.z()) * invdir.z();
      float tzmax = (bounds[1 - dirisneg[2]].z() - ray.origin_.z()) * invdir.z();

      // Update _tzMax_ to ensure robust bounds intersection
      tzmax *= 1 + 2 * gamma(3);
      if (tmin > tzmax || tzmin > tmax) {
        return false;
      }
      if (tzmin > tmin) {
        tmin = tzmin;
      }
      if (tzmax < tmax) {
        tmax = tzmax;
      } 
      return (tmin < ray.tmax) && (tmax > 0);
  }



  

}; //class BoundingBox3D

using BoundingBox3Df = BoundingBox3D<double>;
using BoundingBox3Df0 = BoundingBox3D<float>;
using BoundingBox3Di = BoundingBox3D<int>;



} //namespace geocold



#endif
