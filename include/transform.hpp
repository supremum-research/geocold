#ifndef GEOCOLD_INCLUDE_TRANSFORM_HPP 
#define GEOCOLD_INCLUDE_TRANSFORM_HPP 

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
// #include <glm/mat4x4.hpp>
// #include <glm/gtc/matrix_inverse.hpp>

#include "common.hpp"
#include "vec3.hpp"
#include "point.hpp"
#include "normal.hpp"
#include "ray.hpp"
#include "bounding_boxes.hpp"

namespace geocold {

//only defined for single precision (32 bit) floating point numbers
struct Transform {

  glm::mat4 m_;
  glm::mat4 minv_;

  Transform() 
  :m_{glm::mat4(1.)}
  ,minv_{glm::inverse(m_)}
  {}

  explicit Transform(const glm::mat4& input) noexcept 
    :m_{input}
    ,minv_{glm::inverse(input)}
  {}

  Transform(const glm::mat4& mat, const glm::mat4& minv) 
    :m_{mat}
    ,minv_{minv}
  {}
  
  [[nodiscard]] Transform inverse() const {
    return Transform{minv_, m_};
  }

  [[nodiscard]] Transform transpose() const {
    return Transform{
      glm::transpose(m_),
      glm::transpose(minv_)
    };
  }

  //take a vector of deltas for the translation 
  //along each dimension.
  //remember a translation can only be applied to a point 
  //translation leaves vectors unchanged.
  [[nodiscard]] static Transform translate(const Vec3f0& vec) {
    glm::mat4 mat(1, 0, 0, vec.x(),
                  0, 1, 0, vec.y(),
                  0, 0, 1, vec.z(),
                  0, 0, 0,      1);

    glm::mat4 matinv(1, 0, 0, -vec.x(),
                     0, 1, 0, -vec.y(),
                     0, 0, 1, -vec.z(),
                     0, 0, 0,      1);

    return Transform{ 
      mat,
      matinv
    };
  }

  [[nodiscard]] static Transform scale(float x, float y, float z) {
    assert(x != 0 && y != 0 && z != 0);

    glm::mat4 mat(x, 0, 0, 0, 
                  0, y, 0, 0, 
                  0, 0, z, 0, 
                  0, 0, 0, 1);

    glm::mat4 matinv(1/x, 0, 0, 0,
                     0, 1/y, 0, 0,
                     0, 0, 1/z, 0,
                     0, 0, 0, 1);

    return Transform{ 
      mat,
      matinv
    };
  }

  //theta is passed in degrees, rotateX auto 
  //uses it in radians
  [[nodiscard]] static Transform rotateX(float theta) noexcept {
    auto radtheta = to_radians(theta);
    float sintheta = std::sin(radtheta);
    float costheta = std::cos(radtheta);

    glm::mat4 mat(1,        0,         0, 0,
                  0, costheta, -sintheta, 0,
                  0, sintheta,  costheta, 0,
                  0,        0,         0, 1);
  
    return Transform{mat, glm::transpose(mat)};
  }

  //theta is passed in degrees, rotateX auto 
  //uses it in radians
  [[nodiscard]] static Transform rotateY(float theta) noexcept {
    auto radtheta = to_radians(theta);
    float sintheta = std::sin(radtheta);
    float costheta = std::cos(radtheta);

    glm::mat4 mat( costheta, 0, sintheta, 0,
                  0,         1, 0,        0,
                  -sintheta, 0, costheta, 0,
                  0,         0,        0, 1);
  
    return Transform{mat, glm::transpose(mat)};
  }

  //theta is passed in degrees, rotateX auto 
  //uses it in radians
  [[nodiscard]] static Transform rotateZ(float theta) noexcept {
    auto radtheta = to_radians(theta);
    float sintheta = std::sin(radtheta);
    float costheta = std::cos(radtheta);

    glm::mat4 mat(costheta, -sintheta, 0, 0,
                  sintheta,  costheta, 0, 0,
                         0,         0, 1, 0,
                         0,         0, 0, 1);
  
    return Transform{mat, glm::transpose(mat)};
  }

  [[nodiscard]] static Transform rotate_about(float theta, const Vec3f0& axis) {
    Vec3f0 a = normalize(axis);
    auto radtheta = to_radians(theta);
    float s = std::sin(radtheta);
    float c = std::cos(radtheta);

    glm::mat4 mat;
    mat[0][0] = a.x() * a.x() + (1- a.x() * a.x()) * c;
    mat[0][1] = a.x() * a.y() * (1-c) - a.z() * s;
    mat[0][2] = a.x() * a.z() * (1-c) + a.y() * s;
    mat[0][3] = 0.0;

    mat[1][0] = a.x() * a.y() * (1-c) + a.z() * s;
    mat[1][1] = a.y() * a.y() + (1- a.y() * a.y()) * c;
    mat[1][2] = a.y() * a.z() * (1- c) - a.x() * s;
    mat[1][3] = 0.0;

    mat[2][0] = a.x() * a.z() * (1- c) - a.y() * s;
    mat[2][1] = a.y() * a.z() * (1- c) + a.x() * s;
    mat[2][2] = a.z() * a.z() + (1- a.z() * a.z()) * c;
    mat[2][3] = 0.0;

    mat[3][0] = 0.0;
    mat[3][1] = 0.0;
    mat[3][2] = 0.0;
    mat[3][3] = 0.0;

    return Transform{
      mat, 
      glm::transpose(mat)
    };
  }

  //look at transformation for placing a camera in the screen 
  //gives transformation between camera space n
  static Transform look_at(const Point3f0& pos, const Point3f0& look, const Vec3f0& up) {
    auto dir = pos - look;
    auto normdir = normalize(dir);
    auto left = cross_product(up, normdir);
    auto normleft = normalize(left);
    auto u = cross_product(normdir, normleft);
    auto normu = normalize(u);

    glm::mat4 camtoworld(1.0F); 
   
    for (int i = 0; i < 3; ++i) {
      camtoworld[i][0] = -normleft[i];
      camtoworld[i][1] = normu[i];
      camtoworld[i][2] = normdir[i];
      camtoworld[i][3] = pos[i];
    }

    return Transform{camtoworld, glm::inverse(camtoworld)};
  }

  Point3f0 operator()(const Point3f0& point) const {
    float x = point.x();
    float y = point.y();
    float z = point.z();
  
    float xp = m_[0][0]*x + m_[0][1]*y + m_[0][2]*z + m_[0][3];
    float yp = m_[1][0]*x + m_[1][1]*y + m_[1][2]*z + m_[1][3];
    float zp = m_[2][0]*x + m_[2][1]*y + m_[2][2]*z + m_[2][3];
    float wp = m_[3][0]*x + m_[3][1]*y + m_[3][2]*z + m_[3][3];

    if (wp == 1) {
      return Point3f0{xp, yp, zp};
    } else {
      return Point3f0{xp/wp, yp/wp, zp/wp};
    }
  }

  Vec3f0 operator()(const Vec3f0& point) const {
    float x = point.x();
    float y = point.y();
    float z = point.z();
  
    float xp = m_[0][0]*x + m_[0][1]*y + m_[0][2]*z; 
    float yp = m_[1][0]*x + m_[1][1]*y + m_[1][2]*z; 
    float zp = m_[2][0]*x + m_[2][1]*y + m_[2][2]*z; 
    
    return Vec3f0{xp, yp, zp};
  }

  Normal3f0 operator()(const Normal3f0& point) const {
    float x = point.x();
    float y = point.y();
    float z = point.z();
  
    return Normal3f0 {
      minv_[0][0]*x + minv_[0][1]*y + minv_[0][2]*z,
      minv_[1][0]*x + minv_[1][1]*y + minv_[1][2]*z,
      minv_[2][0]*x + minv_[2][1]*y + minv_[2][2]*z, 
    };
  }

  Ray operator()(const Ray &ray) const {
    auto res = ray;
    res.origin_ = (*this)(ray.origin_);//apply transformation to point
    res.direction_ = (*this)(ray.direction_); //apply transformation to vector
    return res;
  }
  
  //composing transformations
  Transform operator*(const Transform& t2) const {
    return Transform{
      m_ * t2.m_,
      t2.minv_ * minv_ 
    };
  }

  [[nodiscard]] bool swap_handedness() const {
    float det =
        m_[0][0] * (m_[1][1] * m_[2][2] - m_[1][2] * m_[2][1]) -
        m_[0][1] * (m_[1][0] * m_[2][2] - m_[1][2] * m_[2][0]) +
        m_[0][2] * (m_[1][0] * m_[2][1] - m_[1][1] * m_[2][0]);
    return det < 0;
  }

  //to transform a bounding box, 
  //first transform all the points, to create a 
  //new bounding box, 
  //then successively expand the box as per the algorithm 
  //in the book.
  BoundingBox3Df0 operator()(const BoundingBox3Df0& box) const {
    Transform temp = *this;
    BoundingBox3Df0 out{temp(Point3f0{
      box.pmin_.x(),
      box.pmin_.y(),
      box.pmin_.z()
    })};

    out = point_union(out, temp(Point3f0{box.pmax_.x(), box.pmin_.y(), box.pmin_.z()}));
    out = point_union(out, temp(Point3f0{box.pmin_.x(), box.pmax_.y(), box.pmin_.z()}));
    out = point_union(out, temp(Point3f0{box.pmin_.x(), box.pmin_.y(), box.pmax_.z()}));
    out = point_union(out, temp(Point3f0{box.pmin_.x(), box.pmax_.y(), box.pmax_.z()}));
    out = point_union(out, temp(Point3f0{box.pmax_.x(), box.pmax_.y(), box.pmin_.z()}));
    out = point_union(out, temp(Point3f0{box.pmax_.x(), box.pmin_.y(), box.pmax_.z()}));
    out = point_union(out, temp(Point3f0{box.pmax_.x(), box.pmax_.y(), box.pmax_.z()}));
    return out;
  }


  
};
//probably not going to implement the Interaction 
//and SurfaceInteraction as 
//described in PBRT.




} // namespace geocold {


#endif
