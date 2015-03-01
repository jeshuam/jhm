#include "map.h"

namespace engine {
namespace game {

std::unordered_map<std::string, Map*> Map::available_maps_;
Map* Map::active_map_; 

Map::Map(const std::string& name) : name_(name) {
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
  active_map_ = this;
}

// Getters.
const std::string& Map::name() const {
  return name_;
}

std::unordered_set<component::Entity*> Map::entities() {
  return entities_;
}

Map& Map::Get(const std::string& name) {
  return *available_maps_.at(name);
}

void Map::Activate(const std::string& name) {
  Get(name).Activate();
}

Map& Map::GetActive() {
  return *active_map_;
}

}}  // namespace engine::game
