#ifndef _ENGINE_COMPONENTS_MOVABLE_H_
#define _ENGINE_COMPONENTS_MOVABLE_H_

#include <SFML/System.hpp>

#include "engine/components/component.h"
#include "engine/components/drawable.h"
#include "engine/components/entity.h"
#include "logging/easylogging++.h"

// Movable components have an X and Y velocity. For something to be movable, it
// must also have an X and Y coordinate (i.e. be drawable).
class Movable : public Component {
public:
  Movable(int speed=1);
  virtual ~Movable();

  // Update this movable object (by changing it's X and Y location).
  virtual void Update();

  // Get access to the velocity.
  sf::Vector2i& Velocity() {
    return velocity_;
  }

protected:
  sf::Vector2i velocity_;
  int speed_;
};

#endif  // _ENGINE_COMPONENTS_MOVABLE_H_
