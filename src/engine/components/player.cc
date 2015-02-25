#include "player.h"

Player::Player() {

}

Player::~Player() {

}

void Player::KeyPressed(const sf::Event& event) {
  // Get a reference to the Movable component.
  try {
    parent_->GetComponent<Movable>();
  } catch (std::logic_error& e) {
    LOG(FATAL) << "Player entity does not have required Movable component.";
    throw e;
  }

  // Get a reference to the velocity vector.
  sf::Vector2i& velocity = parent_->GetComponent<Movable>().Velocity();

  // When they press down a key...
  if (event.type == sf::Event::KeyPressed) {
    switch (event.key.code) {
      // When the right key is pressed, increase the x velocity by 1.
      case sf::Keyboard::Right:
        velocity.x = std::min(velocity.x + 1, 1);
        break;

      // When the left key is pressed, decrease the x velocity by 1.
      case sf::Keyboard::Left:
        velocity.x = std::max(velocity.x - 1, -1);
        break;

      // When the up key is pressed, increase the y velocity by 1.
      case sf::Keyboard::Up:
        velocity.y = std::min(velocity.y + 1, 1);
        break;

      // When the down key is pressed, decrease the y velocity by 1.
      case sf::Keyboard::Down:
        velocity.y = std::max(velocity.y - 1, -1);
        break;

      // Don't do anything else with remaining keys.
      default:
        break;
    }
  }

  // When they release a key...
  else if (event.type == sf::Event::KeyReleased) {
    switch (event.key.code) {
      // When the right key is released, decrease the x velocity by 1.
      case sf::Keyboard::Right:
        velocity.x = std::max(velocity.x - 1, -1);
        break;

      // When the left key is released, increase the x velocity by 1.
      case sf::Keyboard::Left:
        velocity.x = std::min(velocity.x + 1, 1);
        break;

      // When the up key is released, decrease the y velocity by 1.
      case sf::Keyboard::Up:
        velocity.y = std::max(velocity.y - 1, -1);
        break;

      // When the down key is released, increase the y velocity by 1.
      case sf::Keyboard::Down:
        velocity.y = std::min(velocity.y + 1, 1);
        break;

      // Don't do anything else with remaining keys.
      default:
        break;
    }
  }
}
