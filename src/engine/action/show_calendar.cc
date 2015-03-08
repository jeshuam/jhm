#include "show_calendar.h"

namespace engine {
namespace action {

const std::string ShowCalendar::DayToName(Day day) {
  switch (day) {
    case    MONDAY: return "MON";
    case   TUESDAY: return "TUE";
    case WEDNESDAY: return "WED";
    case  THURSDAY: return "THU";
    case    FRIDAY: return "FRI";
    case  SATURDAY: return "SAT";
    case    SUNDAY: return "SUN";
  }

  LOG->emerg("Invalid day {} given to DayToName(Day)!", day);
  throw std::logic_error("Invalid day");
}

const sf::Color ShowCalendar::DayToColor(Day day) {
  switch (day) {
    case    MONDAY:
    case   TUESDAY:
    case WEDNESDAY:
    case  THURSDAY:
    case    FRIDAY: return sf::Color(64, 64, 64);
    case  SATURDAY: return sf::Color(0, 0, 208);
    case    SUNDAY: return sf::Color(200, 0, 0);
  }

  LOG->emerg("Invalid day {} given to DayToColor(Day)!", day);
  throw std::logic_error("Invalid day");
}

ShowCalendar::Day ShowCalendar::GetDay(int day) {
  switch (day) {
    case 0: return MONDAY;
    case 1: return TUESDAY;
    case 2: return WEDNESDAY;
    case 3: return THURSDAY;
    case 4: return FRIDAY;
    case 5: return SATURDAY;
    case 6: return SUNDAY;
  }

  LOG->emerg("Invalid day {} given to GetDay(int)!", day);
  throw std::logic_error("Invalid day");
}

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

  // There will be a 7x6 grid of rectangles for the actual dates. Work out the
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
  int n_cols = 7;
  int n_rows = 7;

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
        switch (GetDay(col)) {
          case    MONDAY:
            outline = sf::Color(248, 176, 80);
            fill =    sf::Color(248, 200, 176);
            break;
          case   TUESDAY:
            outline = sf::Color(248, 184, 0);
            fill =    sf::Color(248, 232, 136);
            break;
          case WEDNESDAY:
            outline = sf::Color(88, 248, 24);
            fill =    sf::Color(208, 248, 136);
            break;
          case  THURSDAY:
            outline = sf::Color(8, 248, 144);
            fill =    sf::Color(192, 248, 200);
            break;
          case    FRIDAY:
            outline = sf::Color(32, 248, 248);
            fill =    sf::Color(192, 248, 240);
            break;
          case  SATURDAY:
            outline = sf::Color(152, 192, 248);
            fill =    sf::Color(208, 224, 248);
            break;
          case    SUNDAY:
            outline = sf::Color(248, 96, 232);
            fill =    sf::Color(248, 192, 248);
            break;
        }

        block.setOutlineColor(outline);
        block.setOutlineThickness(-kDateBlockBorderThickness);
        block.setFillColor(fill);
      }

      spring_blocks_.push_back(block);

      /// Add the text for this cell.
      // Row == 0 ==> show the days of the week.
      if (row == 0) {
        sf::Text weekday_text;
        spring_blocks_.back().setOutlineThickness(0);
        weekday_text.setFont(*font);
        weekday_text.setString(DayToName(GetDay(col)));
        weekday_text.setCharacterSize(48);
        weekday_text.setColor(DayToColor(GetDay(col)));
        weekday_text.setStyle(sf::Text::Bold);
        weekday_text.setPosition(
          x + kDateBlockBorderThickness + (indiv_date_block_size_.x / 2.0)
            - (weekday_text.getGlobalBounds().width) + 25,
          y + kDateBlockBorderThickness + (indiv_date_block_size_.y / 2.0)
            - (weekday_text.getGlobalBounds().height) - 5
        );

        spring_block_text_.push_back(weekday_text);
        continue;
      }

      else if (row == 1) {
        // Don't start counting days until we get to the first day of the
        // season.
        if (GetDay(col) == spring_start_) {
          current_date = 1;
        }
      }

      // If we are drawing a date...
      if (current_date > 0 and current_date <= spring_days_) {
        sf::Text date_text;
        date_text.setFont(*font);
        date_text.setString(std::to_string(current_date));
        date_text.setCharacterSize(48);
        date_text.setColor(DayToColor(GetDay(col)));
        date_text.setStyle(sf::Text::Bold);
        date_text.setPosition(
          x + kDateBlockBorderThickness + (indiv_date_block_size_.x / 2.0)
            - (date_text.getGlobalBounds().width) + 25,
          y + kDateBlockBorderThickness + (indiv_date_block_size_.y / 2.0)
            - (date_text.getGlobalBounds().height) - 5
        );

        spring_block_text_.push_back(date_text);
        current_date++;
      }
    }
  }
}

ShowCalendar::~ShowCalendar() {

}

bool ShowCalendar::Update(Game& game) {
  if (game.action_map().isActive("back")) {
    return true;
  }

  // Display the background.
  game.window().draw(background_);

  // Display the grid of dates.
  for (const sf::RectangleShape& block : spring_blocks_) {
    game.window().draw(block);
  }

  // Display the text.
  for (const sf::Text& text : spring_block_text_) {
    game.window().draw(text);
  }

  return false;
}

}} // namespace engine::action
