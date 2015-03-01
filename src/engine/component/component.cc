#include "component.h"

#include "engine/component/block_movement.h"
#include "engine/component/directional.h"
#include "engine/component/drawable.h"
#include "engine/component/movable.h"
#include "engine/component/player.h"
#include "engine/component/zone.h"

namespace engine {
namespace component {

Component* Component::Get(const std::string& key) {
  if (key == "block_movement") {
    return new BlockMovement();
  }

  else if (key == "directional") {
    return new Directional();
  }

  else if (key == "drawable") {
    return new Drawable();
  }

  else if (key == "movable") {
    return new Movable();
  }

  else if (key == "player") {
    return new Player();
  }

  else if (key == "zone") {
    return new Zone();
  }

  LOG->emerg("Invalid key {}", key);
  return nullptr;
}

Component::~Component() {

}

void Component::Bind(Entity* entity) {
  entity_ = entity;
}

}}  // namepsace engine::component
