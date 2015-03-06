#ifndef _ENGINE_COMPONENT_INTERACTABLE_H_
#define _ENGINE_COMPONENT_INTERACTABLE_H_

#include <unordered_set>
#include <memory>

#include <SFML/Graphics.hpp>

#include "engine/action/action.h"
#include "engine/action/display_message.h"
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
  virtual bool Update(Game& game);

  // Setters.
  Interactable* action_key(const std::string& action_key);
  Interactable* facing(const std::unordered_set<Directional::Direction> facing);
  Interactable* parameters(const Json::Value& parameters);
  Interactable* cooldown(int cooldown);

  // Getters.
  const std::string& action_key() const;
  const std::unordered_set<Directional::Direction>& facing() const;
  const Json::Value& parameters() const;
  const int cooldown() const;
  const sf::FloatRect area() const;

private:
  // Action key to perform.
  std::string action_key_;

  // Set of valid directions the user may be facing in order to interact with
  // this object.
  std::unordered_set<Directional::Direction> facing_;

  // Parameters to provide to this action.
  Json::Value parameters_;

  // Actual action to be performed.
  std::unique_ptr<action::Action> action_;

  // Last time the action was activated (i.e. completed).
  sf::Clock last_activation_;
  int cooldown_;  // in ms

  // Actually perform the action described by this class.
  void StartAction(Game& game);
};

}}  // namepsace engine::component

#endif  // _ENGINE_COMPONENT_INTERACTABLE_H_
