#include "world.h"

namespace engine {
namespace game {

// Basic information.
std::string World::name_;

// Season information.
Day World::start_day_;
int World::current_day_, World::current_year_;
Season* World::current_season_;
std::vector<Season> World::seasons_;

namespace {

// Load a file into a JSON document object.
Json::Value LoadJSON(const std::string& json_filename) {
  std::ifstream file(json_filename);
  Json::Value val;
  file >> val;
  return val;
}

} // namespace

void World::Load(const std::string& world_filename) {
  LOG->info("Loading world {}...", world_filename);
  Json::Value world_json = LoadJSON(world_filename);

  /// Process the world.
  // Load season information.
  start_day_ = Season::StrToDay(world_json["season_start_day"].asString());

  Json::Value& seasons_json = world_json["seasons"];
  for (unsigned int i = 0; i < seasons_json.size(); i++) {
    seasons_.push_back(Season(i,
                              seasons_json[i]["name"].asString(),
                              seasons_json[i]["length"].asInt()));
  }

  current_season_ = &seasons_[0];
}

const std::string& World::name() {
  return name_;
}

const std::vector<Season>& World::seasons() {
  return seasons_;
}

const Season& World::season() {
  return *current_season_;
}

Day World::day() {
  return Season::IntToDay(
    (current_season_->start_day(start_day_, current_year_) + current_day_)
      % Day::N_DAYS);
}

Day World::start_day() {
  return start_day_;
}

int World::year() {
  return current_year_;
}

}} // namespace engine::game
