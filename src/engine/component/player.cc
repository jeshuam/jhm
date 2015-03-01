#include "player.h"

namespace engine {
namespace component {

Player::Player() : running_multiplier_(1)
                 , walking_directional_(new Directional())
                 , running_directional_(new Directional()) {
  
}

Player::~Player() {

}

void Player::Bind(Entity* entity) {
  Component::Bind(entity);

  walking_directional_->Bind(entity);
  running_directional_->Bind(entity);
  entity->AddComponent(walking_directional_);
}

void Player::SetParameter(const std::string& key, const Json::Value& value) {
  if (key == "walking_directional") {
    for (const std::string& key : value.getMemberNames()) {
      walking_directional_->SetParameter(key, value[key]);
    }
  }

  else if (key == "running_directional") {
    for (const std::string& key : value.getMemberNames()) {
      running_directional_->SetParameter(key, value[key]);
    }
  }

  else if (key == "running_multiplier") {
    running_multiplier(value.asDouble());
  }
}

bool Player::Update(const thor::ActionMap<std::string>& map) {
  LOG->trace("Player::Update");

  // Get a reference to the Movable component.
  if (not entity_->HasComponent<Movable>()) {
    LOG->emerg("Player entity does not have required Movable component.");
  }

  if (not entity_->HasComponent<Directional>()) {
    LOG->emerg("Player entity does not have required Directional component.");
  }

  // Get a reference to the velocity vector.
  Movable& movable = entity_->GetComponent<Movable>();
  sf::Vector2i& velocity = movable.velocity();

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
    // Update the speed multiplier.
    movable.speed_multiplier(running_multiplier_);

    // Change the sprite.
    entity_->ReplaceComponent<Directional>(running_directional_);
  } else {
    // Update the speed multiplier.
    movable.speed_multiplier(1);

    // Change the sprite.
    entity_->ReplaceComponent<Directional>(walking_directional_);
  }

  LOG->trace("Done Player::Update");
  return true;
}

Player* Player::running_multiplier(double running_multiplier) {
  running_multiplier_ = running_multiplier;
  return this;
}

Player* Player::walking_directional(Directional* walking_directional) {
  walking_directional_ = walking_directional;
  walking_directional_->Bind(entity_);
  entity_->AddComponent(walking_directional_);
  return this;
}

Player* Player::running_directional(Directional* running_directional) {
  running_directional_ = running_directional;
  running_directional_->Bind(entity_);
  entity_->AddComponent(running_directional_);
  return this;
}

double Player::running_multiplier() const {
  return running_multiplier_;
}

}}  // namepsace engine::component
