#ifndef _ENGINE_COMPONENT_INTERACTABLE_H_
#define _ENGINE_COMPONENT_INTERACTABLE_H_

#include <unordered_set>

#include <SFML/Graphics.hpp>

#include "engine/component/component.h"
#include "engine/component/directional.h"
#include "engine/component/drawable.h"
#include "engine/component/entity.h"
#include "engine/component/player.h"
#include "engine/game/map.h"

namespace engine {
namespace component {

class Interactable : public Component {
public:
  COMPONENT_KEY("INTERACTABLE");

  // Constructor + Destructor.
  Interactable();
  virtual ~Interactable();

  // Set a parameter (for JSON construction).
  virtual void SetParameter(const std::string& key, const Json::Value& value);

  // Update the given component.
  virtual bool Update(JHM& game);

  // Setters.
  Interactable* action(const std::string& action);
  Interactable* facing(const std::unordered_set<Directional::Direction> facing);
  Interactable* parameters(const Json::Value& parameters);

  // Getters.
  const std::string& action() const;
  const std::unordered_set<Directional::Direction>& facing() const;
  const Json::Value& parameters() const;
  const sf::FloatRect area() const;

private:
  // Action key to perform.
  std::string action_;

  // Set of valid directions the user may be facing in order to interact with
  // this object.
  std::unordered_set<Directional::Direction> facing_;

  // Parameters to provide to this action.
  Json::Value parameters_;

  // Actually perform the action described by this class.
  bool DoAction();
};

}}  // namepsace engine::component

#endif  // _ENGINE_COMPONENT_INTERACTABLE_H_
