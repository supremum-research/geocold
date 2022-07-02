
#ifndef GEOCOLD_INCLUDE_BOUNDING_BOXES_HPP 
#define GEOCOLD_INCLUDE_BOUNDING_BOXES_HPP 

#include <algorithm>
#include <limits>
#include <cmath>
#include "common.hpp"


namespace geocold {

enum class Axis {
  X,
  Y,
  Z
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
    ///get a box that spans the passed point by expanding
    BoundingBox3D<T> point_union(const Point3<T>& box) const {
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

}; //class BoundingBox3D

using BoudingBox3Df = BoundingBox3D<double>;
using BoudingBox3Df0 = BoundingBox3D<float>;
using BoudingBox3Di = BoundingBox3D<int>;



} //namespace geocold



#endif
