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
  LOG->trace("JHM::Setup");

  // Clear the screen.
  window_.clear();

  // When the window is closed, stop running.
  action_map_["quit"] = thor::Action(sf::Event::Closed);

  // Create the main character.
  new Entity({
    new Drawable("../assets/main-character.png", {7, 26}, {19, 29}, 2),
    new Movable(2.5),
    new Player(action_map_, 2)
  });

  LOG->trace("done JHM::Setup");
}

void JHM::ProcessEvents() {
  action_map_.update(window_);
}

void JHM::Loop() {
  LOG->trace("JHM::Loop");

  for (Entity* entity : Entity::GetAllEntities()) {
    entity->Update(action_map_);
  }

  // If we have to quit, then do so.
  if (action_map_.isActive("quit")) {
    running_ = false;
  }

  LOG->trace("Done JHM::Loop");
}

void JHM::Render() {
  LOG->trace("JHM::Render");

  window_.clear();

  // Render all rendable objects.
  for (const Entity* entity : Entity::GetEntitiesWithComponent<Drawable>()) {
    entity->GetComponent<Drawable>().Draw(window_);
  }

  // Display the window.
  window_.display();

  LOG->trace("Done JHM::Render");
}

void JHM::Stop() {
  window_.close();
}
