#include "directional.h"

#include "engine/component/movable.h"

namespace engine {
namespace component {

Directional::Directional() : current_direction_(DOWN) {

}

Directional::~Directional() {
  
}

void Directional::SetParameter(const std::string& key,
                               const Json::Value& value) {
  // TODO(jeshua) implement this.
  throw std::logic_error("Directional::SetParameter() isn't implemented!");
}

void Directional::Update(const thor::ActionMap<std::string>& map) {
  LOG->trace("Directional::Update");

  // Directional components must be movable.
  if (not entity_->HasComponent<Movable>()) {
    LOG->emerg("Directional entity does not have required Movable component.");
  }  


  Movable& movable = entity_->GetComponent<Movable>();
  if (movable.velocity().x == 0 and movable.velocity().y == 0) {
    // Cheat the system to force the first animation frame to come back.
    animator_.playAnimation(current_direction_);
    animator_.animate(entity_->GetComponent<Drawable>().sprite());
    animator_.stopAnimation();
  } else {
    // If we aren't playing an animation, then start it up.
    if (not animator_.isPlayingAnimation()) {
      animator_.playAnimation(current_direction_, true);
      animator_.animate(entity_->GetComponent<Drawable>().sprite());
    } else {
      // If the animation currently playing isn't the right one, move to the
      // right one.
      if (animator_.getPlayingAnimation() != current_direction_) {
        animator_.playAnimation(current_direction_, true);
      }
      
      animator_.update(clock_.restart());
      animator_.animate(entity_->GetComponent<Drawable>().sprite());
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

}}  // namepsace engine::component
