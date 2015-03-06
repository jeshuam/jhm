#ifndef _ENGINE_COMPONENT_DRAWABLE_H_
#define _ENGINE_COMPONENT_DRAWABLE_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "engine/component/component.h"
#include "engine/component/entity.h"
#include "engine/utility/resource_loader.h"
#include "log.h"

namespace engine {
namespace component {

// Drawable objects have an associated image (which can either be a full file or
// a subsection within a file). When you create the component, you must specify
// the sprite parameters.
class Drawable : public Component {
public:
  COMPONENT_KEY("DRAWABLE");

  // Construct a new drawable component. Drawable objects require a either a
  // sprite file or a sprite map and location. You can also specify a scaling
  // factor for the sprite if desired.
  Drawable();
  virtual ~Drawable();

  // Setup the parameter with the given value. The special key "sprite" can be
  // used to configure the internal sprite (i.e. call `create`).
  virtual void SetParameter(const std::string& key, const Json::Value& value);

  // Update this component.
  virtual bool Update(JHM& game);

  // Draw this sprite onto the screen at its current location.
  virtual void Draw(sf::RenderWindow& window) const;

  // Get the hit box of this drawable element. This box can be modified using
  // the hit_box_ attribute.
  const sf::FloatRect HitBox() const;

  // Build methods for creating drawables.
  Drawable* create(const std::string& sprite_filename, sf::Vector2i offset,
                   sf::Vector2i size);
  Drawable* scale(double scale);
  Drawable* z_index(double z_index);
  Drawable* location(sf::Vector2f location);
  Drawable* rotate(double degrees);
  Drawable* hit_box(sf::FloatRect hit_box);

  // Getter methods for variables.
  sf::Sprite& sprite();
  const sf::Sprite& sprite() const;
  const sf::FloatRect& hit_box() const;
  double z_index() const;

protected:
  // The internal sprite used to draw the drawable to the screen.
  sf::Sprite sprite_;

  // What counts as 'hitting' this object?
  sf::FloatRect hit_box_;

  // A reference to the texture used by this drawable.
  std::shared_ptr<sf::Texture> texture_;

  // The location this drawable should be displayed on the z-axis.
  double z_index_;
};

}}  // namepsace engine::component

#endif  // _ENGINE_COMPONENT_DRAWABLE_H_
