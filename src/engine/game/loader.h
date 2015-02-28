#ifndef _ENGINE_GAME_LOADER_H_
#define _ENGINE_GAME_LOADER_H_

#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>

#include "engine/json/json.h"

#include "engine/game/map.h"
#include "log.h"

namespace engine {
namespace game {

// Utility for loading game maps and save games (etc.). These methods will
// basically just construct a series of entities which have been defined in a
// configuration file.
namespace Loader {

// Load a map from a configuration file. This will contain all _statc_ things in
// the area (such as boundaries, backgrounds, shipping crates etc.).
Map LoadMap(const std::string& map_filename);

}  // namespace Loader

}}  // namespace engine::game

#endif  // _ENGINE_UTILITY_LOADER_H_
