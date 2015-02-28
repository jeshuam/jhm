#include "jhm.h"

using engine::component::BlockMovement;
using engine::component::Directional;
using engine::component::Drawable;
using engine::component::Entity;
using engine::component::Movable;
using engine::component::Player;

JHM::JHM() : running_(false) {

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

  // Create the main view.
  window_.create(sf::VideoMode(800, 600), "Harvest Moon");
  window_.clear();
  window_.setView(sf::View(sf::FloatRect(0, 0, 800, 600)));

  // When the window is closed, stop running.
  action_map_["quit"] = thor::Action(sf::Event::Closed);

  // Load the map.
  LOG->info("Loading map...");
  engine::game::Loader::LoadMap("../maps/fomt/farm.map");
  LOG->info("Done!");

  // Create the main character.
  LOG->info("Creating main character...");
  new Entity({
    (new Drawable("../maps/fomt/assets/main-character.png", {7, 26}, {19, 29}))
      ->z_index(10000)
      ->location({200.0, 200.0})
      ->scale(2)
      ->hit_box({0, 28}),
    new Movable(4),
    new Player(action_map_, 4)
  });
  LOG->info("Done!");

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

  // Update the view to match the player.
  for (const Entity* entity : Entity::GetEntitiesWithComponent<Player>()) {
    sf::View view = window_.getView();
    view.setCenter(entity->GetComponent<Drawable>().Sprite().getPosition());
    window_.setView(view);
  }

  // Render all rendable objects.
  std::vector<Entity*> entities = Entity::GetEntitiesWithComponent<Drawable>();
  std::sort(entities.begin(), entities.end(), [](Entity* a, Entity* b) {
    return a->GetComponent<Drawable>().z_index() <
           b->GetComponent<Drawable>().z_index();
  });

  for (const Entity* entity : entities) {
    entity->GetComponent<Drawable>().Draw(window_);
  }

  // Display the window.
  window_.display();

  LOG->trace("Done JHM::Render");
}

void JHM::Stop() {
  window_.close();
}
