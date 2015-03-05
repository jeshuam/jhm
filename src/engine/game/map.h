#ifndef _ENGINE_GAME_MAP_H_
#define _ENGINE_GAME_MAP_H_

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <SFML/Audio.hpp>

#include "engine/component/entity.h"

namespace engine {
namespace game {

// A map is a set of entities which must be drawn. These entities must represent
// the map (i.e. static objects) and shouldn't include any characters or items.
class Map {
public:
  Map(const std::string& name, const std::string& music);
  ~Map();

  // Map will use a builer-like interface.
  Map& add(component::Entity* entity);

  // Remove the given entity.
  Map& remove(component::Entity* entity);

  // Get all entities which have the given component.
  template <typename T>
  std::vector<component::Entity*> GetEntitiesWithComponent() {
    std::vector<component::Entity*> entities;
    for (component::Entity* entity : entities_) {
      if (entity->HasComponent<T>()) {
        entities.push_back(entity);
      }
    }

    return entities;
  }

  // Set this map as the active map.
  void Activate();

  // Getters for members.
  const std::string& name() const;
  const std::string& music() const;
  std::unordered_set<component::Entity*> entities();

  // Get the map with a given name from the registry.
  static Map& Get(const std::string& name);

  // Set the currently 'active' map.
  static void Activate(Map& new_map);

  // Get the currently 'active' map.
  static Map& GetActive();

private:
  // String name of the map. Can be referenced by entities and should be unique.
  std::string name_;

  // File path of the music to play when on this map.
  std::string music_;

  // A set of entities associated with this map. This should be all of the
  // background entities.
  std::unordered_set<component::Entity*> entities_;

  // Register of available maps. Can be used to retreive maps.
  static std::unordered_map<std::string, Map*> available_maps_;

  // Currently active map.
  static Map* active_map_;

  // Currently playing music.
  static std::string active_music_key_;
  static sf::Music active_music_;
};

}}  // namespace engine::game

#endif  // _ENGINE_GAME_MAP_H_
