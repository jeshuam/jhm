#include "interactable.h"

namespace engine {
namespace component {

using game::Map;

Interactable::Interactable() : action_key_(), facing_(), parameters_()
                             , action_(nullptr), cooldown_(300) {

}

Interactable::~Interactable() {

}

void Interactable::SetParameter(const std::string& key,
                                const Json::Value& value) {
  if (key == "action") {
    action_key(value.asString());
  }

  else if (key == "facing") {
    std::unordered_set<Directional::Direction> facing_new;
    for (unsigned int i = 0; i < value.size(); i++) {
      facing_new.insert(Directional::GetDirection(value[i].asString()));
    }

    facing(facing_new);
  }

  else if (key == "parameters") {
    parameters(value);
  }

  else if (key == "cooldown") {
    cooldown(value.asInt());
  }
}

bool Interactable::Update(Game& game) {
  // If there is an action currently playing, keep playing.
  if (action_) {
    if (action_->Update(game)) {
      game.ReleaseOwnership();
      action_.reset();
      last_activation_.restart();
      return true;
    }
  }

  // Otherwise, no action is active...
  else {
    // If we only just interacted with the thing, then don't do it again for a
    // little while.
    if (last_activation_.getElapsedTime() < sf::milliseconds(cooldown())) {
      return true;
    }

    // If they are interacting...
    if (game.action_map().isActive("interact")) {
      // If the player is currently colliding with us.
      Entity* player = Map::GetActive().GetEntitiesWithComponent<Player>()[0];
      auto dir = player->GetComponent<Directional>().current_direction();
      auto hit_box = player->GetComponent<Drawable>().HitBox();
      if (facing().count(dir) == 1 and hit_box.intersects(area())) {
        StartAction(game);
      }
    }
  }

  return true;
}

Interactable* Interactable::action_key(const std::string& action_key) {
  action_key_ = action_key;
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

Interactable* Interactable::cooldown(int cooldown) {
  cooldown_ = cooldown;
  return this;
}

const std::string& Interactable::action_key() const {
  return action_key_;
}

const std::unordered_set<Directional::Direction>& Interactable::facing() const {
  return facing_;
}

const Json::Value& Interactable::parameters() const {
  return parameters_;
}

const int Interactable::cooldown() const {
  return cooldown_;
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

void Interactable::StartAction(Game& game) {
  // Display a message on the screen. This will pause all gameplay and required
  // the player to click "play" to advance it.
  if (action_key() == "display_message") {
    std::vector<std::string> messages;
    for (unsigned int i = 0; i < parameters_["messages"].size(); i++) {
      messages.push_back(parameters_["messages"][i].asString());
    }

    action_.reset(new action::DisplayMessage(game, messages));
  }

  else if (action_key() == "show_calendar") {
    action_.reset(new action::ShowCalendar(game));
  }

  // Take ownership of the game!
  game.TakeOwnership(entity_);
}

}}  // namepsace engine::component
