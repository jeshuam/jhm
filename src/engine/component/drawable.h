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
  Drawable(const std::string& sprite_filename,
           sf::Vector2i offset={0, 0}, sf::Vector2i size={0, 0});
  virtual ~Drawable();

  // Build methods for creating drawables.
  Drawable* create(const std::string& sprite_filename, sf::Vector2i offset,
                   sf::Vector2i size);
  Drawable* scale(double scale);
  Drawable* z_index(double z_index);
  Drawable* location(sf::Vector2f location);
  Drawable* rotate(double degrees);
  Drawable* hit_box(sf::Vector2f hit_box);

  double z_index() const {
    return z_index_;
  }

  // Update this component.
  virtual void Update(const thor::ActionMap<std::string>& map);

  // Draw this sprite onto the screen at its current location.
  virtual void Draw(sf::RenderWindow& window) const;

  // Get access to the internal sprite.
  sf::Sprite& Sprite() {
    return sprite_;
  }

  const sf::Sprite& Sprite() const {
    return sprite_;
  }

  sf::FloatRect HitBox() const {
    if (hit_box_.x <= 0 and hit_box_.y <= 0) {
      return sprite_.getGlobalBounds();
    }

    sf::FloatRect global_bounds = sprite_.getGlobalBounds();

    sf::FloatRect hit_box;
    hit_box.left = global_bounds.left + hit_box_.x;
    hit_box.top = global_bounds.top + hit_box_.y;
    hit_box.width = global_bounds.width - hit_box_.x;
    hit_box.height = global_bounds.height - hit_box_.y;

    return hit_box;
  }

  virtual void SetParameter(const std::string& key, const Json::Value& value);

protected:
  // The internal sprite used to draw the drawable to the screen.
  sf::Sprite sprite_;

  // What counts as 'hitting' this object?
  sf::Vector2f hit_box_;

  // A reference to the texture used by this drawable.
  std::shared_ptr<sf::Texture> texture_;

  // The location this drawable should be displayed on the z-axis.
  double z_index_;
};

}}  // namepsace engine::component

#endif  // _ENGINE_COMPONENT_DRAWABLE_H_
