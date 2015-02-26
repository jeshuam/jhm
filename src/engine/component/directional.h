#ifndef _ENGINE_COMPONENT_DIRECTIONAL_H_
#define _ENGINE_COMPONENT_DIRECTIONAL_H_

#include <array>
#include <vector>

#include <SFML/Graphics.hpp>
#include <Thor/Animations.hpp>

#include "engine/component/component.h"
#include "engine/component/drawable.h"
#include "engine/component/entity.h"
#include "log.h"

namespace engine {
namespace component {

// Directional objects can face in a specific direction. This is essentially a
// container for different rectangle locations within a sprite map that
// correspond to different directions. Directional objects must also be
// drawable and movable. Multiple frames can be selected for each direction to
// show that moving in that direction is animatable.
class Directional : public Component {
public:
  COMPONENT_KEY("DIRECTIONAL");

  // Directional objects can 'face' a specific direction. They also have an
  // animation that will play if they are moving in that direction.
  enum Direction {
    UP, DOWN, LEFT, RIGHT
  };

  // Constructor + Destructor.
  Directional();
  virtual ~Directional();

  // Update this component.
  virtual void Update(const thor::ActionMap<std::string>& map);

  // Add an animation for a specific direction of some total length.
  Directional* AddDirection(
    Direction direction, sf::Time length,
    const std::vector<std::pair<sf::IntRect, double>>& frames);

  // Change the direction this object is facing.
  void ChangeDirection(Direction direction);

protected:
  // Thor animation manager.
  thor::Animator<sf::Sprite, Direction> animator_;
  Direction current_direction_;
  sf::Clock clock_;
};

}}  // namepsace engine::component

#endif  // _ENGINE_COMPONENT_DIRECTIONAL_H_
