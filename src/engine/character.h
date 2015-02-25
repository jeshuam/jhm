#ifndef _ENGINE_CHARACTER_H_
#define _ENGINE_CHARACTER_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "entity/controllable.h"
#include "entity/drawable.h"
#include "texture_loader.h"

class Character : public Controllable
                , public Drawable {
public:
  Character();
  Character(const std::string& sprite_filename);
  Character(const std::string& sprite_filename, int x_offset, int y_offset,
            int width=-1, int height=-1);
  virtual ~Character();

  virtual void Draw(sf::RenderWindow& window) const;
  virtual void KeyPressed(const sf::Event& event);
  virtual void Update();
private:

  // Current character location on the map.
  int x_, y_;
  int x_velocity_, y_velocity_;
  bool moving_left_, moving_right_, moving_up_, moving_down_;
  int speed_ = 10;

  // Characters sprite (image).
  sf::Sprite sprite_;
};

#endif // _ENGINE_CHARACTER_H_
