#include "bounding_boxes.hpp"
#include "common.hpp"

namespace geocold {



inline const Point3& BoundingBox3D::operator[](int f_i) const {
    return f_i == 0 ? pmin_ : pmax_;
}

inline Point3& BoundingBox3D::operator[](int f_i) {
    return f_i == 0 ? pmin_ : pmax_;
}

[[nodiscard]] inline BoundingBox3D BoundingBox3D::box_union(const BoundingBox3D& box) const {
    return BoundingBox3D{
        Point3{ 
            std::min((*this).pmin_.x(), box.pmin_.x()),
            std::min((*this).pmin_.y(), box.pmin_.y()),
            std::min((*this).pmin_.z(), box.pmin_.z())
        },
        Point3{
            std::max((*this).pmax_.x(), box.pmax_.x()),
            std::max((*this).pmax_.y(), box.pmax_.y()),
            std::max((*this).pmax_.z(), box.pmax_.z())
        }
    };
}


Vec3 BoundingBox3D::diagonal() const noexcept {
    return Vec3(pmax_ - pmin_);
}

[[nodiscard]]
inline float BoundingBox3D::surfacearea() const noexcept {
    auto d = this->diagonal();
    return 2 * (d.x() * d.y() + d.y() * d.z() + d.x() * d.z());
}

[[nodiscard]]
inline float BoundingBox3D::volume() const {
    auto d = this->diagonal();
    return d.x() * d.y() * d.z();
}

[[nodiscard]]
Vec3 BoundingBox3D::offset(const Point3& point) const {
    return (point - this->pmin_) / (this->pmax_ - this->pmin_);
}

[[nodiscard]] Axis BoundingBox3D::max_extent() const noexcept {
    auto d = this->diagonal();
    if ( d.x() > d.y() && d.x() > d.z() ) {
        return Axis::X;
    } else if ( d.y() > d.z() ) {
        return Axis::Y; 
    } else {
        return Axis::Z;
    }
}

[[nodiscard]] Point3 BoundingBox3D::lerp(const Point3& t) const {
    return Point3{
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









} //namespace geocold 
