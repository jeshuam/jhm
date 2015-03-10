#ifndef _ENGINE_COMPONENT_ZONE_H_
#define _ENGINE_COMPONENT_ZONE_H_

#include <SFML/Graphics.hpp>

#include "engine/component/component.h"

namespace engine {
namespace component {

// A zone is kinda like a drawable, but isn't drawn to the screen. Something
// shouldn't be both drawable and a zone at the same time. Zones can be used to
// define that something should happen within a particular area on the map (e.g.
// movement should be blocked --> invisible wall, a transition from one map to
// the next should occur).
class Zone : public Component {
public:
  COMPONENT_KEY("ZONE");

  // Constructor + Destructor.
  Zone();
  virtual ~Zone();

  // Update the given parameter to match the given value.
  virtual void SetParameter(const std::string& key, const Json::Value& value);

  // Update this component.
  virtual bool Update(Game& game);

  // Builder methods for a zone.
  Zone* area(sf::FloatRect area);
  Zone* scale(double scale_factor);
  Zone* debug(bool debug);

  // Getter methods.
  const sf::FloatRect area() const;
  double scale() const;
  bool debug() const;

private:
  // Each zone is simply a rectangle which can be checked (e.g. collisions). To
  // make things easy with scaling, these rectangles are defined based on the
  // _original_ size of the map, and an additional scale factor an be applied.
  sf::FloatRect area_;
  double scale_;

  // If this is true, show the zone on the screen as a rectangle.
  bool debug_;
};

}}  // namepsace engine::component

#endif  // _ENGINE_COMPONENT_ZONE_H_
