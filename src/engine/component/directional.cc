#include "directional.h"

#include "engine/component/movable.h"

namespace engine {
namespace component {

Directional::Directional() : current_direction_(DOWN) {

}

Directional::~Directional() {
  
}

void Directional::Update(const thor::ActionMap<std::string>& map) {
  // Directional components must be movable.
  if (not parent_->HasComponent<Movable>()) {
    LOG(FATAL) << "Directional entity does not have required Movable"
               << " component.";
  }  

  Movable& movable = parent_->GetComponent<Movable>();
  if (movable.Velocity().x == 0 and movable.Velocity().y == 0) {
    // Cheat the system to force the first animation frame to come back.
    animator_.playAnimation(current_direction_);
    animator_.animate(parent_->GetComponent<Drawable>().Sprite());
    animator_.stopAnimation();
  } else {
    // If we aren't playing an animation, then start it up.
    if (not animator_.isPlayingAnimation()) {
      animator_.playAnimation(current_direction_, true);
      animator_.animate(parent_->GetComponent<Drawable>().Sprite());
    } else {
      // If the animation currently playing isn't the right one, move to the
      // right one.
      if (animator_.getPlayingAnimation() != current_direction_) {
        animator_.playAnimation(current_direction_, true);
      }
      
      animator_.update(clock_.restart());
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
    Direction direction, sf::Time length,
    const std::vector<std::pair<sf::Vector2i, double>>& frames) {
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
  for (const std::pair<sf::Vector2i, double>& frame : frames) {
    rect.left = frame.first.x;
    rect.top = frame.first.y;

    animation.addFrame(frame.second, rect);
  }

  // Save the animation.
  animator_.addAnimation(direction, animation, length);
  return *this;
}

void Directional::ChangeDirection(Direction direction) {
  current_direction_ = direction;
}

}}  // namepsace engine::component
