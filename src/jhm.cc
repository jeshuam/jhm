#include "jhm.h"

using engine::component::BlockMovement;
using engine::component::Directional;
using engine::component::Drawable;
using engine::component::Entity;
using engine::component::Movable;
using engine::component::Player;

using engine::game::Map;

using thor::Action;

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

  // Define controls.
  action_map_["moving_up"] = Action(sf::Keyboard::Up, Action::Hold);
  action_map_["moving_down"] = Action(sf::Keyboard::Down, Action::Hold);
  action_map_["moving_right"] = Action(sf::Keyboard::Right, Action::Hold);
  action_map_["moving_left"] = Action(sf::Keyboard::Left, Action::Hold);
  action_map_["running"] = Action(sf::Keyboard::Space, Action::Hold);

  // Load the map.
  engine::game::Loader::LoadMap("../maps/fomt/farm.map");
  engine::game::Loader::LoadMap("../maps/fomt/farm-house.map");
  engine::game::Loader::LoadSave("../maps/fomt/player.save");

  LOG->trace("done JHM::Setup");
}

void JHM::ProcessEvents() {
  action_map_.update(window_);
}

void JHM::Loop() {
  LOG->trace("JHM::Loop");

  for (Entity* entity : Map::GetActive().entities()) {
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
  for (const Entity* entity :
        Map::GetActive().GetEntitiesWithComponent<Player>()) {
    sf::View view = window_.getView();
    view.setCenter(entity->GetComponent<Drawable>().sprite().getPosition());
    window_.setView(view);
  }

  // Render all rendable objects.
  std::vector<Entity*> entities =
      Map::GetActive().GetEntitiesWithComponent<Drawable>();
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
