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
    Loop();
    Render();
  }

  // Shutdown the game.
  Stop();
}

void JHM::Setup() {
  // Clear the screen.
  window_.clear();

  // When the window is closed, stop running.
  action_map_["quit"] = thor::Action(sf::Event::Closed);

  // Create the main character.
  Entity* main_character = new Entity({
    new Drawable("../assets/character.png", {0, 0}, {32, 48}, 2),
    new Movable(2.5),
    new Player(action_map_, 2),
    new Directional()
  });

  main_character->GetComponent<Directional>()
      .AddDirection(Directional::UP, sf::seconds(1.0),
                    {{{ 0, 144}, 2},
                     {{32, 144}, 2},
                     {{64, 144}, 2},
                     {{96, 144}, 2}})
      .AddDirection(Directional::DOWN, sf::seconds(1.0),
                    {{{ 0,   0}, 2},
                     {{32,   0}, 2},
                     {{64,   0}, 2},
                     {{96,   0}, 2}})
      .AddDirection(Directional::LEFT, sf::seconds(1.0),
                    {{{ 0,  48}, 2},
                     {{32,  48}, 2},
                     {{64,  48}, 2},
                     {{96,  48}, 2}})
      .AddDirection(Directional::RIGHT, sf::seconds(1.0),
                    {{{ 0,  96}, 2},
                     {{32,  96}, 2},
                     {{64,  96}, 2},
                     {{96,  96}, 2}});
}

void JHM::ProcessEvents() {
  action_map_.update(window_);
}

void JHM::Loop() {
  for (Entity* entity : Entity::GetAllEntities()) {
    entity->Update(action_map_);
  }

  // If we have to quit, then do so.
  if (action_map_.isActive("quit")) {
    running_ = false;
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
  window_.close();
}
