#ifndef _JHM_H_
#define _JHM_H_

#include <SFML/Graphics.hpp>

#include "engine/components/drawable.h"
#include "engine/components/entity.h"
#include "engine/components/movable.h"
#include "engine/components/player.h"

class JHM {
public:
  JHM();
  ~JHM();

  // Run the game.
  void Run();

private:
  // Setup the game (create the window, load the assets, etc.).
  void Setup();

  // Process events in the queue.
  void ProcessEvents();

  // Run any loop events.
  void Loop();

  // Render things to the screen.
  void Render();

  // Shutdown the game (save, release assets, etc.).
  void Stop();

  // True if the game is running or not.
  bool running_;

  // This is the last time the main loop was run.
  sf::Clock last_loop_run_clock_;

  // Main game window.
  sf::RenderWindow window_;
};

#endif  // _JHM_H_
