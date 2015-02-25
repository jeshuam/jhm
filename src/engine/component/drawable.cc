#include "drawable.h"

namespace engine {
namespace component {

Drawable::Drawable(const std::string& sprite_filename)
    : Drawable(sprite_filename, {0, 0}) {

}

Drawable::Drawable(const std::string& sprite_filename, sf::Vector2u offset,
                   sf::Vector2u size, double scale) {
  // Get a reference to the texture.
  texture_ = utility::resource_loader::cache.acquire(
      thor::Resources::fromFile<sf::Texture>(sprite_filename));

  // If width or height is -1, then set it to the max.
  if (size.x <= 0 or size.y <= 0) {
    size = texture_->getSize();
  }

  // Construct the sprite.
  sprite_.setTexture(*texture_);
  sprite_.setTextureRect(sf::IntRect(offset.x, offset.y, size.x, size.y));
  sprite_.setScale(scale, scale);
}

Drawable::~Drawable() {

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

sf::Sprite& Drawable::Sprite() {
  return sprite_;
}

}}  // namepsace engine::component
