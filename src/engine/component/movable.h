#ifndef _ENGINE_COMPONENT_MOVABLE_H_
#define _ENGINE_COMPONENT_MOVABLE_H_

#include <SFML/System.hpp>

#include "engine/component/block_movement.h"
#include "engine/component/component.h"
#include "engine/component/directional.h"
#include "engine/component/drawable.h"
#include "engine/component/entity.h"
#include "log.h"

namespace engine {
namespace component {

// Movable components have an X and Y velocity. For something to be movable, it
// must also have an X and Y coordinate (i.e. be drawable).
class Movable : public Component {
public:
  COMPONENT_KEY("MOVABLE");

  Movable(double speed=1.0);
  virtual ~Movable();

  // Update the component. This will change the X and Y value based on the
  // current X and Y velocity.
  virtual void Update(const thor::ActionMap<std::string>& map);

  // Get access to the velocity.
  sf::Vector2i& Velocity() {
    return velocity_;
  }

  // Set the speed multiplier. This can be used to modify the effective speed at
  // runtime (e.g. a running person).
  void SpeedMultiplier(double speed_multiplier) {
    speed_multiplier_ = speed_multiplier;
  }

protected:
  // The X and Y velocity (usually -1, 0 or 1).
  sf::Vector2i velocity_;

  // Control the overall speed of the entity.
  double speed_;
  double speed_multiplier_;

  // Only update movable objects every x milliseconds.
  static const int kUpdateFrequencyMs = 20;
  sf::Clock clock_;
};

}}  // namepsace engine::component

#endif  // _ENGINE_COMPONENT_MOVABLE_H_
