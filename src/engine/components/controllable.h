#ifndef _ENGINE_ENTITY_CONTROLLABLE_H_
#define _ENGINE_ENTITY_CONTROLLABLE_H_

#include <SFML/Window.hpp>

#include "entity.h"

class Controllable : public Entity {
public:
  virtual void KeyPressed(const sf::Event& event) = 0;
};

#endif  // _ENGINE_ENTITY_CONTROLLABLE_H_
