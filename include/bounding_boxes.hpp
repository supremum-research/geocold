#ifndef GEOCOLD_INCLUDE_BOUNDING_BOXES_HPP 
#define GEOCOLD_INCLUDE_BOUNDING_BOXES_HPP 

#include <limits>
#include <cmath>
#include <algorithm>

#include "definitions.hpp"
#include "point.hpp"
#include "vec3.hpp"

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
struct BoundingBox3D {
    Point3 pmin_;
    Point3 pmax_;

    BoundingBox3D() noexcept {
        float min_num = std::numeric_limits<float>::lowest();
        float max_num =  std::numeric_limits<float>::max();
        pmin_ = Point3(max_num, max_num, max_num);
        pmin_ = Point3(min_num, min_num, min_num);
    }

    explicit BoundingBox3D(const Point3& point)  
        :pmin_{point}
        ,pmax_{point}
    {}

    BoundingBox3D(const Point3& point1, const Point3& point2) 
        :pmin_{std::min(point1.x(), point2.x()), std::min(point1.y(), point2.y()), std::min(point1.z(), point2.z())}
        ,pmax_{std::max(point1.x(), point2.x()), std::max(point1.y(), point2.y()), std::max(point1.z(), point2.z())}
    {}

    const Point3& operator[](int f_i) const;

    Point3& operator[](int f_i);

    [[nodiscard]] BoundingBox3D box_union(const BoundingBox3D& box) const;

    Vec3 diagonal() const noexcept;

    [[nodiscard]]
    float surfacearea() const noexcept;

    [[nodiscard]]
    float volume() const;

    [[nodiscard]]
    Vec3 offset(const Point3& point) const;

    [[nodiscard]] Axis max_extent() const noexcept;

    //lerp linearly interpolates between corners of the 
    //box by given amount in each dimension.
    [[nodiscard]] Point3 lerp(const Point3& t) const;


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
    [[nodiscard]] bool rapidintersect(Ray ray, const Vec3 invdir, const int dirisneg[3]) const {
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




} //namespace geocold



#endif
