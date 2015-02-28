#include "directional.h"

#include "engine/component/movable.h"

namespace engine {
namespace component {

Directional::Directional() : current_direction_(DOWN) {

}

Directional::~Directional() {
  
}

void Directional::Update(const thor::ActionMap<std::string>& map) {
  LOG->trace("Directional::Update");

  // Directional components must be movable.
  if (not parent_->HasComponent<Movable>()) {
    LOG->emerg("Directional entity does not have required Movable component.");
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

  LOG->trace("Done Directional::Update");
}

Directional* Directional::AddDirection(
    Direction direction, sf::Time length,
    const std::vector<std::pair<sf::IntRect, double>>& frames) {
  // Copy the sprite's texture rectangle and pass a modified version in with
  // each frame.
  thor::FrameAnimation animation;
  for (const std::pair<sf::IntRect, double>& frame : frames) {
    animation.addFrame(frame.second, frame.first);
  }

  // Save the animation.
  animator_.addAnimation(direction, animation, length);
  return this;
}

void Directional::ChangeDirection(Direction direction) {
  current_direction_ = direction;
}

void Directional::SetParameter(const std::string& key,
                               const Json::Value& value) {
  // TODO(jeshua) implement this.
}

}}  // namepsace engine::component
