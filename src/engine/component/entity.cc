#include "entity.h"

#include "engine/component/component.h"

namespace engine {
namespace component {

// Container to store entitites.
std::unordered_set<Entity*> Entity::entities_;

Entity::Entity() : Entity({}) {
  
}

Entity::Entity(std::initializer_list<Component*> components) {
  entities_.insert(this);

  // Load the components.
  for (Component* component : components) {
    AddComponent(component);
  }
}

Entity::~Entity() {
  entities_.erase(this);
}

void Entity::AddComponent(Component* component) {
  components_.insert(std::shared_ptr<Component>(component));

  // Bind this component to the entity.
  component->Bind(this);
}

void Entity::Update() {
  for (auto& component : components_) {
    component->Update();
  }
}

}}  // namepsace engine::component
