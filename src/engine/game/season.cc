#include "season.h"

#include "engine/game/world.h"

namespace engine {
namespace game {

const std::string& Season::name() const {
  return name_;
}

int Season::length() const {
  return length_;
}

Day Season::start_day(Day start_day, int year) const {
  // Calculate the number of days in a year. Also add up how many days have
  // passed in seasons BEFORE this one.
  int days_per_year = 0, days_passed = 0;
  for (const Season& season : World::seasons()) {
    days_per_year += season.length();

    if (season.id_ < id_) {
      days_passed += season.length();
    }
  }

  // At least year * days_per_year days have passed so far.
  days_passed += days_per_year * year;

  // Work out the first day of THIS season relative to the first day ever.
  return IntToDay((World::start_day() + days_passed) % Day::N_DAYS);
}

Day Season::IntToDay(int day) {
  switch (day) {
    case 0: return Day::MONDAY;
    case 1: return Day::TUESDAY;
    case 2: return Day::WEDNESDAY;
    case 3: return Day::THURSDAY;
    case 4: return Day::FRIDAY;
    case 5: return Day::SATURDAY;
    case 6: return Day::SUNDAY;
  }

  LOG->emerg("Invalid day '{}' given to IntToDay!", day);
  throw std::logic_error("Invalid day");
}

Day Season::StrToDay(const std::string& day) {
  if (day == "MONDAY") {
    return Day::MONDAY;
  } else if (day == "TUESDAY") {
    return Day::TUESDAY;
  } else if (day == "WEDNESDAY") {
    return Day::WEDNESDAY;
  } else if (day == "THURSDAY") {
    return Day::THURSDAY;
  } else if (day == "FRIDAY") {
    return Day::FRIDAY;
  } else if (day == "SATURDAY") {
    return Day::SATURDAY;
  } else if (day == "SUNDAY") {
    return Day::SUNDAY;
  }

  LOG->emerg("Invalid day '{}' given to StrToDay!", day);
  throw std::logic_error("Invalid day");
}

sf::Color Season::DayToColor(Day day) {
  switch (day) {
    case    MONDAY:
    case   TUESDAY:
    case WEDNESDAY:
    case  THURSDAY:
    case    FRIDAY: return sf::Color(64, 64, 64);
    case  SATURDAY: return sf::Color(0, 0, 208);
    case    SUNDAY: return sf::Color(200, 0, 0);
    default: break;
  }

  LOG->emerg("Invalid day {} given to DayToColor!", day);
  throw std::logic_error("Invalid day");
}

std::string Season::DayToStr(Day day) {
  switch (day) {
    case    MONDAY: return "MON";
    case   TUESDAY: return "TUE";
    case WEDNESDAY: return "WED";
    case  THURSDAY: return "THU";
    case    FRIDAY: return "FRI";
    case  SATURDAY: return "SAT";
    case    SUNDAY: return "SUN";
    default: break;
  }

  LOG->emerg("Invalid day {} given to DayToName!", day);
  throw std::logic_error("Invalid day");
}

}} // namespace engine::game
