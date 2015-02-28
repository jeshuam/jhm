#include "movable.h"

namespace engine {
namespace component {

Movable::Movable() : velocity_(), speed_(0.0), speed_multiplier_(1.0)
                   , clock_() {

}

Movable::~Movable() {

}

void Movable::SetParameter(const std::string& key, const Json::Value& value) {
  if (key == "speed") {
    speed(value.asDouble());
  }

  else if (key == "speed_multiplier") {
    speed_multiplier(value.asDouble());
  }
}

void Movable::Update(const thor::ActionMap<std::string>& map) {
  LOG->trace("Movable::Update");

  // Only run this every x ms.
  if (clock_.getElapsedTime().asMilliseconds() < kUpdateFrequencyMs) {
    LOG->trace("Done (early) Movable::Update");
    return;
  }

  // The object _must_ be drawable.
  if (not entity_->HasComponent<Drawable>()) {
    LOG->emerg("Movable entity does not have required Drawable component.");
  }

  // Update the current position of the object.
  Drawable& d = entity_->GetComponent<Drawable>();
  sf::Vector2f old_position = d.sprite().getPosition();
  d.sprite().setPosition(
      d.sprite().getPosition().x + (velocity_.x * speed_ * speed_multiplier_),
      d.sprite().getPosition().y - (velocity_.y * speed_ * speed_multiplier_));

  // If the sprite's new position interferes with anything that blocks movement,
  // don't actually move.
  for (const Entity* entity :
        game::Map::GetActive().GetEntitiesWithComponent<BlockMovement>()) {
    if (not entity->HasComponent<Drawable>()) {
      LOG->emerg("Something blocks movement but is isn't drawable!");
    }

    const Drawable& d2 = entity->GetComponent<Drawable>();
    sf::FloatRect d2_bounds = d2.HitBox();

    // Add some padding around the movement-blocking object. It makes the
    // controls a little less likely to get stuck.
    d2_bounds.left -= 4;
    d2_bounds.top -= 4;
    d2_bounds.width += 8;
    d2_bounds.height += 8;
    if (d2_bounds.intersects(d.HitBox())) {
      LOG->debug("Collision detected! Not moving the sprite.");
      d.sprite().setPosition(old_position);
      break;
    }
  }

  // If the object is directional (optional), change the direction.
  entity_->HasComponent<Directional>();
  if (entity_->HasComponent<Directional>()) {
    Directional& directional = entity_->GetComponent<Directional>();
    if (velocity_.x < 0) {
      directional.ChangeDirection(Directional::LEFT);
    } else if (velocity_.x > 0) {
      directional.ChangeDirection(Directional::RIGHT);
    } else if (velocity_.y > 0) {
      directional.ChangeDirection(Directional::UP);
    } else if (velocity_.y < 0) {
      directional.ChangeDirection(Directional::DOWN);
    }
  }

  clock_.restart();
  LOG->trace("Done Movable::Update");
}

Movable* Movable::speed(double speed) {
  speed_ = speed;
  return this;
}

Movable* Movable::speed_multiplier(double speed_multiplier) {
  speed_multiplier_ = speed_multiplier;
  return this;
}

sf::Vector2i& Movable::velocity() {
  return velocity_;
}

const sf::Vector2i& Movable::velocity() const {
  return velocity_;
}

double Movable::speed() const {
  return speed_;
}

double Movable::speed_multiplier() const {
  return speed_multiplier_;
}

}}  // namepsace engine::component
