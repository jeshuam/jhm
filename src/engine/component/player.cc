#include "player.h"

namespace engine {
namespace component {

Player::Player(thor::ActionMap<std::string>& map) {
  map["moving_up"] = thor::Action(sf::Keyboard::Up, thor::Action::Hold);
  map["moving_down"] = thor::Action(sf::Keyboard::Down, thor::Action::Hold);
  map["moving_right"] = thor::Action(sf::Keyboard::Right, thor::Action::Hold);
  map["moving_left"] = thor::Action(sf::Keyboard::Left, thor::Action::Hold);
  map["running"] = thor::Action(sf::Keyboard::S, thor::Action::Hold);
}

Player::~Player() {

}

void Player::Update(const thor::ActionMap<std::string>& map) {
  // Get a reference to the Movable component.
  if (not parent_->HasComponent<Movable>()) {
    LOG(FATAL) << "Player entity does not have required Movable component.";
  }

  // Get a reference to the velocity vector.
  Movable& movable = parent_->GetComponent<Movable>();
  sf::Vector2i& velocity = movable.Velocity();

  // Determine the Y velocity.
  if (map.isActive("moving_up") and not map.isActive("moving_down")) {
    velocity.y = 1;
  }

  else if (map.isActive("moving_down") and not map.isActive("moving_up")) {
    velocity.y = -1;
  }

  else {
    velocity.y = 0;
  }

  // Determine the X velocity.
  if (map.isActive("moving_right") and not map.isActive("moving_left")) {
    velocity.x = 1;
  }

  else if (map.isActive("moving_left") and not map.isActive("moving_right")) {
    velocity.x = -1;
  }

  else {
    velocity.x = 0;
  }

  // If the player is running...
  if (map.isActive("running")) {
    movable.SpeedMultiplier(10);
  } else {
    movable.SpeedMultiplier(1);
  }
}

}}  // namepsace engine::component
