#include "directional.h"

#include "engine/component/movable.h"

namespace engine {
namespace component {

Directional::Directional() : current_direction_(DOWN) {

}

Directional::Directional(std::vector<sf::Vector2i> up,
                         std::vector<sf::Vector2i> down,
                         std::vector<sf::Vector2i> left,
                         std::vector<sf::Vector2i> right)
    : current_direction_(DOWN) {

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
  if (movable.Velocity().x == 0 and movable.Velocity().y == 0) {
    animator_.stopAnimation();
    animator_.playAnimation(current_direction_);
    animator_.animate(parent_->GetComponent<Drawable>().Sprite());
  } else {
    if (not animator_.isPlayingAnimation()) {
      animator_.playAnimation(current_direction_);
      clock_.restart();
    } else {
      // If the animation currently playing isn't the right one, move to the
      // right one.
      if (animator_.getPlayingAnimation() != current_direction_) {
        animator_.playAnimation(current_direction_);
        clock_.restart();
      }
      
      animator_.update(clock_.getElapsedTime());
      animator_.animate(parent_->GetComponent<Drawable>().Sprite());
    }
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

Directional& Directional::AddDirection(
    Direction direction, const std::vector<sf::Vector2i>& frames) {
  // Get the sprite's rectangle.
  if (not parent_->HasComponent<Drawable>()) {
    LOG(FATAL) << "Directional entity does not have required Drawable "
               << "component.";
  }

  sf::Sprite& sprite = parent_->GetComponent<Drawable>().Sprite();
  thor::FrameAnimation animation;

  // Copy the sprite's texture rectangle and pass a modified version in with
  // each frame.
  sf::IntRect rect = sprite.getTextureRect();
  for (const sf::Vector2i& frame : frames) {
    rect.left = frame.x;
    rect.top = frame.y;

    animation.addFrame(1.0, rect);
  }

  // Save the animation.
  animator_.addAnimation(direction, animation, sf::seconds(1.0));
  return *this;
}

void Directional::ChangeDirection(Direction direction) {
  current_direction_ = direction;
}

}}  // namepsace engine::component
