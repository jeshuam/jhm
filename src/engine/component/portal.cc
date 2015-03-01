#include "portal.h"

namespace engine {
namespace component {

using game::Map;

Portal::Portal() : destination_(), destination_position_()
                 , require_interaction_(false) {

}

Portal::~Portal() {

}

void Portal::SetParameter(const std::string& key, const Json::Value& value) {
  if (key == "destination") {
    destination(value.asString());
  }

  if (key == "destination_position") {
    destination_position({value[0].asFloat(), value[1].asFloat()});
  }

  if (key == "require_interaction") {
    require_interaction(value.asBool());
  }

  else if (key == "zone") {
    Component* zone = Component::Get("zone");
    for (const std::string& key : value.getMemberNames()) {
      zone->SetParameter(key, value[key]);
    }

    portal_zone(zone);
  }
}

bool Portal::Update(const thor::ActionMap<std::string>& map) {
  // If they haven't pressed the required key, don't even bother checking for
  // collisions.
  if (require_interaction() and not map.isActive("interact")) {
    return true;
  }

  // Check for collision with the player. If the player has collided with the
  // portal, then move to the new map.
  Entity* player = Map::GetActive().GetEntitiesWithComponent<Player>()[0];

  // The player must be drawable.
  if (not player->HasComponent<Drawable>()) {
    LOG->emerg("Player does not have required Drawable component!");
  }

  Drawable& d = player->GetComponent<Drawable>();
  if (d.HitBox().intersects(portal_zone().area())) {
    Map::GetActive().remove(player);
    Map::Get(destination()).add(player).Activate();
    d.sprite().setPosition(destination_position());
    return false;
  }

  return true;
}

Portal* Portal::destination(const std::string& destination) {
  destination_ = destination;
  return this;
}

Portal* Portal::portal_zone(Component* portal_zone) {
  entity_->AddComponent(portal_zone);
  return this;
}

Portal* Portal::destination_position(sf::Vector2f destination_position) {
  destination_position_ = destination_position;
  return this;
}

Portal* Portal::require_interaction(bool require_interaction) {
  require_interaction_ = require_interaction;
  return this;
}

// Getter methods.
const std::string& Portal::destination() const {
  return destination_;
}

Zone& Portal::portal_zone() {
  return entity_->GetComponent<Zone>();
}

const Zone& Portal::portal_zone() const {
  return entity_->GetComponent<Zone>();
}

const sf::Vector2f& Portal::destination_position() const {
  return destination_position_;
}

sf::Vector2f& Portal::destination_position() {
  return destination_position_;
}

bool Portal::require_interaction() const {
  return require_interaction_;
}

}}  // namepsace engine::component
