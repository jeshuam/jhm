#ifndef _ENGINE_COMPONENT_DRAWABLE_H_
#define _ENGINE_COMPONENT_DRAWABLE_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "engine/component/component.h"
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
  Drawable(const std::string& sprite_filename);
  Drawable(const std::string& sprite_filename, sf::Vector2u offset,
           sf::Vector2u size=sf::Vector2u(), double scale=1);
  virtual ~Drawable();

  // Update this component.
  virtual void Update(const thor::ActionMap<std::string>& map);

  // Draw this sprite onto the screen at its current location.
  virtual void Draw(sf::RenderWindow& window) const;

  // Get access to the internal sprite.
  sf::Sprite& Sprite();

protected:
  // The internal sprite used to draw the drawable to the screen.
  sf::Sprite sprite_;

  // A reference to the texture used by this drawable.
  std::shared_ptr<sf::Texture> texture_;
};

}}  // namepsace engine::component

#endif  // _ENGINE_COMPONENT_DRAWABLE_H_
