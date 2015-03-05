#include "map.h"

namespace engine {
namespace game {

std::unordered_map<std::string, Map*> Map::available_maps_;
Map* Map::active_map_;

// Currently playing music.
std::string Map::active_music_key_;
sf::Music Map::active_music_;

Map::Map(const std::string& name, const std::string& music) : name_(name)
                                                            , music_(music) {
  available_maps_[name] = this;
}

Map::~Map() {

}

Map& Map::add(component::Entity* entity) {
  entities_.insert(entity);
  return *this;
}

Map& Map::remove(component::Entity* entity) {
  entities_.erase(entity);
  return *this;
}

void Map::Activate() {
  Activate(*this);
}

// Getters.
const std::string& Map::name() const {
  return name_;
}

const std::string& Map::music() const {
  return music_;
}

std::unordered_set<component::Entity*> Map::entities() {
  return entities_;
}

Map& Map::Get(const std::string& name) {
  return *available_maps_.at(name);
}

void Map::Activate(Map& new_map) {
  // If they have different music playing (or nothing is playing at the moment)
  // then change songs.
  if (active_music_key_ != new_map.music()) {
    active_music_key_ = new_map.music();
    LOG->info("Changing music to {}", active_music_key_);

    active_music_.stop();
    if (not active_music_.openFromFile(active_music_key_)) {
      LOG->emerg("Could not open music file {}!", active_music_key_);
    }
    active_music_.setLoop(true);
    active_music_.play();
  }

  active_map_ = &new_map;
}

Map& Map::GetActive() {
  return *active_map_;
}

}}  // namespace engine::game
