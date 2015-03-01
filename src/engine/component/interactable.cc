#include "interactable.h"

namespace engine {
namespace component {

using game::Map;

Interactable::Interactable() : action_(), facing_(), parameters_() {

}

Interactable::~Interactable() {

}

void Interactable::SetParameter(const std::string& key,
                                const Json::Value& value) {
  if (key == "action") {
    action(value.asString());
  }

  else if (key == "facing") {
    std::unordered_set<Directional::Direction> facing_new;
    for (int i = 0; i < value.size(); i++) {
      facing_new.insert(Directional::GetDirection(value[i].asString()));
    }

    facing(facing_new);
  }

  else if (key == "parameters") {
    parameters(value);
  }
}

bool Interactable::Update(const thor::ActionMap<std::string>& map) {
  // If they are interacting...
  if (map.isActive("interact")) {
    // If the player is currently colliding with us.
    Entity* player = Map::GetActive().GetEntitiesWithComponent<Player>()[0];
    auto dir = player->GetComponent<Directional>().current_direction();
    auto hit_box = player->GetComponent<Drawable>().HitBox();
    if (facing().count(dir) == 1 and hit_box.intersects(area())) {
      return DoAction();
    }
  }

  return true;
}

Interactable* Interactable::action(const std::string& action) {
  action_ = action;
  return this;
}

Interactable* Interactable::facing(
      const std::unordered_set<Directional::Direction> facing) {
  facing_ = facing;
  return this;
}

Interactable* Interactable::parameters(const Json::Value& parameters) {
  parameters_ = parameters;
  return this;
}

const std::string& Interactable::action() const {
  return action_;
}

const std::unordered_set<Directional::Direction>& Interactable::facing() const {
  return facing_;
}

const Json::Value& Interactable::parameters() const {
  return parameters_;
}

const sf::FloatRect Interactable::area() const {
  sf::FloatRect area;
  if (entity_->HasComponent<Drawable>()) {
    area = entity_->GetComponent<Drawable>().sprite().getGlobalBounds();
  }

  else if (entity_->HasComponent<Zone>()) {
    area = entity_->GetComponent<Zone>().area();
  }

  else {
    LOG->emerg("Interactable object must have some kind of footprint!");
  }

  // Expand the area by 1 pixel in each direction.
  area.left++;
  area.top++;
  area.width += 2;
  area.height += 2;
  return area;
}

bool Interactable::DoAction() {
  // Display a message on the screen. This will pause all gameplay and required
  // the player to click "play" to advance it.
  if (action() == "display_message") {
    LOG->info("Displaying message {}", parameters_["message"].asString());
  }

  return true;
}

}}  // namepsace engine::component
