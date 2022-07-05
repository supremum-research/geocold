#ifndef GEOCOLD_INCLUDE_PRIMITIVES_POINT_HPP 
#define GEOCOLD_INCLUDE_PRIMITIVES_POINT_HPP 

#include <array>
#include <cassert>
#include <cmath>
//#include "vec3.hpp"

#include "definitions.hpp"
#include "vec3.hpp"


namespace geocold {

/// A point has the following operations defined on it. 
/// 1. [] indexing that checks the input index 
/// 2. 


struct Point3 {
    float x_;
    float y_;
    float z_;

  constexpr Point3() noexcept : x_{0}, y_{0}, z_{0} {} //default constructor

  constexpr Point3(float x_f, float y_f, float z_f) noexcept : x_{x_f}, y_{y_f}, z_{z_f} {} // constructor
                                                                                            
  [[nodiscard]] constexpr float x() const noexcept { return x_; }

  [[nodiscard]] constexpr float y() const noexcept { return y_; }

  [[nodiscard]] constexpr float z() const noexcept{ return z_; }

  [[nodiscard]] constexpr float& x() noexcept { return x_; }

  [[nodiscard]] constexpr float& y() noexcept { return y_; }

  [[nodiscard]] constexpr float& z() noexcept{ return z_; }

  [[nodiscard]] constexpr float operator[](int idx) const;

  [[nodiscard]] constexpr float& operator[](int idx);

  [[nodiscard]] constexpr Vec3 operator-(const Point3& rhs) const noexcept;

  [[nodiscard]] constexpr Point3 divide(const Point3& point) const noexcept;

  [[nodiscard]] constexpr float squared_distancefromorigin() const noexcept { return x_ * x_ + y_ * y_ + z_ * z_; }

  [[nodiscard]] constexpr float distancefromorigin() const { return std::sqrt(squared_distancefromorigin()); }

};


} //namespace geocold


#endif
