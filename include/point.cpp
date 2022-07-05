
#include "point.hpp"

namespace geocold {


[[nodiscard]] constexpr float Point3::operator[](int idx) const { 
  assert(idx < 3 && idx >= 0);
  return idx == 0 ?  x_
                  : idx == 1 ? y_
                  : z_;
}


[[nodiscard]] constexpr float& Point3::operator[](int idx) { 
  assert(idx < 3 && idx >= 0);
  return idx == 0 ?  x_
                  : idx == 1 ? y_
                  : z_;
}

[[nodiscard]] constexpr Vec3 Point3::operator-(const Point3& rhs) const noexcept {
  return Vec3{x_ - rhs.x(), y_ - rhs.y(), z_ - rhs.z()};
}

[[nodiscard]] constexpr Point3 Point3::divide(const Point3& point) const noexcept {
  return Point3{
    x_ / point.x(),
    y_ / point.y(),
    z_ / point.z()
  };
}








} //namespace geocold 
