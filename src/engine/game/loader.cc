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

// Load a list of components into a new entity and return it.
Entity* LoadComponents(const Json::Value& components_json) {
  Entity* entity = new Entity();

  for (const std::string& component_name : components_json.getMemberNames()) {
    const Json::Value& component_json = components_json[component_name];

    Component* component = Component::Get(component_name);

    LOG->debug("Loading component {}", component_name);

    for (const std::string& param_name : component_json.getMemberNames()) {
      LOG->debug("Setting parameter {}...", param_name);
      component->SetParameter(param_name, component_json[param_name]);
    }

    LOG->debug("Done!");

    entity->AddComponent(component);
  }

  return entity;
}

} // namespace <anon>

Map& LoadMap(const std::string& map_filepath) {
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
  LOG->info("Loading map {}...", map_filename);
  Map* map = new Map(map_json["name"].asString());

  // Load the entities.
  const Json::Value& entities = map_json["entities"];
  for (int i = 0; i < entities.size(); i++) {
    LOG->debug("Processing entity {}", i);
    map->add(LoadComponents(entities[i]));
  }

  // Change back to the old directory.
  chdir(cwd);

  return *map;
}

void LoadSave(const std::string& save_filepath) {
  // Current working directory; switch back here when we are done.
  char cwd[PATH_MAX];
  getcwd(cwd, sizeof(cwd));

  // Move to the directory of the map file.
  std::string save_file_dir = save_filepath.substr(0, save_filepath.rfind('/'));
  std::string save_filename = save_filepath.substr(save_filepath.rfind('/') +1);
  chdir(save_file_dir.c_str());

  LOG->info("Loading save file {}...", save_filename);

  // Load the save file (i.e. JSON).
  Json::Value save_json = LoadJSON(save_filename);

  // Load the drawable component.
  Entity* player = LoadComponents(save_json["components"]);

  // Add this player to the requested map.
  Map::Get(save_json["map"].asString()).add(player).Activate();

  // Change back to the old directory.
  chdir(cwd);
}

}  // namespace Loader

}}  // namespace engine::game
