#include "jhm.h"

using engine::component::BlockMovement;
using engine::component::Directional;
using engine::component::Drawable;
using engine::component::Entity;
using engine::component::Movable;
using engine::component::Player;
using engine::component::Zone;

using engine::game::Map;

using thor::Action;

JHM::JHM() : running_(false), current_owner_(nullptr), video_mode_(1280, 800) {

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

    if (not Loop()) {
      continue;
    }

    Render();
  }

  // Shutdown the game.
  Stop();
}

void JHM::TakeOwnership(Entity* entity) {
  current_owner_ = entity;
}

void JHM::ReleaseOwnership() {
  current_owner_ = nullptr;
}

const sf::RenderWindow& JHM::window() const {
  return window_;
}

sf::RenderWindow& JHM::window() {
  return window_;
}

const thor::ActionMap<std::string>& JHM::action_map() const {
  return action_map_;
}

const sf::VideoMode& JHM::video_mode() const {
  return video_mode_;
}

void JHM::Setup() {
  LOG->trace("JHM::Setup");

  // Create the main view.
  window_.create(video_mode_, "Harvest Moon");
  window_.setVerticalSyncEnabled(true);
  sf::View view({0, 0, 1280, 800});
  view.zoom(0.5);
  window_.setView(view);
  window_.clear();

  // When the window is closed, stop running.
  action_map_["quit"] = thor::Action(sf::Event::Closed);

  // Define controls.
  action_map_["moving_up"] = Action(sf::Keyboard::Up, Action::Hold);
  action_map_["moving_down"] = Action(sf::Keyboard::Down, Action::Hold);
  action_map_["moving_right"] = Action(sf::Keyboard::Right, Action::Hold);
  action_map_["moving_left"] = Action(sf::Keyboard::Left, Action::Hold);

  action_map_["up"] = Action(sf::Keyboard::Up, Action::PressOnce);
  action_map_["down"] = Action(sf::Keyboard::Down, Action::PressOnce);
  action_map_["right"] = Action(sf::Keyboard::Right, Action::PressOnce);
  action_map_["left"] = Action(sf::Keyboard::Left, Action::PressOnce);

  action_map_["running"] = Action(sf::Keyboard::Space, Action::Hold);
  action_map_["interact"] = Action(sf::Keyboard::E);
  action_map_["back"] = Action(sf::Keyboard::Escape);

  // Load the world information.
  engine::game::World::Load("maps/fomt/world.dat");

  // Load the map.
  engine::game::Loader::LoadMap("maps/fomt/farm.map");
  engine::game::Loader::LoadMap("maps/fomt/farm-house.map");
  engine::game::Loader::LoadSave("maps/fomt/player.save");

  LOG->trace("done JHM::Setup");
}

void JHM::ProcessEvents() {
  action_map_.clearEvents();
  action_map_.update(window_);
}

bool JHM::Loop() {
  LOG->trace("JHM::Loop");

  if (not current_owner_) {
    for (Entity* entity : Map::GetActive().entities()) {
      if (not entity->Update(*this)) {
        return false;
      }
    }
  }

  // If we have to quit, then do so.
  if (action_map_.isActive("quit")) {
    running_ = false;
  }

  LOG->trace("Done JHM::Loop");
  return true;
}

void JHM::Render() {
  LOG->trace("JHM::Render");

  window_.clear();

  // Update the view to match the player.
  if (not current_owner_) {
    for (const Entity* entity :
          Map::GetActive().GetEntitiesWithComponent<Player>()) {
      sf::View view = window_.getView();
      view.setCenter(entity->GetComponent<Drawable>().sprite().getPosition());
      window_.setView(view);
    }
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

  // Update the current owner.
  if (current_owner_) {
    current_owner_->Update(*this);
  }

  // Render all debugging zones.
  for (const Entity* entity :
        Map::GetActive().GetEntitiesWithComponent<Zone>()) {
    const Zone& zone = entity->GetComponent<Zone>();
    if (zone.debug()) {
      const sf::FloatRect area = zone.area();
      sf::RectangleShape shape({area.width, area.height});
      shape.setPosition({area.left, area.top});
      shape.setOutlineThickness(1);
      shape.setOutlineColor(sf::Color::Red);
      shape.setFillColor(sf::Color::Transparent);
      window_.draw(shape);
    }
  }

  // Display the window.
  window_.display();

  LOG->trace("Done JHM::Render");
}

void JHM::Stop() {
  window_.close();
}
