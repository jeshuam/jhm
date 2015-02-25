#include "jhm.h"

#include "logging/easylogging++.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char** argv) {
  START_EASYLOGGINGPP(argc, argv);

  // Run the game.
  JHM game;
  game.Run();
}
