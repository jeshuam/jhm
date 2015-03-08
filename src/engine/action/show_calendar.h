#ifndef _ENGINE_ACTION_SHOW_CALENDAR_H_
#define _ENGINE_ACTION_SHOW_CALENDAR_H_

#include <vector>

#include "engine/action/action.h"
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
  enum Day {
    MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY
  };

  static const std::string DayToName(Day day);
  static const sf::Color DayToColor(Day day);
  static Day GetDay(int day);

  ShowCalendar(Game& game);
  virtual ~ShowCalendar();

  virtual bool Update(Game& game);

  // Getters + Setters.
private:
  // Calendar background.
  sf::RectangleShape background_;
  static const Day spring_start_ = MONDAY;
  static const int spring_days_ = 45;
  std::vector<sf::RectangleShape> spring_blocks_;
  std::vector<sf::Text> spring_block_text_;
};

}} // namespace engine::action

#endif  // _ENGINE_ACTION_SHOW_CALENDAR_H_
