#ifndef _ENGINE_COMPONENT_COMPONENT_H_
#define _ENGINE_COMPONENT_COMPONENT_H_

#include <SFML/System.hpp>
#include <Thor/Input/ActionMap.hpp>
#include <json/json.h>

#include "log.h"

namespace engine {
namespace component {

// All components must declare this at the top of their PUBLIC section. This
// will setup the name_ and name() methods automatically.
#define COMPONENT_KEY(KEY)                                  \
  static const std::string& name_() {                       \
    static const std::string name = KEY;                    \
    return name;                                            \
  }                                                         \
                                                            \
  virtual const std::string& name() {                       \
    return name_();                                         \
  }                                                         \

// Forward declare entity to avoid circular includes.
class Entity;

// Super class for all component types. Any number of components can be attached
// to an entity and that entity will gain the effects of the components.
class Component {
public:
  COMPONENT_KEY("COMPONENT");

  // Get a new component of the given type.
  static Component* Get(const std::string& key);

  // Virtual destructor (which does nothing).
  virtual ~Component();

  // Bind the given entity to this component.
  virtual void Bind(Entity* entity);

  // Set the parameter of the current component. This is required to be
  // set by each component to allow for easy loading from configuration files.
  virtual void SetParameter(const std::string& key,
                            const Json::Value& value) = 0;

  // Update the given component. This will be called once per loop.
  virtual void Update(const thor::ActionMap<std::string>& map) = 0;

protected:
  // A reference to the entity this component is attached to. Ownership will not
  // be taken of this pointer (is is assumed that destroying an entity will also
  // destroy all associated components).
  Entity* entity_;
};

}}  // namepsace engine::component

#endif  // _ENGINE_COMPONENT_COMPONENT_H_
