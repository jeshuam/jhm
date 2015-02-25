#ifndef _ENGINE_COMPONENTS_COMPONENT_H_
#define _ENGINE_COMPONENTS_COMPONENT_H_

#include <SFML/System.hpp>
#include <Thor/Input/ActionMap.hpp>

namespace engine {
namespace component {

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
  
  // Bind the given entity to this component.
  void Bind(Entity* parent) {
    this->parent_ = parent;
  }

protected:
  // A reference to the entity this component is attached to. Ownership will not
  // be taken of this pointer (is is assumed that destroying an entity will also
  // destroy all associated components).
  Entity* parent_;
};

}}  // namepsace engine::component

#endif  // _ENGINE_COMPONENTS_COMPONENT_H_
