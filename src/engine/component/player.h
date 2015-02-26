#ifndef _ENGINE_COMPONENT_PLAYER_H_
#define _ENGINE_COMPONENT_PLAYER_H_

#include <SFML/Window.hpp>
#include <Thor/Input/Action.hpp>

#include "engine/component/component.h"
#include "engine/component/movable.h"
#include "engine/component/directional.h"
#include "log.h"

namespace engine {
namespace component {

// A component which allows a player to take control of an entity. The entity
// must be drawable and movable. Players _must_ be directional (this is managed
// internally). Players have 2 directional animations: walking and running.
class Player : public Component {
public:
  COMPONENT_KEY("PLAYER");

  // Constructor + Destructor.
  Player(thor::ActionMap<std::string>& map, double running_multiplier);
  virtual ~Player();

  // Override the bind method to also automatically bind the walking and running
  // directional objects.
  virtual void Bind(Entity* entity);

  // The player just responds to keypresses.
  virtual void Update(const thor::ActionMap<std::string>& map);

protected:
  // How much faster should running be?
  double running_multiplier_;

  // Directional animations for walking and running.
  Directional* walking_directional_;
  Directional* running_directional_;
};

}}  // namepsace engine::component

#endif  // _ENGINE_COMPONENT_PLAYER_H_
