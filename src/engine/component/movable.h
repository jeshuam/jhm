#ifndef _ENGINE_COMPONENTS_MOVABLE_H_
#define _ENGINE_COMPONENTS_MOVABLE_H_

#include <SFML/System.hpp>

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
  Movable(double speed=1.0);
  virtual ~Movable();

  // Update this movable object (by changing it's X and Y location).
  virtual void Update(const thor::ActionMap<std::string>& map);

  // Get access to the velocity.
  sf::Vector2i& Velocity() {
    return velocity_;
  }

  // Set the speed multiplier.
  void SpeedMultiplier(double speed_multiplier) {
    speed_multiplier_ = speed_multiplier;
  }

  static const std::string& name_() {
    static const std::string name = "MOVABLE";
    return name;
  }

  virtual const std::string& name() {
    return name_();
  }

protected:
  sf::Vector2i velocity_;
  double speed_;
  double speed_multiplier_;
  sf::Clock clock_;
};

}}  // namepsace engine::component

#endif  // _ENGINE_COMPONENTS_MOVABLE_H_
