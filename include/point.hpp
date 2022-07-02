#ifndef GEOCOLD_INCLUDE_PRIMITIVES_POINT_HPP 
#define GEOCOLD_INCLUDE_PRIMITIVES_POINT_HPP 

#include <array>
#include <cassert>
//#include "vec3.hpp"
#include "common.hpp"

namespace geocold {

/// A point has the following operations defined on it. 
/// 1. [] indexing that checks the input index 
/// 2. 
template <typename T>
class Point3 {
  private: 
    T x_;
    T y_;
    T z_;


  public:

  using size_type = std::size_t;
  using index_type = size_type; 
  using element_type = T;

  constexpr Point3() noexcept : x_{0}, y_{0}, z_{0} {} //default constructor

  constexpr Point3(T x_f, T y_f, T z_f) noexcept : x_{x_f}, y_{y_f}, z_{z_f} {} // constructor

  constexpr explicit Point3<T>(const Vec3<T>& vec) noexcept {
    this->x_ = vec.x();
    this->y_ = vec.y();
    this->z_ = vec.z();
  }

  
  [[nodiscard]] constexpr T x() const noexcept { return x_; }

  [[nodiscard]] constexpr T y() const noexcept { return y_; }

  [[nodiscard]] constexpr T z() const noexcept{ return z_; }

  [[nodiscard]] constexpr T& x() noexcept { return x_; }

  [[nodiscard]] constexpr T& y() noexcept { return y_; }

  [[nodiscard]] constexpr T& z() noexcept{ return z_; }

  [[nodiscard]] constexpr T operator[](index_type idx) const { 
    assert(idx < static_cast<std::size_t>(3) && idx >= static_cast<std::size_t>(0));
    return idx == 0 ?  x_
                    : idx == 1 ? y_
                    : z_;
  }

  [[nodiscard]] constexpr T& operator[](index_type idx) { 
    assert(idx < static_cast<std::size_t>(3) && idx >= static_cast<std::size_t>(0));
    return idx == 0 ?  x_
                    : idx == 1 ? y_
                    : z_;
  }


  [[nodiscard]] constexpr Vec3<T> operator-(const Point3<T>& rhs) const noexcept {
    return Vec3<T>(this->x_ - rhs.x(), this->y_ - rhs.y(), this->z_ - rhs.z());
  }

  [[nodiscard]] constexpr Point3<T> divide(const Point3<T>& point) const noexcept {
    return Point3<T>{
      this->x_ / point.x(),
      this->y_ / point.y(),
      this->z_ / point.z()
    };
  }

  [[nodiscard]] constexpr T squared_distancefromorigin() const noexcept { return x_ * x_ + y_ * y_ + z_ * z_; }

  [[nodiscard]] constexpr T distancefromorigin() const { return std::sqrt(squared_distancefromorigin()); }

};



/* -------- typedefs for Point3                             -------- */
using Point3f0 = Point3<float>;
using Point3f = Point3<double>;
using Point3i = Point3<int>;
/* --------                              -------- */




} //namespace geocold


#endif
