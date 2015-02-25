#ifndef _ENGINE_COMPONENTS_PLAYER_H_
#define _ENGINE_COMPONENTS_PLAYER_H_

#include <SFML/Window.hpp>

#include "engine/component/component.h"
#include "engine/component/movable.h"

namespace engine {
namespace component {

// A component which allows a player to take control of an entity. The entity
// must be drawable and movable.
class Player : public Component {
public:
  Player();
  virtual ~Player();

  // The player just responds to keypresses.
  virtual void KeyPressed(const sf::Event& event);
};

}}  // namepsace engine::component

#endif  // _ENGINE_COMPONENTS_PLAYER_H_
