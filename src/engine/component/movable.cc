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
  if (clock_.getElapsedTime().asMilliseconds() < 20) {
    LOG->trace("Done (early) Movable::Update");
    return;
  }

  // The object _must_ be drawable.
  if (not parent_->HasComponent<Drawable>()) {
    LOG->emerg("Movable entity does not have required Drawable component.");
  }

  // Update the velocity.
  Drawable& d = parent_->GetComponent<Drawable>();
  d.Sprite().setPosition(
      d.Sprite().getPosition().x + (velocity_.x * speed_ * speed_multiplier_),
      d.Sprite().getPosition().y - (velocity_.y * speed_ * speed_multiplier_));

  // If the object is directional (optional), change the direction.
  parent_->HasComponent<Directional>();
  if (parent_->HasComponent<Directional>()) {
    Directional& directional = parent_->GetComponent<Directional>();
    if (velocity_.x < 0) {
      directional.MoveLeft();
    } else if (velocity_.x > 0) {
      directional.MoveRight();
    } else if (velocity_.y > 0) {
      directional.MoveUp();
    } else if (velocity_.y < 0) {
      directional.MoveDown();
    }
  }

  clock_.restart();
  LOG->trace("Done Movable::Update");
}

}}  // namepsace engine::component
