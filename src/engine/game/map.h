#ifndef _ENGINE_GAME_MAP_H_
#define _ENGINE_GAME_MAP_H_

#include <unordered_set>

#include "engine/component/entity.h"

namespace engine {
namespace game {

// A map is a set of entities which must be drawn. These entities must represent
// the map (i.e. static objects) and shouldn't include any characters or items.
class Map {
public:
  Map();
  Map(std::initializer_list<component::Entity*> entities);
  ~Map();

  // Map will use a builer-like interface.
  Map& name(const std::string& name);
  Map& add(component::Entity* entity);

private:
  std::string name_;
  std::unordered_set<component::Entity*> entities_;
};

}}  // namespace engine::game

#endif  // _ENGINE_GAME_MAP_H_
