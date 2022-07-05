#include "point.hpp"
#include "vec3.hpp"

namespace geocold {


constexpr Vec3::Vec3(const Normal3& normal) noexcept 
  :x_{normal.x()}, 
   y_{normal.y()},
   z_{normal.z()} 
{}


constexpr Vec3::Vec3(const Point3& point) noexcept 
  :x_{point.x()}, 
   y_{point.y()},
   z_{point.z()} 
{
  assert(!hasNaNs());
}

[[nodiscard]] inline constexpr Vec3 Vec3::operator-() const noexcept { 
  return Vec3{-x_, -y_, -z_}; 
}

[[nodiscard]] inline constexpr float Vec3::operator[](int idx) const { 
  assert(idx < static_cast<int>(3) && idx >= static_cast<int>(0));
  return idx == 0 ?  x_ 
                  : idx == 1 ? y_
                  : z_;
}


[[nodiscard]] inline constexpr float& Vec3::operator[](int idx) { 
  assert(idx < static_cast<int>(3) && idx >= static_cast<int>(0));
  return idx == 0 ?  x_
                  : idx == 1 ? y_
                  : z_;
}

[[nodiscard]] inline constexpr Vec3& Vec3::operator+=(const Vec3& vec) noexcept {
  x_ += vec.x();
  y_ += vec.y();
  z_ += vec.z();
  return *this;
}


[[nodiscard]] inline constexpr Vec3& Vec3::operator-=(const Vec3& vec) noexcept {
  x_ -= vec.x();
  y_ -= vec.y();
  z_ -= vec.z();
  return *this;
}

[[nodiscard]] inline constexpr Vec3& Vec3::operator*=(const Vec3& vec) noexcept {
  x_ *= vec.x();
  y_ *= vec.y();
  z_ *= vec.z();
  return *this;
}

[[nodiscard]] inline constexpr Vec3 Vec3::operator/=(const float& denom) {
  assert(denom != 0);
  return (*this) *= static_cast<float>(1/denom);
}

[[nodiscard]] inline constexpr Vec3 Vec3::operator+(const Vec3& vec) const noexcept {
  Vec3 temp = Vec3(this->x(), this->y(), this->z());
  temp += vec;
  return temp;
}

[[nodiscard]] inline constexpr Vec3 Vec3::operator-(const Vec3& vec) const noexcept {
  Vec3 temp = Vec3(this->x(), this->y(), this->z());
  temp -= vec;
  return temp;
}


[[nodiscard]] constexpr float Vec3::dot(Vec3& vec) const noexcept {
  return this->x_ * vec.x() + this->y_ * vec.y() + this->z_ * vec.z();
}

[[nodiscard]] inline constexpr float Vec3::squared_l2_norm() const noexcept { return x_ * x_ + y_ * y_ + z_ * z_; }

[[nodiscard]] inline constexpr float Vec3::norm() const { return std::sqrt(squared_l2_norm()); }

[[nodiscard]] inline constexpr Vec3 Vec3::operator*=(float scalar) {
  this->x_ *= scalar;
  this->y_ *= scalar;
  this->z_ *= scalar;
  return *this;
}

[[nodiscard]] constexpr Vec3 Vec3::operator*(float scalar) const {
  auto temp = Vec3(this->x_, this->y_, this->z_);
  temp *= scalar;
  return temp;
}

[[nodiscard]] constexpr Vec3 Vec3::operator/(float scalar) const {
  auto temp = Vec3(this->x_, this->y_, this->z_);
  temp *= static_cast<float>(1)/scalar;
  return temp;
}

[[nodiscard]] constexpr Vec3 Vec3::abs() {
  return Vec3{std::abs(this->x()), std::abs(this->y()), std::abs(this->z())};
}

[[nodiscard]] constexpr bool Vec3::hasNaNs() const noexcept {
  return std::isnan(x_)|| std::isnan(y_) || std::isnan(z_);
}

[[nodiscard]] Vec3 Vec3::cross(const Vec3& vec) const noexcept {
  auto vecx = vec.x();
  auto vecy = vec.y();
  auto vecz = vec.z();
  return Vec3{(y_ * vecz) - (z_ * vecy),
              (z_ * vecx) - (x_ * vecz),
              (x_ * vecy) - (y_ * vecx)
  };
}


[[nodiscard]] constexpr Vec3 Vec3::operator/(const Vec3& denom) const {
  return Vec3 {
    x_ / denom.x_,
    y_ / denom.y_,
    z_ / denom.z_
  };
}







}// namespace geocold 
