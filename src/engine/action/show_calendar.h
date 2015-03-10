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
  static constexpr double kCalendarSizePercent = 5.0 / 6.0;
  static const int kCharacterSize = 32;
  static const int kTextOffsetLeft = 15;
  static const int kTextOffsetTop = -4;
  static const int kBackgroundTextOffsetTop = 0;

  ShowCalendar(Game& game);
  virtual ~ShowCalendar();

  virtual bool Update(Game& game);

  // Getters + Setters.
private:
  // Calendar background.
  sf::RectangleShape background_;
  sf::Text background_text_;

  // Blocks for each day in the calendar.
  int active_block_, start_block_;
  std::vector<sf::RectangleShape> blocks_;
  std::vector<sf::Text> block_text_;

  // Currently active season on the calendar.
  const game::Season* active_season_;
  int active_year_;

  // Bouncing selection hand.
  sf::Sprite selection_hand_;
  std::shared_ptr<sf::Texture> selection_hand_texture_;

  // Load the currently active season onto the calendar.
  void LoadActiveSeason(const sf::Vector2f calendar_size,
                        const sf::Vector2f calendar_start);

  // Given a season, load the next one in the sequence. If this is the last
  // season, then move to the next year.
  bool LoadNextSeason();

  // Given a season, load the previous one in the sequence. If this is the first
  // season, the move to the previous year. If there are no previous years, then
  // do nothing. Will return true if the season has changed.
  bool LoadPreviousSeason();

  // Get the background title given the required parameters.
  std::string BackgroundTitle(int year, const std::string& season_name);
};

}} // namespace engine::action

#endif  // _ENGINE_ACTION_SHOW_CALENDAR_H_
