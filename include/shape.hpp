
#ifndef GEOCOLD_INCLUDE_OBJ_LOADER_HPP 
#define GEOCOLD_INCLUDE_OBJ_LOADER_HPP 

#include <vector>
#include <memory>


#include "definitions.hpp"
#include "transform.hpp"
#include "localdiffgeo.hpp"

//all shapes are defined in object coordinate space
//all spheres are defined with origin at the 
//center of the sphere
//to place an object at another place in the 
//scene, a transformation ought to be provided
//Shape defines this transformation 
//as well as the inverse transform
namespace geocold {

struct Shape {
  std::shared_ptr<Transform> object2world;
  std::shared_ptr<Transform> world2object;
  const bool reverse_orientation;
  const bool transform_swap_handedness;

  Shape(
      Transform* object_to_world,
      Transform* world_to_object,
      bool reverseorientation
    );

  [[nodiscard]] virtual float area() const = 0;

  virtual LocalDiffGeo sample(const LocalDiffGeo& interaction, const Point3f0 point, float* pdf);

  virtual float solid_angle(const Point3f &p, int nSamples = 512) const;
  [[nodiscard]] virtual BoundingBox3Df0 object_bound() const = 0;

  [[nodiscard]] BoundingBox3Df0 world_bound() const;

   
};



} //namespace geocold


#endif
