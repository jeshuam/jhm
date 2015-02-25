#ifndef _ENGINE_COMPONENT_DIRECTIONAL_H_
#define _ENGINE_COMPONENT_DIRECTIONAL_H_

#include <array>
#include <vector>

#include <SFML/Graphics.hpp>

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
    UP=0, DOWN=1, LEFT=2, RIGHT=3
  };

  Directional();
  Directional(std::vector<sf::Vector2i> up, std::vector<sf::Vector2i> down,
              std::vector<sf::Vector2i> left, std::vector<sf::Vector2i> right);
  virtual ~Directional();

  // Update the directional object.
  virtual void Update();

  // Methods for moving in a particular direction.
  void MoveUp();
  void MoveDown();
  void MoveLeft();
  void MoveRight();

protected:
  // Array of directions --> animation frames.
  std::array<std::vector<sf::Vector2i>, 4> directions_;

  // Current frame through the animation.
  Direction current_direction_;
  int current_frame_;

  // Change the direction this object is facing.
  void ChangeDirection(Direction direction);

  // Get the next frame for the given direction.
  const sf::Vector2i& GetFrame(int frame_id);
  const sf::Vector2i& GetNextFrame();

  // Update the current frame.
  void UpdateFrame(const sf::Vector2i& frame);
};

}}  // namepsace engine::component

#endif  // _ENGINE_COMPONENT_DIRECTIONAL_H_
