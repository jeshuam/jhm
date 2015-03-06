#ifndef _ENGINE_COMPONENT_PORTAL_H_
#define _ENGINE_COMPONENT_PORTAL_H_

#include "engine/component/component.h"
#include "engine/component/drawable.h"
#include "engine/component/entity.h"
#include "engine/component/player.h"
#include "engine/component/zone.h"
#include "engine/game/map.h"

namespace engine {
namespace component {

// A portal acts as a link between two maps. Portals are 1-way; you need to make
// two portals (one in each map).
class Portal : public Component {
public:
  COMPONENT_KEY("PORTAL");

  // Constructor + Destructor.
  Portal();
  virtual ~Portal();

  // Update the given parameter to match the given value.
  virtual void SetParameter(const std::string& key, const Json::Value& value);

  // Update this component.
  virtual bool Update(JHM& game);

  // Builder methods for a portal.
  Portal* destination(const std::string& destination);
  Portal* portal_zone(Component* portal_zone);
  Portal* destination_position(sf::Vector2f destination_zone);
  Portal* require_interaction(bool require_interaction);

  // Getter methods.
  const std::string& destination() const;
  const Zone& portal_zone() const;
  Zone& portal_zone();
  const sf::Vector2f& destination_position() const;
  sf::Vector2f& destination_position();
  bool require_interaction() const;

private:
  // Key of the destination map.
  std::string destination_;

  // Where to put the player once the portalling is done.
  sf::Vector2f destination_position_;

  // If true, then the "interact" button must be pressed while in the area.
  bool require_interaction_;
};

}}  // namepsace engine::component

#endif  // _ENGINE_COMPONENT_PORTAL_H_
