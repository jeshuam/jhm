#ifndef _ENGINE_COMPONENTS_PLAYER_H_
#define _ENGINE_COMPONENTS_PLAYER_H_

#include <SFML/Window.hpp>
#include <Thor/Input/Action.hpp>

#include "engine/component/component.h"
#include "engine/component/movable.h"
#include "engine/component/directional.h"
#include "log.h"

namespace engine {
namespace component {

// A component which allows a player to take control of an entity. The entity
// must be drawable and movable.
class Player : public Component {
public:
  Player(thor::ActionMap<std::string>& map, double running_multiplier);
  virtual ~Player();

  // The player just responds to keypresses.
  virtual void Update(const thor::ActionMap<std::string>& map);

  virtual void Bind(Entity* entity);

  static const std::string& name_() {
    static const std::string name = "PLAYER";
    return name;
  }

  virtual const std::string& name() {
    return name_();
  }

protected:
  double running_multiplier_;

  Directional* walking_directional_;
  Directional* running_directional_;
};

}}  // namepsace engine::component

#endif  // _ENGINE_COMPONENTS_PLAYER_H_
