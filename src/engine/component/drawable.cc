#include "drawable.h"

#include "engine/component/player.h"

namespace engine {
namespace component {

Drawable::Drawable(const std::string& sprite_filename, sf::Vector2i offset,
                   sf::Vector2i size) {
  // Get a reference to the texture.
  texture_ = utility::resource_loader::cache.acquire(
      thor::Resources::fromFile<sf::Texture>(sprite_filename));

  // If width or height is -1, then set it to the max.
  if (size.x == 0 or size.y == 0) {
    size.x = texture_->getSize().x;
    size.y = texture_->getSize().y;
  }

  // Construct the sprite.
  sprite_.setTexture(*texture_);
  sprite_.setTextureRect(sf::IntRect(offset.x, offset.y, size.x, size.y));
}

Drawable::~Drawable() {

}

Drawable* Drawable::scale(double scale) {
  sprite_.setScale(scale, scale);
  return this;
}

Drawable* Drawable::z_index(double z_index) {
  z_index_ = z_index;
  return this;
}

Drawable* Drawable::location(sf::Vector2f location) {
  sprite_.move(location);
  return this;
}

Drawable* Drawable::repeat() {
  texture_->setRepeated(true);
  sprite_.setTexture(*texture_);
  return this;
}

Drawable* Drawable::rotate(double degrees) {
  sprite_.rotate(degrees);
  return this;
}

Drawable* Drawable::hit_box(sf::Vector2f hit_box) {
  hit_box_ = hit_box;
  return this;
}

void Drawable::Update(const thor::ActionMap<std::string>& map) {
  LOG->trace("Drawable::Update");
  LOG->trace("Done Drawable::Update");
}

void Drawable::Draw(sf::RenderWindow& window) const {
  LOG->trace("Drawable::Draw");
  window.draw(sprite_);
  LOG->trace("Done Drawable::Draw");
}

}}  // namepsace engine::component
