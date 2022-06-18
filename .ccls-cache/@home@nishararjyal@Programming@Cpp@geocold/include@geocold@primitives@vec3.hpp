
#ifndef GEOCOLD_INCLUDE_PRIMITIVES_VEC3_HPP 
#define GEOCOLD_INCLUDE_PRIMITIVES_VEC3_HPP 

#include <cmath>
#include <iostream>
#include <cassert>

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

  constexpr Vec3(T x_f, T y_f, T z_f) : m_x{x_f}, m_y{y_f}, m_z{z_f} {} //default constructor
  
  [[nodiscard]] constexpr T x() const { return m_x; }

  [[nodiscard]] constexpr T y() const { return m_y; }

  [[nodiscard]] constexpr T z() const { return m_z; }

  [[nodiscard]] constexpr Vec3 operator-() const { return Vec3(-m_x, -m_y, -m_z); }

  [[nodiscard]] constexpr T operator[](index_type idx) const { 
    assert(idx < static_cast<std::size_t>(3) && idx >= static_cast<std::size_t>(0));
    return idx == 0 ?  m_x 
                    : idx == 1 ? m_y
                    : m_z;
  }

  [[nodiscard]] constexpr T& operator[](index_type idx) { 
    assert(idx < static_cast<std::size_t>(3) && idx >= static_cast<std::size_t>(0));
    return idx == 0 ?  m_x 
                    : idx == 1 ? m_y
                    : m_z;
  }

  [[nodiscard]] constexpr T& operator+=(const Vec3& vec) {
    m_x += vec.x();
    m_y += vec.y();
    m_z += vec.z();
    return *this;
  }

  [[nodiscard]] constexpr T& operator*=(const Vec3& vec) {
    m_x *= vec.x();
    m_y *= vec.y();
    m_z *= vec.z();
    return *this;
  }

  [[nodiscard]] constexpr T& operator/=(const element_type fraction) {
    return (*this) *= static_cast<element_type>(1/fraction);
  }

  [[nodiscard]] constexpr T length() const { return std::sqrt(this->squared_l2_norm()); }
  
  [[nodiscard]] constexpr T squared_l2_norm() const { return m_x * m_x + m_y * m_y + m_z * m_z; }

};


#endif
