#ifndef GEOCOLD_INCLUDE_PRIMITIVES_VEC3_HPP 
#define GEOCOLD_INCLUDE_PRIMITIVES_VEC3_HPP 

#include <cmath>
#include <algorithm>
#include <iostream>
#include <cassert>

#include "definitions.hpp"
#include "normal.hpp"

/// A vector has the following operations defined on it. 
/// 1. multiplication with a negative scalar no. => all coordinates are made negative
/// 2. [] indexing that checks the input index 
/// 3. *= operation with another vector => element wise *= operation.
/// 4. /= with a scalar no. => every element of the vector /= with the scalar
/// 5. addition betn vectors 'u' and 'v' => implements element wise addition => returns a vector
/// 6. difference of 'v' from 'u' => v - u => element wise subtraction => returns a vector
/// 7. inner_product of two vectors => element wise product and a then sum => returns a scalar 8. norm => gives the l2 norm of the vector => is a scalar no.
/// 9. squared_l2_norm => gives the square of the norm() of the vector.
/// 10. += and -= operations between vectors used to implement + and - between vectors
/// 11. Vec3 also supports multiplication with scalar on the left and on the right
/// the one on the left is in file common.hpp

namespace geocold {

struct Vec3 {
//members

  float x_;
  float y_;
  float z_;

//methods
  constexpr Vec3() : x_{0}, y_{0}, z_{0} {} //default constructor

  constexpr Vec3(float x_f, float y_f, float z_f) : x_{x_f}, y_{y_f}, z_{z_f} {} // constructor
  
  constexpr explicit Vec3(const Normal3& normal) noexcept;
  

  constexpr explicit Vec3(const Point3& point) noexcept;

  [[nodiscard]] constexpr float x() const noexcept { return x_; }

  [[nodiscard]] constexpr float y() const noexcept { return y_; }

  [[nodiscard]] constexpr float z() const noexcept{ return z_; }

  [[nodiscard]] constexpr float& x() noexcept { return x_; }

  [[nodiscard]] constexpr float& y() noexcept { return y_; }

  [[nodiscard]] constexpr float& z() noexcept{ return z_; }

  [[nodiscard]] constexpr Vec3 operator-() const noexcept;

  [[nodiscard]] constexpr float operator[](int idx) const;

  [[nodiscard]] constexpr float& operator[](int idx);

  [[nodiscard]] constexpr Vec3& operator+=(const Vec3& vec) noexcept;

  [[nodiscard]] constexpr Vec3& operator-=(const Vec3& vec) noexcept;

  [[nodiscard]] constexpr Vec3& operator*=(const Vec3& vec) noexcept;

  [[nodiscard]] constexpr Vec3 operator/=(const float& denom);

  [[nodiscard]] constexpr Vec3 operator+(const Vec3& vec) const noexcept;

  [[nodiscard]] constexpr Vec3 operator-(const Vec3& vec) const noexcept;

  [[nodiscard]] constexpr float dot(Vec3& vec) const noexcept;
  
  [[nodiscard]] constexpr float squared_l2_norm() const noexcept;

  [[nodiscard]] constexpr float norm() const;

  [[nodiscard]] constexpr Vec3 operator*=(float scalar);

  [[nodiscard]] constexpr Vec3 operator*(float scalar) const;
  
  [[nodiscard]] constexpr Vec3 operator/(float scalar) const;

  [[nodiscard]] constexpr Vec3 operator/(const Vec3& denom) const;

  [[nodiscard]] constexpr Vec3 abs();

  [[nodiscard]] constexpr bool hasNaNs() const noexcept;


  [[nodiscard]] Vec3 cross(const Vec3& vec) const noexcept;

};




} //namespace geocold

#endif
