#ifndef _ENGINE_GAME_SEASON_H_
#define _ENGINE_GAME_SEASON_H_

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "log.h"

namespace engine {
namespace game {

// Use a namespace becasuse there isn't another good way to do it.
enum Day {
  MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY, N_DAYS,
};

// Container class for Season information.
class Season {
public:
  // Functions for dealing with Day's.
  static Day IntToDay(int day);
  static Day StrToDay(const std::string& day);
  static sf::Color DayToColor(Day day);
  static std::string DayToStr(Day day);

  // Let other things destroy seasons.
  Season(int id, const std::string& name, int length) : id_(id)
                                                      , name_(name)
                                                      , length_(length) { }
  Season() { }
  ~Season() { }

  // Getters for information.
  const std::string& name() const;
  int length() const;
  Day start_day(Day start_day, int year=0) const;

private:
  /// Details.
  // Unique ID of the season. Later seasons will have a higher ID.
  int id_;

  // Name of the season (e.g. Winter, Spring, XXX).
  std::string name_;

  // Number of days in the season.
  int length_;
};

}} // namespace engine::game

#endif  // _ENGINE_GAME_SEASON_H_
