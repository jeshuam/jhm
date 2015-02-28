#include "drawable.h"

#include "engine/component/player.h"

namespace engine {
namespace component {

Drawable::Drawable() {

}

Drawable::Drawable(const std::string& sprite_filename, sf::Vector2i offset,
                   sf::Vector2i size) {
  create(sprite_filename, offset, size);
}

Drawable::~Drawable() {

}

Drawable* Drawable::create(const std::string& sprite_filename,
                           sf::Vector2i offset, sf::Vector2i size) {
  // Get a reference to the texture.
  texture_ = utility::resource_loader::cache.acquire(
      thor::Resources::fromFile<sf::Texture>(sprite_filename));

  // If width or height is -1, then set it to the max.
  if (size.x == 0 or size.y == 0) {
    size.x = texture_->getSize().x;
    size.y = texture_->getSize().y;
  }

  // Always repeat the texture.
  texture_->setRepeated(true);

  // Construct the sprite.
  sprite_.setTexture(*texture_);
  sprite_.setTextureRect(sf::IntRect(offset.x, offset.y, size.x, size.y));
  return this;
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

void Drawable::SetParameter(const std::string& key, const Json::Value& value) {
  if (key == "scale") {
    scale(value.asDouble());
  }

  else if (key == "z_index") {
    z_index(value.asDouble());
  }

  else if (key == "location") {
    location(sf::Vector2f(value[0].asDouble(), value[1].asDouble()));
  }

  else if (key == "rotate") {
    rotate(value.asDouble());
  }

  else if (key == "hit_box") {
    hit_box(sf::Vector2f(value[0].asDouble(), value[1].asDouble()));
  }

  else if (key == "sprite") {
    const std::string& filename = value["file"].asString();

    sf::Vector2i offset, size;
    if (value.isMember("offset")) {
      offset = { value["offset"][0].asInt(), value["offset"][1].asInt() };
    }

    if (value.isMember("size")) {
      size = { value["size"][0].asInt(), value["size"][1].asInt() };
    }

    create(filename, offset, size);
  }
}

}}  // namepsace engine::component
