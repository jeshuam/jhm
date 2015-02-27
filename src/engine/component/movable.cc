#include "movable.h"

namespace engine {
namespace component {

Movable::Movable(double speed) : speed_(speed), speed_multiplier_(1.0) {

}

Movable::~Movable() {

}

void Movable::Update(const thor::ActionMap<std::string>& map) {
  LOG->trace("Movable::Update");

  // Only run this every x ms.
  if (clock_.getElapsedTime().asMilliseconds() < kUpdateFrequencyMs) {
    LOG->trace("Done (early) Movable::Update");
    return;
  }

  // The object _must_ be drawable.
  if (not parent_->HasComponent<Drawable>()) {
    LOG->emerg("Movable entity does not have required Drawable component.");
  }

  // Update the current position of the object.
  Drawable& d = parent_->GetComponent<Drawable>();
  sf::Vector2f old_position = d.Sprite().getPosition();
  d.Sprite().setPosition(
      d.Sprite().getPosition().x + (velocity_.x * speed_ * speed_multiplier_),
      d.Sprite().getPosition().y - (velocity_.y * speed_ * speed_multiplier_));

  // If the sprite's new position interferes with anything that blocks movement,
  // don't actually move.
  for (const Entity* entity : Entity::GetEntitiesWithComponent<BlockMovement>()) {
    if (not entity->HasComponent<Drawable>()) {
      LOG->emerg("Something blocks movement but is isn't drawable!");
    }

    const Drawable& d2 = entity->GetComponent<Drawable>();
    sf::FloatRect d2_bounds = d2.Sprite().getGlobalBounds();

    // Add some padding around the movement-blocking object. It makes the
    // controls a little less likely to get stuck.
    d2_bounds.left -= 4;
    d2_bounds.top -= 4;
    d2_bounds.width += 8;
    d2_bounds.height += 8;
    if (d2.HitBox().intersects(d.HitBox())) {
      LOG->debug("Collision detected!");
      d.Sprite().setPosition(old_position);
      break;
    }
  }

  // If the object is directional (optional), change the direction.
  parent_->HasComponent<Directional>();
  if (parent_->HasComponent<Directional>()) {
    Directional& directional = parent_->GetComponent<Directional>();
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

}}  // namepsace engine::component
