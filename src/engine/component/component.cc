#include "component.h"

#include "engine/component/block_movement.h"
#include "engine/component/drawable.h"

namespace engine {
namespace component {

Component* Component::Get(const std::string& key) {
  if (key == "drawable") {
    return new Drawable();
  }

  else if (key == "block_movement") {
    return new BlockMovement();
  }

  LOG->emerg("Invalid key {}", key);
  return nullptr;
}

}}  // namepsace engine::component
