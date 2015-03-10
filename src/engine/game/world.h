#ifndef _ENGINE_GAME_WORLD_H_
#define _ENGINE_GAME_WORLD_H_

#include <fstream>
#include <string>
#include <vector>

#include <json/json.h>

#include "engine/game/season.h"
#include "log.h"

namespace engine {
namespace game {

// The game world contains information about static things within the game.
// These aren't entities, they a more like properties of the world. This should
// include things like:
//     - Season information (order, number, names, days/season, starting day).
//
// World is a singleton. It basically acts as a configuration class which should
// be loaded from a JSON file.
class World {
public:
  static void Load(const std::string& world_filename="");

  /// Query the World's information.
  // Basic information.
  static const std::string& name();

  // Season information.
  static const std::vector<Season>& seasons();
  static const Season& season();
  static Day day();
  static int day_of_season();
  static Day start_day();
  static int year();

private:
  World() {}
  ~World() {}

  /// World information.
  // Basic information.
  static std::string name_;

  // Season information.
  static Day start_day_;
  static int current_day_, current_year_;
  static Season* current_season_;
  static std::vector<Season> seasons_;

};

}} // namespace engine::game

#endif  // _ENGINE_GAME_WORLD_H_
