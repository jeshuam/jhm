#ifndef _GAME_H_
#define _GAME_H_

#include <SFML/Graphics.hpp>
#include <Thor/Input/ActionMap.hpp>

#include "log.h"

namespace engine {
namespace component {

class Entity;

}} // namespace engine::component

// Abstract 'game' class to make engine code a bit nicer.
class Game {
public:
  // An entity may call this to take temporary ownership of the game. All other
  // updating of entities will stop while this entity has ownership; they will
  // still be drawn to the screen, however. The entity can use this to display
  // messages or menus etc. The update method for this entity will be called
  // after everything has been rendered. It can even take control of the view
  // (as this will no longer be updated either).
  virtual void TakeOwnership(engine::component::Entity* entity) = 0;

  // Release a previously taken ownership.
  virtual void ReleaseOwnership() = 0;

  // Getters.
  virtual const sf::RenderWindow& window() const = 0;
  virtual sf::RenderWindow& window() = 0;
  virtual const thor::ActionMap<std::string>& action_map() const = 0;
};

#endif  // _GAME_H_
