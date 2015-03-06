#ifndef _JHM_H_
#define _JHM_H_

#include <algorithm>

#include <SFML/Graphics.hpp>
#include <Thor/Input/Action.hpp>
#include <Thor/Input/ActionMap.hpp>

#include "engine/component/block_movement.h"
#include "engine/component/drawable.h"
#include "engine/component/directional.h"
#include "engine/component/entity.h"
#include "engine/component/movable.h"
#include "engine/component/player.h"
#include "engine/game/map.h"
#include "engine/game/loader.h"
#include "log.h"

class JHM {
public:
  JHM();
  ~JHM();

  // Run the game.
  void Run();

  // An entity may call this to take temporary ownership of the game. All other
  // updating of entities will stop while this entity has ownership; they will
  // still be drawn to the screen, however. The entity can use this to display
  // messages or menus etc. The update method for this entity will be called
  // after everything has been rendered. It can even take control of the view
  // (as this will no longer be updated either).
  void TakeOwnership(engine::component::Entity* entity);

  // Release a previously taken ownership.
  void ReleaseOwnership();

  // Getters.
  const sf::RenderWindow& window() const;
  sf::RenderWindow& window();
  const thor::ActionMap<std::string>& action_map() const;

private:
  // Setup the game (create the window, load the assets, etc.).
  void Setup();

  // Process events in the queue.
  void ProcessEvents();

  // Run any loop events.
  bool Loop();

  // Render things to the screen.
  void Render();

  // Shutdown the game (save, release assets, etc.).
  void Stop();

  // True if the game is running or not.
  bool running_;

  // The entity that has taken ownership of the game.
  engine::component::Entity* current_owner_;

  // Main game window.
  sf::RenderWindow window_;
  thor::ActionMap<std::string> action_map_;
};

#endif  // _JHM_H_
