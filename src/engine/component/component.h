#ifndef _ENGINE_COMPONENT_COMPONENT_H_
#define _ENGINE_COMPONENT_COMPONENT_H_

#include <SFML/System.hpp>
#include <Thor/Input/ActionMap.hpp>

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
  virtual ~Component() {

  }

  // Update the given component. This will be called once per loop.
  virtual void Update(const thor::ActionMap<std::string>& map) = 0;

  // Get the name of the concrete component.
  static const std::string& name_() {
    static const std::string name = "COMPONENT";
    return name;
  }

  virtual const std::string& name() = 0;
  
  // Bind the given entity to this component.
  virtual void Bind(Entity* parent) {
    this->parent_ = parent;
  }

protected:
  // A reference to the entity this component is attached to. Ownership will not
  // be taken of this pointer (is is assumed that destroying an entity will also
  // destroy all associated components).
  Entity* parent_;
};

}}  // namepsace engine::component

#endif  // _ENGINE_COMPONENT_COMPONENT_H_
