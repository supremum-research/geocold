
#include "shape.hpp"


namespace geocold{


Shape::Shape(Transform* object_to_world, Transform* world_to_object, bool reverseorientation)
    :object2world{std::shared_ptr<Transform>(object_to_world)}
    ,world2object{std::shared_ptr<Transform>(world_to_object)}
    ,reverse_orientation{reverseorientation}
    ,transform_swap_handedness{object2world->swap_handedness()}
  {}


//world_bound returns a bounding box in 
//world space
//So, convert the object_bound to world space through the 
//object2world transform
[[nodiscard]] BoundingBox3Df0 Shape::world_bound() const {
    return (*object2world)(object_bound());
}



} //namespace geocold

