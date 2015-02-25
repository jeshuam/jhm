#include "movable.h"

Movable::Movable(int speed) : velocity_(), speed_(speed) {

}

Movable::~Movable() {

}

void Movable::Update() {
  try {
    Drawable& d = parent_->GetComponent<Drawable>();
    int x = d.Sprite().getPosition().x, y = d.Sprite().getPosition().y;

    d.Sprite().setPosition(x + (velocity_.x * speed_),
                           y - (velocity_.y * speed_)); // Top left is (0, 0).
  } catch (std::logic_error& e) {
    LOG(FATAL) << "Movable entity does not have required Drawable component.";
    throw e;
  }
}
