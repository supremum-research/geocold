#ifndef GEOCOLD_INCLUDE_PRIMITIVES_NORMAL_HPP 
#define GEOCOLD_INCLUDE_PRIMITIVES_NORMAL_HPP 

#include <cassert>
#include <cmath>
//#include "vec3.hpp"
#include "common.hpp"


//A good ray tracer should separate the difference between a normal, a vector,
//a point and a ray.
namespace geocold {

template <typename T>
class Normal3 {
  private: 
    T x_;
    T y_;
    T z_;

  public:

    using index_type = std::size_t; 
    using element_type = T;
    using size_type = std::size_t;

    Normal3() :x_{T(0)}, y_{T(0)}, z_{T(0)} {} 
    
    constexpr explicit Normal3(const Vec3<T>& vec) noexcept : x_{vec.x()}, y_{vec.y()}, z_{vec.z()} {
      assert(!vec.hasNaNs());
    }

    constexpr Normal3(T x_f, T y_f, T z_f) : x_{x_f}, y_{y_f}, z_{z_f} {} // constructor
    

    [[nodiscard]] constexpr T x() const noexcept { return x_; }

    [[nodiscard]] constexpr T y() const noexcept { return y_; }

    [[nodiscard]] constexpr T z() const noexcept{ return z_; }

    [[nodiscard]] constexpr Normal3 operator-() const noexcept { return Normal3(-x_, -y_, -z_); }

    [[nodiscard]] constexpr T operator[](index_type idx) const { 
      assert(idx < static_cast<int>(3) && idx >= static_cast<int>(0));
      return idx == 0 ?  x_ 
                      : idx == 1 ? y_
                      : z_;
    }

    [[nodiscard]] constexpr T& operator[](index_type idx) { 
      assert(idx < static_cast<int>(3) && idx >= static_cast<int>(0));
      return idx == 0 ?  x_ 
                      : idx == 1 ? y_
                      : z_;
    }

    [[nodiscard]] constexpr Normal3<T>& operator+=(const Normal3<T>& vec) const noexcept {
      x_ += vec.x();
      y_ += vec.y();
      z_ += vec.z();
      return *this;
    }

    [[nodiscard]] constexpr Normal3<T>& operator-=(const Normal3<T>& vec) const noexcept {
      x_ -= vec.x();
      y_ -= vec.y();
      z_ -= vec.z();
      return *this;
    }

    [[nodiscard]] constexpr Normal3<T>& operator*=(const Normal3<T>& vec) const noexcept {
      x_ *= vec.x();
      y_ *= vec.y();
      z_ *= vec.z();
      return *this;
    }

    [[nodiscard]] constexpr Normal3<T>& operator/=(const element_type denom) {
      assert(denom != 0);
      return (*this) *= static_cast<element_type>(1/denom);
    }

    [[nodiscard]] constexpr Normal3<T> operator+(const Normal3<T>& vec) const noexcept {
      Vec3<T> temp = Vec3(this->x(), this->y(), this->z());
      temp += vec;
      return temp;
    }

    [[nodiscard]] constexpr Normal3<T> operator-(const Normal3<T>& vec) const noexcept {
      Vec3<T> temp = Vec3(this->x(), this->y(), this->z());
      temp -= vec;
      return temp;
    }

    [[nodiscard]] constexpr Normal3<T> normalize() const {
      auto norm = std::sqrt(this->x_*this->x_ + this->y_ * this->y_ + this->z_ * this->z_);
      return Normal3<T>{
        this->x_ / norm,
        this->y_ / norm,
        this->z_ / norm
      };
    }


};

using Normal3f0 = Normal3<float>;
using Normal3f  = Normal3<double>;
using Normal3i = Normal3<int>;

} //namespace geocold


#endif
