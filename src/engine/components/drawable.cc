#include "drawable.h"

Drawable::Drawable(const std::string& sprite_filename)
    : Drawable(sprite_filename, {0, 0}) {

}

Drawable::Drawable(const std::string& sprite_filename, sf::Vector2u offset,
                   sf::Vector2u size) {
  // Get a reference to the texture.
  const sf::Texture& texture = TextureLoader::Load(sprite_filename);

  // If width or height is -1, then set it to the max.
  if (size.x <= 0 or size.y <= 0) {
    size = texture.getSize();
  }

  // Construct the sprite.
  sprite_.setTexture(texture);
  sprite_.setTextureRect(sf::IntRect(offset.x, offset.y, size.x, size.y));
}

void Drawable::Draw(sf::RenderWindow& window) const {
  window.draw(sprite_);
}

sf::Sprite& Drawable::Sprite() {
  return sprite_;
}
