#ifndef _ENGINE_ACTION_SHOW_CALENDAR_H_
#define _ENGINE_ACTION_SHOW_CALENDAR_H_

#include <vector>

#include "engine/action/action.h"
#include "engine/game/world.h"
#include "engine/utility/resource_loader.h"

namespace engine {
namespace action {

class ShowCalendar : public Action {
public:
  static const int kTopPadding = 40;
  static const int kBorderThickness = 5;
  static const int kDateBlockBorderThickness = 2;
  static const int kDateBlockPadding = 1; // pixels between date blocks
  static constexpr double kCalendarSizePercent = 19.0 / 20.0;

  ShowCalendar(Game& game);
  virtual ~ShowCalendar();

  virtual bool Update(Game& game);

  // Getters + Setters.
private:
  // Calendar background.
  sf::RectangleShape background_;
  std::vector<sf::RectangleShape> blocks_;
  std::vector<sf::Text> block_text_;
};

}} // namespace engine::action

#endif  // _ENGINE_ACTION_SHOW_CALENDAR_H_
