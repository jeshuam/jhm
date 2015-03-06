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
  Player();
  virtual ~Player();

  // For now, we need to override the bind option to especially bind both
  // special directionals.
  virtual void Bind(Entity* entity);

  // Update the value of 'key' to 'value'.
  virtual void SetParameter(const std::string& key, const Json::Value& value);

  // The player just responds to keypresses.
  virtual bool Update(JHM& game);

  // Build methods for a player.
  Player* running_multiplier(double running_multiplier);
  Player* walking_directional(Directional* walking_directional);
  Player* running_directional(Directional* running_directional);

  // Getter methods.
  double running_multiplier() const;

protected:
  // How much faster should running be?
  double running_multiplier_;

  // Directional animations for walking and running.
  Directional* walking_directional_;
  Directional* running_directional_;
};

}}  // namepsace engine::component

#endif  // _ENGINE_COMPONENT_PLAYER_H_
