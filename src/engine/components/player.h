#ifndef _ENGINE_COMPONENTS_PLAYER_H_
#define _ENGINE_COMPONENTS_PLAYER_H_

#include <SFML/Window.hpp>

#include "engine/components/component.h"
#include "engine/components/movable.h"

// A component which allows a player to take control of an entity. The entity
// must be drawable and movable.
class Player : public Component {
public:
  Player();
  virtual ~Player();

  // The player just responds to keypresses.
  virtual void KeyPressed(const sf::Event& event);
};

#endif  // _ENGINE_COMPONENTS_PLAYER_H_
