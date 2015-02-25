#ifndef _ENGINE_COMPONENT_DIRECTIONAL_H_
#define _ENGINE_COMPONENT_DIRECTIONAL_H_

#include <array>
#include <vector>

#include <SFML/Graphics.hpp>
#include <Thor/Animations.hpp>

#include "logging/easylogging++.h"

#include "engine/component/component.h"
#include "engine/component/drawable.h"
#include "engine/component/entity.h"

namespace engine {
namespace component {

// Directional objects can face in a specific direction. This is essentially a
// container for different rectangle locations within a sprite map that
// correspond to different directions. Directional objects must also be
// drawable and movable. Multiple frames can be selected for each direction to
// show that moving in that direction is animatable.
class Directional : public Component {
public:
  enum Direction {
    UP, DOWN, LEFT, RIGHT
  };

  Directional();
  virtual ~Directional();

  // Method for adding directions to the directional object.
  Directional& AddDirection(
    Direction direction, sf::Time length,
    const std::vector<std::pair<sf::Vector2i, double>>& frames);

  // Update the directional object.
  virtual void Update(const thor::ActionMap<std::string>& map);

  // Methods for moving in a particular direction.
  void MoveUp();
  void MoveDown();
  void MoveLeft();
  void MoveRight();

protected:
  // Thor animation manager.
  thor::Animator<sf::Sprite, Direction> animator_;
  Direction current_direction_;
  sf::Clock clock_;

  // Change the direction this object is facing.
  void ChangeDirection(Direction direction);
};

}}  // namepsace engine::component

#endif  // _ENGINE_COMPONENT_DIRECTIONAL_H_
