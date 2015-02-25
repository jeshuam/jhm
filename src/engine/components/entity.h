// This is the super class for all entities. Anything which inherits this class
// will automatically register itself as an entity which can then be fetched \
// from anywhere in the main game.
// During runtime, the entity list will be traversed several times to handle
// events and rendering.

#ifndef _ENGINE_ENTITY_ENTITY_H_
#define _ENGINE_ENTITY_ENTITY_H_

#include <unordered_set>

class Entity {
public:
  // 
  Entity();
  virtual ~Entity();

  virtual void Update() = 0;

  static void Register(Entity* entity);
  static void Unregister(Entity* entity);

  static std::unordered_set<Entity*> entities_;

  template <class T>
  static std::unordered_set<T*> GetEntitiesOfType() {
    std::unordered_set<T*> to_return;
    for (Entity* entity : entities_) {
      T* entity_specific = dynamic_cast<T*>(entity);
      if (entity_specific != nullptr) {
        to_return.insert(entity_specific);
      }
    }

    return to_return;
  }
};

#endif  // _ENGINE_ENTITY_ENTITY_H_
