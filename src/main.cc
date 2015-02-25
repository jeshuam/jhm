#include "jhm.h"
#include "log.h"

std::shared_ptr<spdlog::logger> LOG;

int main(int argc, char** argv) {
  spdlog::set_level(spdlog::level::trace);
  LOG = spdlog::stdout_logger_mt("log");

  // Run the game.
  JHM game;
  game.Run();
}
