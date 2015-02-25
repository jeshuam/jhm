#include "jhm.h"

using engine::component::Directional;
using engine::component::Drawable;
using engine::component::Entity;
using engine::component::Movable;
using engine::component::Player;

JHM::JHM() : running_(false), window_(sf::VideoMode(800, 600), "JHM") {

}

JHM::~JHM() {

}

void JHM::Run() {
  // Setup the game.
  Setup();

  // While the game is running...
  running_ = true;
  while (running_) {
    ProcessEvents();

    if (last_loop_run_clock_.getElapsedTime().asMilliseconds() > 100) {
      Loop();
      Render();

      last_loop_run_clock_.restart();
    }
  }

  // Shutdown the game.
  Stop();
}

void JHM::Setup() {
  // Setup the window.
  window_.setKeyRepeatEnabled(false);

  // Clear the screen.
  window_.clear();

  // Create the main character.
  new Entity({
    new Drawable("../assets/character.png", {0, 0}, {32, 48}),
    new Movable(10),
    new Player(),
    new Directional(
      {{0, 144}, {32, 144}, {64, 144}, {96, 144}},
      {{0,   0}, {32,   0}, {64,   0}, {96,   0}},
      {{0,  48}, {32,  48}, {64,  48}, {96,  48}},
      {{0,  96}, {32,  96}, {64,  96}, {96,  96}}
    ),
  });
}

void JHM::ProcessEvents() {
  sf::Event event;
  while (window_.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed:
        running_ = false;
        break;

      case sf::Event::KeyPressed:
      case sf::Event::KeyReleased:
        for (Entity* entity : Entity::GetEntitiesWithComponent<Player>()) {
          entity->GetComponent<Player>().KeyPressed(event);
        }

        break;

      default:
        break;
    }
  }
}

void JHM::Loop() {
  for (Entity* entity : Entity::GetEntitiesWithComponent<Movable>()) {
    entity->GetComponent<Movable>().Update();
  }
}

void JHM::Render() {
  window_.clear();

  // Render all rendable objects.
  for (const Entity* entity : Entity::GetEntitiesWithComponent<Drawable>()) {
    entity->GetComponent<Drawable>().Draw(window_);
  }

  // Display the window.
  window_.display();
}

void JHM::Stop() {

}
