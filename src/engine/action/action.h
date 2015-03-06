#ifndef _ENGINE_ACTION_ACTION_H_
#define _ENGINE_ACTION_ACTION_H_

#include "game.h"

namespace engine {
namespace action {

// Some action that happens when you interact with something.
class Action {
public:
  virtual ~Action() {}

  // Update the current state of the action. This could be playing an animation,
  // performing some processing, waiting for input, anything. All state should
  // be managed by the object which inherits from Action. This should return
  // `true` when the action has been completed.
  virtual bool Update(Game& game) = 0;
};

}} // namespace engine::action

#endif  // _ENGINE_ACTION_ACTION_H_
