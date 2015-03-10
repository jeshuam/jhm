#include "show_calendar.h"

namespace engine {
namespace action {

using namespace game;

ShowCalendar::ShowCalendar(Game& game) {
  // Setup the background.
  background_.setFillColor(sf::Color(248, 240, 112));
  background_.setOutlineThickness(-kBorderThickness);
  background_.setOutlineColor(sf::Color(208, 192, 88));

  // Get the screen coordinates to display the calendar on.
  double window_x = game.window().getSize().x;
  double window_y = game.window().getSize().y;
  sf::Vector2f calendar_start(game.window().mapPixelToCoords({
    int(window_x * (1.0 - kCalendarSizePercent)),
    int(window_y * (1.0 - kCalendarSizePercent))
  }));

  sf::Vector2f calendar_end(game.window().mapPixelToCoords({
    int(window_x * (kCalendarSizePercent)),
    int(window_y * (kCalendarSizePercent))
  }));

  sf::Vector2f calendar_size(calendar_end.x - calendar_start.x,
                             calendar_end.y - calendar_start.y);

  // Draw the background.
  background_.setSize(calendar_size);
  background_.setPosition(calendar_start);

  // Set the background text.
  std::shared_ptr<sf::Font> font = utility::resource_loader::cache.acquire(
    thor::Resources::fromFile<sf::Font>("maps/fomt/fomt.ttf"));
  background_text_.setFont(*font);
  background_text_.setCharacterSize(48);
  background_text_.setColor(sf::Color::Black);
  background_text_.setString(BackgroundTitle(World::year(),
                                             World::season().name()));

  float bg_w = background_.getSize().x;
  float bg_x = background_.getPosition().x;
  float bg_y = background_.getPosition().y;
  background_text_.setPosition(
    bg_x + (bg_w / 2.0) - (background_text_.getGlobalBounds().width / 2.0),
    bg_y - kBorderThickness
  );

  // The active season always starts as the current season.
  active_season_ = &World::season();
  active_year_ = World::year();

  // Load the current season.
  LoadActiveSeason(background_.getSize(), background_.getPosition());
  active_block_ = start_block_ + World::day_of_season();

  // Show a bouncing selected arrow.
  selection_hand_texture_ = utility::resource_loader::cache.acquire(
    thor::Resources::fromFile<sf::Texture>(
      "maps/fomt/assets/calendar-hand.png"));
  selection_hand_.setTexture(*selection_hand_texture_);
  selection_hand_.setScale(2.0, 2.0);
}

ShowCalendar::~ShowCalendar() {

}

bool ShowCalendar::Update(Game& game) {
  if (game.action_map().isActive("back")) {
    return true;
  }

  int season_end_block = start_block_ + active_season_->length() - 1;
  if (game.action_map().isActive("up")) {
    // If we move the active block up one row (subtract seven) and it isn't
    // before the starting block, the do it.
    if (active_block_ - 7 >= start_block_) {
      active_block_ -= 7;
    } else {
      if (LoadPreviousSeason()) {
        LoadActiveSeason(background_.getSize(), background_.getPosition());

        // If the position of the active block was AFTERR where the new start
        // block is, we need to focus a block on the second row.
        int end_block = start_block_ + active_season_->length() - 1;
        int end_block_row = end_block - (end_block % 7);
        active_block_ = end_block_row + active_block_ % 7;

        // If the active block appears BEFORE the start block and we can't put
        // it on the next row (because it is past the end block) then just make
        // the start block to active block. If we _can_ put it on the next row,
        // then do that instead.
        if (active_block_ > end_block) {
          if (active_block_ - 7 < start_block_) {
            active_block_ = end_block;
          } else {
            active_block_ -= 7;
          }
        }

        // If the active block is after the end block (this can only happen with
        // very short months...) then just display it at the end block.
        else if (active_block_ < start_block_) {
          active_block_ = start_block_;
        }
      }
    }
  }

  if (game.action_map().isActive("down")) {
    // If we move the active block down one row (add seven) and it isn't after
    // the finishing block, the do it.
    if (active_block_ + 7 <= season_end_block) {
      active_block_ += 7;
    } else {
      if (LoadNextSeason()) {
        LoadActiveSeason(background_.getSize(), background_.getPosition());

        // If the position of the active block was BEFORE where the new start
        // block is, we need to focus a block on the second row.
        int start_block_row = start_block_ - (start_block_ % 7);
        active_block_ = start_block_row + active_block_ % 7;

        // If the active block appears BEFORE the start block and we can't put
        // it on the next row (because it is past the end block) then just make
        // the start block to active block. If we _can_ put it on the next row,
        // then do that instead.
        int end_block = start_block_ + active_season_->length() - 1;
        if (active_block_ < start_block_) {
          if (active_block_ + 7 > end_block) {
            active_block_ = start_block_;
          } else {
            active_block_ += 7;
          }
        }

        // If the active block is after the end block (this can only happen with
        // very short months...) then just display it at the end block.
        else if (active_block_ > end_block) {
          active_block_ = end_block;
        }
      }
    }
  }

  if (game.action_map().isActive("right")) {
    // If the active block isn't the last block in a row or the last block
    // of the season, then add one (move right).
    if (active_block_ % 7 < 6 and active_block_ < season_end_block) {
      active_block_++;
    }
  }

  if (game.action_map().isActive("left")) {
    // If the active block isn't the first block in a row or the first block
    // of the season, the subtract one (move left).
    if (active_block_ % 7 > 0 and active_block_ > start_block_) {
      active_block_--;
    }
  }

  // Display the background.
  game.window().draw(background_);
  game.window().draw(background_text_);

  // Display the grid of dates.
  for (const sf::RectangleShape& block : blocks_) {
    game.window().draw(block);
  }

  // Display the text.
  for (const sf::Text& text : block_text_) {
    game.window().draw(text);
  }

  // Decide where to put the hand, and put it there.
  const sf::Vector2f pos = blocks_[active_block_].getPosition();
  const sf::Vector2f size = blocks_[active_block_].getSize();
  selection_hand_.setPosition(
    pos.x - selection_hand_.getGlobalBounds().width,
    pos.y + (size.y / 2.0) - (selection_hand_.getGlobalBounds().height / 2.0)
  );
  game.window().draw(selection_hand_);

  return false;
}

void ShowCalendar::LoadActiveSeason(const sf::Vector2f calendar_size,
                                    const sf::Vector2f calendar_start) {
  // Remove all blocks that currently exist.
  blocks_.clear();
  block_text_.clear();

  // There will be a 7x7 grid of rectangles for the actual dates. Work out the
  // size of each block.
  sf::Vector2f date_block_size_(
    calendar_size.x - (2 * kBorderThickness),
    calendar_size.y - (2 * kBorderThickness) - kTopPadding);

  // Work out the initial (x, y) location of the first block, and we can work
  // from there.
  sf::Vector2f date_block_start_(
    calendar_start.x + kBorderThickness,
    calendar_start.y + kBorderThickness + kTopPadding);

  // Draw the date blocks from left-to-right, top-to-bottom.
  const int n_cols = 7;
  const int n_rows = 7;

  // Work out the size of an individual date block.
  sf::Vector2f indiv_date_block_size_(
    date_block_size_.x / n_cols - kDateBlockPadding * (n_cols - 2),
    date_block_size_.y / n_rows - kDateBlockPadding * (n_rows - 2)
  );

  // Load the font to apply to all text.
  std::shared_ptr<sf::Font> font = utility::resource_loader::cache.acquire(
    thor::Resources::fromFile<sf::Font>("maps/fomt/fomt.ttf"));

  int current_date = 0;
  for (int row = 0; row < n_rows; row++) {
    float y = date_block_start_.y
              + (row * (date_block_size_.y / n_rows))
              + kDateBlockPadding * row;
    for (int col = 0; col < n_cols; col++) {
      float x = date_block_start_.x
                + (col * (date_block_size_.x / n_cols))
                + kDateBlockPadding * col;

      sf::RectangleShape block(indiv_date_block_size_);
      block.setPosition({x, y});
      block.setFillColor(sf::Color::Transparent);

      // Set the color of the block.
      if (row > 0) {
        sf::Color outline, fill;
        switch (Season::IntToDay(col)) {
          case    Day::MONDAY:
            outline = sf::Color(248, 176, 80);
            fill =    sf::Color(248, 200, 176);
            break;
          case   Day::TUESDAY:
            outline = sf::Color(248, 184, 0);
            fill =    sf::Color(248, 232, 136);
            break;
          case Day::WEDNESDAY:
            outline = sf::Color(88, 248, 24);
            fill =    sf::Color(208, 248, 136);
            break;
          case  Day::THURSDAY:
            outline = sf::Color(8, 248, 144);
            fill =    sf::Color(192, 248, 200);
            break;
          case    Day::FRIDAY:
            outline = sf::Color(32, 248, 248);
            fill =    sf::Color(192, 248, 240);
            break;
          case  Day::SATURDAY:
            outline = sf::Color(152, 192, 248);
            fill =    sf::Color(208, 224, 248);
            break;
          case    Day::SUNDAY:
            outline = sf::Color(248, 96, 232);
            fill =    sf::Color(248, 192, 248);
            break;
          default:
            break;
        }

        block.setOutlineColor(outline);
        block.setOutlineThickness(-kDateBlockBorderThickness);
        block.setFillColor(fill);
      }

      blocks_.push_back(block);

      /// Add the text for this cell.
      // Row == 0 ==> show the days of the week.
      if (row == 0) {
        sf::Text weekday_text;
        blocks_.back().setOutlineThickness(0);
        weekday_text.setFont(*font);
        weekday_text.setString(Season::DayToStr(Season::IntToDay(col)));
        weekday_text.setCharacterSize(48);
        weekday_text.setColor(Season::DayToColor(Season::IntToDay(col)));
        weekday_text.setStyle(sf::Text::Bold);
        weekday_text.setPosition(
          x + kDateBlockBorderThickness + (indiv_date_block_size_.x / 2.0)
            - (weekday_text.getGlobalBounds().width) + 25,
          y + kDateBlockBorderThickness + (indiv_date_block_size_.y / 2.0)
            - (weekday_text.getGlobalBounds().height) - 5
        );

        block_text_.push_back(weekday_text);
        continue;
      }

      else if (row == 1) {
        // Don't start counting days until we get to the first day of the
        // season.
        Day start_day = active_season_->start_day(World::start_day(),
                                                  active_year_);
        if (Season::IntToDay(col) == start_day) {
          current_date = 1;
          start_block_ = blocks_.size() - 1;
        }
      }

      // If we are drawing a date...
      int season_length = active_season_->length();
      if (current_date > 0 and current_date <= season_length) {
        sf::Text date_text;
        date_text.setFont(*font);
        date_text.setString(std::to_string(current_date));
        date_text.setCharacterSize(48);
        date_text.setColor(Season::DayToColor(Season::IntToDay(col)));
        date_text.setStyle(sf::Text::Bold);
        date_text.setPosition(
          x + kDateBlockBorderThickness + (indiv_date_block_size_.x / 2.0)
            - (date_text.getGlobalBounds().width) + 25,
          y + kDateBlockBorderThickness + (indiv_date_block_size_.y / 2.0)
            - (date_text.getGlobalBounds().height) - 5
        );

        block_text_.push_back(date_text);
        current_date++;
      }
    }
  }

  // Update the season text.
  background_text_.setString(BackgroundTitle(active_year_,
                                             active_season_->name()));
}

bool ShowCalendar::LoadNextSeason() {
  // Find the current season in the list.
  auto location = std::find(World::seasons().begin(), World::seasons().end(),
                            *active_season_);

  // If we aren't at the end, just return the next one.
  if (location + 1 != World::seasons().end()) {
    active_season_ = &(*(location + 1));
    return true;
  }

  // Otherwise, we need to add one to the year and get the first one. Only have
  // at most 2 years lookahead, though.
  else if (active_year_ + 1 < World::year() + 2) {
    active_year_++;
    active_season_ = &World::seasons().front();
    return true;
  }

  return false;
}

bool ShowCalendar::LoadPreviousSeason() {
  // Find the current season in the list.
  auto location = std::find(World::seasons().begin(), World::seasons().end(),
                            *active_season_);

  // If we aren't at the end, just return the next one.
  if (location != World::seasons().begin()) {
    active_season_ = &(*(location - 1));
    return true;
  }

  // Otherwise, we need to add one to the year and get the first one.
  else if (active_year_ > 0) {
    active_year_--;
    active_season_ = &World::seasons().back();
    return true;
  }

  return false;
}

std::string ShowCalendar::BackgroundTitle(int year,
                                          const std::string& season_name) {
  std::stringstream stream;
  stream << "Year " << year + 1 << "    " << season_name;
  return stream.str();
}

}} // namespace engine::action
