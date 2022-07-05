
#ifndef GEOCOLD_INCLUDE_PRIMITIVES_VEC3_HPP 
#define GEOCOLD_INCLUDE_PRIMITIVES_VEC3_HPP 

#include <cmath>
#include <algorithm>
#include <iostream>
#include <cassert>
#include "definitions.hpp"

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

template <typename T>
class Vec3 {
//members
private:

  T m_x;
  T m_y;
  T m_z;

public:
  using index_type = std::size_t; 
  using element_type = T;
  using size_type = std::size_t;
//methods
  constexpr Vec3() : m_x{0}, m_y{0}, m_z{0} {} //default constructor

  constexpr Vec3(T x_f, T y_f, T z_f) : m_x{x_f}, m_y{y_f}, m_z{z_f} {} // constructor
  
  constexpr explicit Vec3(const Normal3<T>& normal) noexcept 
    :m_x{normal.x()}, 
     m_y{normal.y()},
     m_z{normal.z()} 
  {}
  

  constexpr explicit Vec3(const Point3<T>& point) noexcept 
    :m_x{point.x()}, 
     m_y{point.y()},
     m_z{point.z()} 
  {
    assert(!hasNaNs());
  }

  [[nodiscard]] constexpr T x() const noexcept { return m_x; }

  [[nodiscard]] constexpr T y() const noexcept { return m_y; }

  [[nodiscard]] constexpr T z() const noexcept{ return m_z; }

  [[nodiscard]] constexpr Vec3 operator-() const noexcept { return Vec3(-m_x, -m_y, -m_z); }

  [[nodiscard]] constexpr T operator[](int idx) const { 
    assert(idx < static_cast<int>(3) && idx >= static_cast<int>(0));
    return idx == 0 ?  m_x 
                    : idx == 1 ? m_y
                    : m_z;
  }

  [[nodiscard]] constexpr T& operator[](int idx) { 
    assert(idx < static_cast<int>(3) && idx >= static_cast<int>(0));
    return idx == 0 ?  m_x 
                    : idx == 1 ? m_y
                    : m_z;
  }

  [[nodiscard]] constexpr Vec3<T>& operator+=(const Vec3<T>& vec) const noexcept {
    m_x += vec.x();
    m_y += vec.y();
    m_z += vec.z();
    return *this;
  }

  [[nodiscard]] constexpr Vec3<T>& operator-=(const Vec3<T>& vec) const noexcept {
    m_x -= vec.x();
    m_y -= vec.y();
    m_z -= vec.z();
    return *this;
  }

  [[nodiscard]] constexpr Vec3<T>& operator*=(const Vec3<T>& vec) const noexcept {
    m_x *= vec.x();
    m_y *= vec.y();
    m_z *= vec.z();
    return *this;
  }

  [[nodiscard]] constexpr Vec3<T>& operator/=(const element_type denom) {
    assert(denom != 0);
    return (*this) *= static_cast<element_type>(1/denom);
  }

  [[nodiscard]] constexpr Vec3<T> operator+(const Vec3<T>& vec) const noexcept {
    Vec3<T> temp = Vec3(this->x(), this->y(), this->z());
    temp += vec;
    return temp;
  }

  [[nodiscard]] constexpr Vec3<T> operator-(const Vec3<T>& vec) const noexcept {
    Vec3<T> temp = Vec3(this->x(), this->y(), this->z());
    temp -= vec;
    return temp;
  }

  [[nodiscard]] constexpr T& dot(Vec3<T>& vec) const noexcept {
    return this->m_x * vec.x() + this->m_y * vec.y() + this->m_z * vec.z();
  }
  
  [[nodiscard]] constexpr T squared_l2_norm() const noexcept { return m_x * m_x + m_y * m_y + m_z * m_z; }

  [[nodiscard]] constexpr T norm() const { return std::sqrt(squared_l2_norm()); }

  [[nodiscard]] constexpr Vec3<T> operator*=(T scalar) {
    this->m_x *= scalar;
    this->m_y *= scalar;
    this->m_z *= scalar;
    return *this;
  }

  [[nodiscard]] constexpr Vec3<T> operator*(T scalar) {
    auto temp = Vec3<T>(this->m_x, this->m_y, this->m_z);
    temp *= scalar;
    return temp;
  }
  
  [[nodiscard]] constexpr Vec3<T> operator/(T scalar) {
    auto temp = Vec3<T>(this->m_x, this->m_y, this->m_z);
    temp *= static_cast<element_type>(1)/scalar;
    return temp;
  }

  [[nodiscard]] constexpr Vec3<T> abs() {
    return Vec3<T>(std::abs(this->x()), std::abs(this->y()), std::abs(this->z()));
  }

  [[nodiscard]] constexpr bool hasNaNs() const noexcept {
    return std::isnan(m_x)|| std::isnan(m_y) || std::isnan(m_z);
  }


  [[nodiscard]] Vec3<T> cross(const Vec3<T>& vec) const noexcept {
    auto vecx = vec.x();
    auto vecy = vec.y();
    auto vecz = vec.z();
    return Vec3<T>((this->y()) * vecz) - (this->z() * vecy),
    (this->z() * vecx) - (this->x() * vecz),
    (this->x() * vecy) - (this->y() * vecx);
  }

};


/* -------- typedefs for Vec3                             -------- */
using Vec3f0 = Vec3<float>;
using Vec3f = Vec3<double>;
using Vec3i = Vec3<int>;
/* -------- typedefs for Vec3                             -------- */


} //namespace geocold

#endif
