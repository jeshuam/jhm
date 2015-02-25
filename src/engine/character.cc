#include "character.h"

Character::Character() {

}

Character::Character(const std::string& sprite_filename)
    : Character(sprite_filename, 0, 0) {

}

Character::Character(const std::string& sprite_filename, int x_offset,
                      int y_offset, int width, int height)
    : x_(0), y_(0), x_velocity_(0), y_velocity_(0), sprite_() {
  // Get a reference to the texture.
  const sf::Texture& texture = TextureLoader::Load(sprite_filename);

  // If width or height is -1, then set it to the max.
  if (width < 0) {
    width = texture.getSize().x;
  }

  if (height < 0) {
    height = texture.getSize().y;
  }

  // Construct the sprite.
  sprite_.setTexture(texture);
  sprite_.setTextureRect(sf::IntRect(x_offset, y_offset, width, height));
  sprite_.setPosition(x_, y_);
}

Character::~Character() {

}

void Character::Draw(sf::RenderWindow& window) const {
  window.draw(sprite_);
}

void Character::KeyPressed(const sf::Event& event) {
  switch (event.type) {
    case sf::Event::KeyPressed:
      switch (event.key.code) {
        case sf::Keyboard::Right:
          if (not moving_right_) {
            x_velocity_ = std::min(x_velocity_ + 1, 1);
          }

          moving_right_ = true;
          break;

        case sf::Keyboard::Left:
          if (not moving_left_) {
            x_velocity_ = std::max(x_velocity_ - 1, -1);
          }

          moving_left_ = true;
          break;

        case sf::Keyboard::Up:
          if (not moving_up_) {
            y_velocity_ = std::min(y_velocity_ + 1, 1);
          }

          moving_up_ = true;
          break;

        case sf::Keyboard::Down:
          if (not moving_down_) {
            y_velocity_ = std::max(y_velocity_ - 1, -1);
          }

          moving_down_ = true;
          break;
      }
      break;

    case sf::Event::KeyReleased:
      switch (event.key.code) {
        case sf::Keyboard::Right:
          x_velocity_ = std::max(x_velocity_ - 1, -1);
          moving_right_ = false;
          break;

        case sf::Keyboard::Left:
          x_velocity_ = std::min(x_velocity_ + 1, 1);
          moving_left_ = false;
          break;

        case sf::Keyboard::Up:
          y_velocity_ = std::max(y_velocity_ - 1, -1);
          moving_up_ = false;
          break;

        case sf::Keyboard::Down:
          y_velocity_ = std::min(y_velocity_ + 1, 1);
          moving_down_ = false;
          break;
      }
      break;
  }
}

void Character::Update() {
  x_ += x_velocity_ * speed_;
  y_ -= y_velocity_ * speed_;

  // Update the sprite X and Y location.
  sprite_.setPosition(x_, y_);
}
