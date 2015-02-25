#ifndef _ENGINE_ENTITY_ENTITY_H_
#define _ENGINE_ENTITY_ENTITY_H_

#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>

#include <Thor/Input/ActionMap.hpp>

#include "log.h"

namespace engine {
namespace component {

// Forward declare component to avoid circular includes.
class Component;

// An entity is just a bag of components. You can only have one of any component
// at any one time, though. The entity will take ownership of all components.
class Entity {
public:
  Entity();
  Entity(std::initializer_list<Component*> components);
  virtual ~Entity();

  // Add a component to this entity.
  void AddComponent(Component* component);

  // Update all internal components.
  void Update(const thor::ActionMap<std::string>& map);

  // Remove a component from this entity.
  template <typename T>
  void RemoveComponent() {
    components_.erase(T::name_());
  }

  // Check to see whether this entity has the requested component type. If it
  // does, return true, otherwise return false.
  template <typename T>
  bool HasComponent() {
    return components_.find(T::name_()) != components_.end();
  }

  // Get a reference to a given component type. Throws a logic error if this
  // entity doesn't contain the requested component.
  template <typename T>
  T& GetComponent() {
    try {
      return *dynamic_cast<T*>(components_.at(T::name_()));
    } catch (std::out_of_range) {
      throw std::logic_error("Request for component where none exists.");  
    }
  }

  template <typename T>
  const T& GetComponent() const {
    return const_cast<Entity*>(this)->GetComponent<T>();
  }

  template <typename T>
  void ReplaceComponent(Component* new_component) {
    components_[T::name_()] = new_component;
  }

  // Get all entities that contain a specific component.
  template <typename T>
  static std::unordered_set<Entity*> GetEntitiesWithComponent() {
    std::unordered_set<Entity*> entities;
    for (Entity* entity : entities_) {
      if (entity->HasComponent<T>()) {
        entities.insert(entity);
      }
    }


    return entities;
  }

  // Get all available entities.
  static std::unordered_set<Entity*> GetAllEntities() {
    return entities_;
  }

private:
  // Each entity will store with it a set of components. These pointers will be
  // freed when the entity is destroyed.
  std::unordered_map<std::string, Component*> components_;

  // Each entity will be registered into a large set to allow the main loop to
  // gain access to the entities themselves.
  static std::unordered_set<Entity*> entities_;
};

}}  // namepsace engine::component

#endif  // _ENGINE_ENTITY_ENTITY_H_
