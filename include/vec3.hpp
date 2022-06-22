
#ifndef GEOCOLD_INCLUDE_PRIMITIVES_VEC3_HPP 
#define GEOCOLD_INCLUDE_PRIMITIVES_VEC3_HPP 

#include <cmath>
#include <iostream>
#include <cassert>


/// A vector has the following operations defined on it. 
/// 1. multiplication with a negative scalar no. => all coordinates are made negative
/// 2. [] indexing that checks the input index 
/// 3. *= operation with another vector => element wise *= operation.
/// 4. /= with a scalar no. => every element of the vector /= with the scalar
/// 5. addition betn vectors 'u' and 'v' => implements element wise addition => returns a vector
/// 6. difference of 'v' from 'u' => v - u => element wise subtraction => returns a vector
/// 7. inner_product of two vectors => element wise product and a then sum => returns a scalar
/// 8. norm => gives the l2 norm of the vector => is a scalar no.
/// 9. squared_l2_norm => gives the square of the norm() of the vector.
/// 10. += and -= operations between vectors used to implement + and - between vectors
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
  
  [[nodiscard]] constexpr T x() const noexcept { return m_x; }

  [[nodiscard]] constexpr T y() const noexcept { return m_y; }

  [[nodiscard]] constexpr T z() const noexcept{ return m_z; }

  [[nodiscard]] constexpr Vec3 operator-() const noexcept { return Vec3(-m_x, -m_y, -m_z); }

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

  [[nodiscard]] constexpr T& inner_product(Vec3<T>& vec) const noexcept {
    return this->m_x * vec.x() + this->m_y * vec.y() + this->m_z * vec.z();
  }
  
  [[nodiscard]] constexpr T squared_l2_norm() const noexcept { return m_x * m_x + m_y * m_y + m_z * m_z; }

  [[nodiscard]] constexpr T norm() const { return std::sqrt(squared_l2_norm()); }

};


using Vec3f0 = Vec3<float>;
using Vec3f = Vec3<double>;
using Vec3i = Vec3<int>;


#endif
