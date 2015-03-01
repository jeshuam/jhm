#include "directional.h"

#include "engine/component/movable.h"

namespace engine {
namespace component {

// Map from direction names to directions.
const std::unordered_map<std::string, Directional::Direction> directions = {
  {"UP", Directional::UP},
  {"DOWN", Directional::DOWN},
  {"LEFT", Directional::LEFT},
  {"RIGHT", Directional::RIGHT},
};

Directional::Direction Directional::GetDirection(const std::string& direction) {
  return directions.at(direction);
}

Directional::Directional() : animator_(), current_direction_(DOWN), clock_() {

}

Directional::~Directional() {
  
}

void Directional::SetParameter(const std::string& key,
                               const Json::Value& value) {
  if (key == "directions") {
    // For each direction...
    for (int i = 0; i < value.size(); i++) {
      const Json::Value& direction_json = value[i];

      // Get the current direction enum.
      Direction dir = GetDirection(direction_json["direction"].asString());

      // Get the total length of time this animation should take.
      sf::Time length = sf::seconds(direction_json["length"].asDouble());

      // Load all of the frames.
      const Json::Value& frames_json = direction_json["frames"];
      std::vector<std::pair<sf::IntRect, double>> frames;

      for (int frame = 0; frame < frames_json.size(); frame++) {
        const Json::Value& frame_json = frames_json[frame];

        // Load the rectangle from JSON.
        sf::IntRect rect = {frame_json[0][0].asInt(), frame_json[0][1].asInt(),
                            frame_json[0][2].asInt(), frame_json[0][3].asInt()};

        // Load the relative timer values for each frame.
        double relative_time = frame_json[1].asDouble();

        // Save the frame.
        frames.push_back({rect, relative_time});
      }

      // Save the direction.
      AddDirection(dir, length, frames);
    }
  }
}

bool Directional::Update(const thor::ActionMap<std::string>& map) {
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
  return true;
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

Directional::Direction Directional::current_direction() const {
  return current_direction_;
}

}}  // namepsace engine::component
