#include "player.h"

namespace engine {
namespace component {

Player::Player(thor::ActionMap<std::string>& map, double running_multiplier)
    : running_multiplier_(running_multiplier) {
  map["moving_up"] = thor::Action(sf::Keyboard::Up, thor::Action::Hold);
  map["moving_down"] = thor::Action(sf::Keyboard::Down, thor::Action::Hold);
  map["moving_right"] = thor::Action(sf::Keyboard::Right, thor::Action::Hold);
  map["moving_left"] = thor::Action(sf::Keyboard::Left, thor::Action::Hold);
  map["running"] = thor::Action(sf::Keyboard::Space, thor::Action::Hold);

  walking_directional_ = (new Directional())
      ->AddDirection(Directional::UP, sf::seconds(1.0),
                    {{{ 95, 25, 19, 30}, 2},
                     {{117, 26, 18, 29}, 2},
                     {{137, 25, 19, 30}, 2},
                     {{159, 26, 18, 29}, 2}})
      ->AddDirection(Directional::DOWN, sf::seconds(1.0),
                    {{{ 7, 26, 19, 29}, 2},
                     {{29, 27, 18, 28}, 2},
                     {{50, 26, 19, 29}, 2},
                     {{72, 27, 17, 28}, 2}})
      ->AddDirection(Directional::LEFT, sf::seconds(1.0),
                    {{{22 + 182, 26, -22, 29}, 2},
                     {{22 + 206, 27, -22, 28}, 2},
                     {{22 + 232, 26, -22, 29}, 2},
                     {{23 + 257, 27, -23, 28}, 2}})
      ->AddDirection(Directional::RIGHT, sf::seconds(1.0),
                    {{{182, 26, 22, 29}, 2},
                     {{206, 27, 22, 28}, 2},
                     {{232, 26, 22, 29}, 2},
                     {{257, 27, 23, 28}, 2}});

  running_directional_ = (new Directional())
      ->AddDirection(Directional::UP, sf::seconds(1.0),
                    {{{ 77, 76, 17, 29}, 2},
                     {{98, 76, 17, 29}, 2},
                     {{120, 76, 17, 29}, 2}})
      ->AddDirection(Directional::DOWN, sf::seconds(1.0),
                    {{{5, 77, 17, 27}, 2},
                     {{26, 75, 19, 28}, 2},
                     {{50, 77, 16, 27}, 2}})
      ->AddDirection(Directional::LEFT, sf::seconds(1.0),
                    {{{142, 77, 24, 26}, 2},
                     {{169, 74, 22, 29}, 2},
                     {{196, 77, 24, 26}, 2}})
      ->AddDirection(Directional::RIGHT, sf::seconds(1.0),
                    {{{24 + 142, 77, -24, 26}, 2},
                     {{22 + 169, 74, -22, 29}, 2},
                     {{24 + 196, 77, -24, 26}, 2}});
}

Player::~Player() {

}

void Player::Bind(Entity* parent) {
  Component::Bind(parent);

  walking_directional_->Bind(parent);
  running_directional_->Bind(parent);
  parent_->AddComponent(walking_directional_);
}

void Player::Update(const thor::ActionMap<std::string>& map) {
  LOG->trace("Player::Update");

  // Get a reference to the Movable component.
  if (not parent_->HasComponent<Movable>()) {
    LOG->emerg("Player entity does not have required Movable component.");
  }

  if (not parent_->HasComponent<Directional>()) {
    LOG->emerg("Player entity does not have required Directional component.");
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
    // Update the speed multiplier.
    movable.SpeedMultiplier(running_multiplier_);

    // Change the sprite.
    parent_->ReplaceComponent<Directional>(running_directional_);
  } else {
    // Update the speed multiplier.
    movable.SpeedMultiplier(1);

    // Change the sprite.
    parent_->ReplaceComponent<Directional>(walking_directional_);
  }

  LOG->trace("Done Player::Update");
}

}}  // namepsace engine::component
