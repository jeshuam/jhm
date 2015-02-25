#ifndef _ENGINE_ENTITY_ENTITY_H_
#define _ENGINE_ENTITY_ENTITY_H_

#include <memory>
#include <unordered_set>

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

  // Remove a component from this entity.
  template <typename T>
  void RemoveComponent() {
    try {
      components_.erase(components_.find(GetComponent<T>()));
    } catch (std::logic_error) {
      // Do nothing; this component was never present.
    }
  }

  // Check to see whether this entity has a given component type.
  template <typename T>
  T& GetComponent() {
    for (const std::shared_ptr<Component>& component : components_) {
      T* component_specific = dynamic_cast<T*>(component.get());
      if (component_specific) {
        return *component_specific;
      }
    }

    // Oh noes! This shouldn't happen; you shouldn't ask for components that
    // don't exist. You should only call this to get a quick reference to the
    // component, nothing more.
    throw std::logic_error("Request for component where none exists.");
  }

  template <typename T>
  const T& GetComponent() const {
    for (const std::shared_ptr<Component>& component : components_) {
      T* component_specific = dynamic_cast<T*>(component.get());
      if (component_specific) {
        return *component_specific;
      }
    }

    // Oh noes! This shouldn't happen; you shouldn't ask for components that
    // don't exist. You should only call this to get a quick reference to the
    // component, nothing more.
    throw std::logic_error("Request for component where none exists.");
  }

  // Get all entities that contain a specific component.
  template <typename T>
  static std::unordered_set<Entity*> GetEntitiesWithComponent() {
    std::unordered_set<Entity*> entities;
    for (Entity* entity : entities_) {
      try {
        entity->GetComponent<T>();
        entities.insert(entity);
      } catch (std::logic_error) {
        // Do nothing; this entity doesn't contain the required component.
      }
    }

    return entities;
  }

private:
  // Each entity will store with it a set of components.
  std::unordered_set<std::shared_ptr<Component>> components_;

  // Each entity will be registered into a large set to allow the main loop to
  // gain access to the entities themselves.
  static std::unordered_set<Entity*> entities_;
};

}}  // namepsace engine::component

#endif  // _ENGINE_ENTITY_ENTITY_H_
