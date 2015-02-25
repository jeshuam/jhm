#ifndef _ENGINE_ENTITY_DRAWABLE_H_
#define _ENGINE_ENTITY_DRAWABLE_H_

#include <SFML/Window.hpp>

#include "entity.h"

//
// Classes that inherit from this must contain a Draw method for drawing to the
// display.
//
class Drawable : public Entity {
public:
  //
  // Draw this object to the screen at its current location.
  //
  virtual void Draw(sf::RenderWindow& window) const = 0;
};

#endif  // _ENGINE_ENTITY_DRAWABLE_H_
