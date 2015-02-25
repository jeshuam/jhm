#include "jhm.h"

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

    if (last_loop_run_clock_.getElapsedTime().asMilliseconds() > 32.0) {
      Loop();
      Render();

      last_loop_run_clock_.restart();
    }
  }

  // Shutdown the game.
  Stop();
}

void JHM::Setup() {
  // Clear the screen.
  window_.clear();

  // Create the main character.
  player_ = Character("../assets/character.png", 0, 0, 32, 48);
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
        for (Controllable* entity : Entity::GetEntitiesOfType<Controllable>()) {
          entity->KeyPressed(event);
        }

        break;

      default:
        break;
    }
  }
}

void JHM::Loop() {
  for (Entity* entity : Entity::GetEntitiesOfType<Entity>()) {
    entity->Update();
  }
}

void JHM::Render() {
  window_.clear();

  // Render all rendable objects.
  for (const Drawable* entity : Entity::GetEntitiesOfType<Drawable>()) {
    entity->Draw(window_);
  }

  // Display the window.
  window_.display();
}

void JHM::Stop() {

}
