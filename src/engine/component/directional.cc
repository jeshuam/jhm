#include "directional.h"

#include "engine/component/movable.h"

namespace engine {
namespace component {

Directional::Directional() : current_direction_(DOWN), current_frame_(0) {

}

Directional::Directional(std::vector<sf::Vector2i> up,
                         std::vector<sf::Vector2i> down,
                         std::vector<sf::Vector2i> left,
                         std::vector<sf::Vector2i> right)
    : current_direction_(DOWN), current_frame_(0) {
  directions_[UP] = up;
  directions_[DOWN] = down;
  directions_[LEFT] = left;
  directions_[RIGHT] = right;
}

Directional::~Directional() {
  
}

void Directional::Update() {
  // Directional components must be movable.
  if (not parent_->HasComponent<Movable>()) {
    LOG(FATAL) << "Directional entity does not have required Movable"
               << " component.";
  }

  Movable& movable = parent_->GetComponent<Movable>();
  if (movable.Velocity().x != 0 or movable.Velocity().y != 0) {
    UpdateFrame(GetNextFrame());
  } else {
    UpdateFrame(GetFrame(0));
  }
}

void Directional::MoveUp() {
  ChangeDirection(UP);
}

void Directional::MoveDown() {
  ChangeDirection(DOWN);
}

void Directional::MoveLeft() {
  ChangeDirection(LEFT);
}

void Directional::MoveRight() {
  ChangeDirection(RIGHT);
}

void Directional::ChangeDirection(Direction direction) {
  // If we are moving to a different direction, reset the current frame. If we
  // aren't, then increase the current frame count.
  if (current_direction_ != direction) {
    current_direction_ = direction;
    current_frame_ = 0;
  }
}

const sf::Vector2i& Directional::GetFrame(int frame_id) {
  return directions_[current_direction_][frame_id];
}

const sf::Vector2i& Directional::GetNextFrame() {
  // Get the direction to return.
  const sf::Vector2i& frame = GetFrame(current_frame_);

  // Get the next frame.
  current_frame_ = (current_frame_ + 1) %
                   (directions_[current_direction_].size());

  // Get the frame for this direction.
  return frame;
}

void Directional::UpdateFrame(const sf::Vector2i& frame) {
  if (not parent_->HasComponent<Drawable>()) {
    LOG(FATAL) << "Directional entity does not have required Drawable "
               << "component.";
  }

  sf::Sprite& sprite = parent_->GetComponent<Drawable>().Sprite();

  const sf::IntRect& current = sprite.getTextureRect();
  sprite.setTextureRect({frame, {current.width, current.height}});
}

}}  // namepsace engine::component
