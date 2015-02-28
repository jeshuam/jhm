#include "loader.h"

namespace engine {
namespace game {

namespace Loader {

namespace {

// Load a file into a JSON document object.
Json::Value LoadJSON(const std::string& json_filename) {
  std::ifstream file(json_filename);
  Json::Value val;
  file >> val;
  return val;
}

} // namespace <anon>

Map LoadMap(const std::string& map_filename) {
  Map map = Map();

  // Load the map file (i.e. JSON).
  Json::Value map_json = LoadJSON(map_filename);

  // Load the map ID.
  map.name(map_json.get("name", "Fail").asString());

  // Load the entities.
  Json::Value entities = map_json["entities"];
  for (int i = 0; i < entities.size(); i++) {
    Json::Value entity = entities[i];

    for (const std::string& component_name : entity.getMemberNames()) {
      if (component_name == "drawable") {

      }
    }
  }

  return map;
}

}  // namespace Loader

}}  // namespace engine::game
