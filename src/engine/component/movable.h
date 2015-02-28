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

  // Constructor + destructor.
  Movable(double speed=1.0);
  virtual ~Movable();

  // Update the parameter with key `key` to value `value`.
  virtual void SetParameter(const std::string& key, const Json::Value& value);

  // Update the component. This will change the X and Y value based on the
  // current X and Y velocity.
  virtual void Update(const thor::ActionMap<std::string>& map);

  // Build methods for creating a movable.
  Movable* speed(double speed);
  Movable* speed_multiplier(double speed_multiplier);

  // Getters for various member variables.
  sf::Vector2i& velocity();
  const sf::Vector2i& velocity() const;
  double speed() const;
  double speed_multiplier() const;

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
