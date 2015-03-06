#include "display_message.h"

namespace engine {
namespace action {

DisplayMessage::DisplayMessage(const std::string& message) : message_(message) {

}

DisplayMessage::~DisplayMessage() {

}

bool DisplayMessage::Update(Game& game) {
  // Wait until they aren't interacting...
  if (game.action_map().isActive("interact")) {
    return false;
  }

  // Display the message!
  // TODO(jeshua): Actually display this on the screen.
  LOG->info(message_);
  return true;
}

const std::string& DisplayMessage::message() const {
  return message_;
}

}} // namespace engine::action

