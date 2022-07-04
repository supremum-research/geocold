
#ifndef GEOCOLD_INCLUDE_BOUNDING_BOXES_HPP 
#define GEOCOLD_INCLUDE_BOUNDING_BOXES_HPP 

#include <memory>


#include "common.hpp"
#include "shape.hpp"
#include "point.hpp"
#include "vec3.hpp"
#include "normal.hpp"

namespace geocold {

struct LocalDiffGeo {
  Point3f0 point; //point where the surface was hit. 3 * 32
  Normal3f0 gnorm; //geometric normal form PBRT 3 * 32
  Normal3f0 snorm; //shading normal from PBRT 3 * 32
  
  float u; //for texture mapping, surface parametrizations 32
  float v; //32

  float time; //32 //all interactions have a time associated with them, intersection time

  Vec3f0 dpdu; //3*32
  Vec3f0 dpdv; //3*32
  std::shared_ptr<Shape> shape; //64
 
  LocalDiffGeo() = default;

  LocalDiffGeo(
      Point3f0 p_,
      Normal3f0 ng,
      float u_,
      float v_,
      float time_,
      Vec3f0 dpdu_,
      Vec3f0 dpdv_,
      std::shared_ptr<Shape> shape_
      ) 
    :point{p_}
    ,gnorm{ng.normalize()}
    ,snorm{cross_product(dpdu_, dpdv_)}
    ,u{u_}
    ,v{v_}
    ,time{time_}
    ,dpdu{dpdu_}
    ,dpdv{dpdv_}
    ,shape{shape_}
  {}

  LocalDiffGeo(
      Point3f0 p_,
      Normal3f0 ng,
      Normal3f0 ns,
      float u_,
      float v_,
      float time_,
      Vec3f0 dpdu_,
      Vec3f0 dpdv_,
      std::shared_ptr<Shape> shape_
      ) 
    :point{p_}
    ,gnorm{ng.normalize()}
    ,snorm{ns.normalize()}
    ,u{u_}
    ,v{v_}
    ,time{time_}
    ,dpdu{dpdu_}
    ,dpdv{dpdv_}
    ,shape{std::move(shape_)}
  {}


  
};


} //namespace geocold



#endif
