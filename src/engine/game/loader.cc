#include "loader.h"

namespace engine {
namespace game {

namespace Loader {

using component::Component;
using component::Entity;

namespace {

// Load a file into a JSON document object.
Json::Value LoadJSON(const std::string& json_filename) {
  std::ifstream file(json_filename);
  Json::Value val;
  file >> val;
  return val;
}

} // namespace <anon>

Map LoadMap(const std::string& map_filepath) {
  Map map = Map();

  // Current working directory; switch back here when we are done.
  char cwd[PATH_MAX];
  getcwd(cwd, sizeof(cwd));

  // Move to the directory of the map file.
  std::string map_file_dir = map_filepath.substr(0, map_filepath.rfind('/'));
  std::string map_filename = map_filepath.substr(map_filepath.rfind('/') + 1);
  chdir(map_file_dir.c_str());

  // Load the map file (i.e. JSON).
  Json::Value map_json = LoadJSON(map_filename);

  // Load the map ID.
  LOG->info("Loading map {}...", map_json["name"]);
  map.name(map_json["name"].asString());

  // Load the entities.
  const Json::Value& entities = map_json["entities"];
  for (int i = 0; i < entities.size(); i++) {
    const Json::Value& entity_json = entities[i];

    Entity* entity = new Entity();

    LOG->debug("Loading entity {}", i);

    for (const std::string& component_name : entity_json.getMemberNames()) {
      const Json::Value& component_json = entity_json[component_name];

      Component* component = Component::Get(component_name);

      LOG->debug("Loading component {}", component_name);

      for (const std::string& param_name : component_json.getMemberNames()) {
        LOG->trace("Setting parameter {}...", param_name);
        component->SetParameter(param_name, component_json[param_name]);
      }

      LOG->debug("Done!");

      entity->AddComponent(component);
    }

    map.add(entity);
  }

  // Change back to the old directory.
  chdir(cwd);

  return map;
}

}  // namespace Loader

}}  // namespace engine::game
