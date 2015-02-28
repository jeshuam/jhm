#include "entity.h"

#include "engine/component/component.h"

namespace engine {
namespace component {

// Container to store entitites.
std::unordered_set<Entity*> Entity::entities_;

Entity::Entity() {
  entities_.insert(this);
}

Entity::~Entity() {
  entities_.erase(this);

  for (auto& type_component : components_) {
    delete type_component.second;
  }
}

Entity* Entity::AddComponent(Component* component) {
  // Insert the component.
  components_[component->name()] = component;

  // Bind this component to the entity.
  component->Bind(this);
  return this;
}

void Entity::Update(const thor::ActionMap<std::string>& map) {
  for (auto& type_component : components_) {
    type_component.second->Update(map);
  }
}

}}  // namepsace engine::component
