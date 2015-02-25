#include "entity.h"

Entity::Entity() {
  Entity::Register(this);
}

Entity::~Entity() {
  Entity::Unregister(this);
}

// Container to store entitites.
std::unordered_set<Entity*> Entity::entities_;

void Entity::Register(Entity* entity) {
  entities_.insert(entity);
}

void Entity::Unregister(Entity* entity) {
  entities_.erase(entity);
}
