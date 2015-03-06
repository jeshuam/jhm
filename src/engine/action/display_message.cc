#include "display_message.h"

namespace engine {
namespace action {

DisplayMessage::DisplayMessage(const std::string& message) : message_(message) {

}

DisplayMessage::~DisplayMessage() {

}

bool DisplayMessage::Update(Game& game) {
  return false;
}

const std::string& DisplayMessage::message() const {
  return message_;
}

}} // namespace engine::action

