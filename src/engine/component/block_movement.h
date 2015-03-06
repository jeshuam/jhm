#ifndef _ENGINE_COMPONENT_BLOCK_MOVEMENT_H_
#define _ENGINE_COMPONENT_BLOCK_MOVEMENT_H_

#include "engine/component/component.h"

namespace engine {
namespace component {

// This component can be used to block movement. Any class that moves must check
// to see whether they are going to collide with an entity that blocks walking.
//
// Anything that blocks movement must be drawable. This component doesn't really
// do anything, it just allows certain drawable objects to be specified as
// movement-blocking objects.
class BlockMovement : public Component {
public:
  COMPONENT_KEY("BLOCKMOVEMENT");

  BlockMovement() {

  }

  virtual ~BlockMovement() {

  }

  virtual bool Update(JHM& game) {
    return true;
  }

  virtual void SetParameter(const std::string& key, const Json::Value& value) {

  }
};

}}  // namepsace engine::component

#endif  // _ENGINE_COMPONENT_BLOCK_MOVEMENT_H_
