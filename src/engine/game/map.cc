#include "map.h"

namespace engine {
namespace game {

Map::Map() {

}

Map::Map(std::initializer_list<component::Entity*> entities)
    : entities_(entities) {

}

Map::~Map() {

}

Map& Map::name(const std::string& name) {
  name_ = name;
  return *this;
}

Map& Map::add(component::Entity* entity) {
  entities_.insert(entity);
  return *this;
}

}}  // namespace engine::game
