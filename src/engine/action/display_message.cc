#include "display_message.h"

namespace engine {
namespace action {

DisplayMessage::DisplayMessage(const std::vector<std::string>& messages)
    : messages_(messages)
    , state_(DisplayMessage::WAITING_FOR_INTERACT_KEY_RELEASE)
    , next_state_(DisplayMessage::DISPLAYING_MESSAGE)
    , message_index_(0), characters_displayed_(0)
    , font_(utility::resource_loader::cache.acquire(
              thor::Resources::fromFile<sf::Font>("maps/fomt/fomt.ttf"))) {
  text_display_.setFont(*font_);
  text_display_.setCharacterSize(48);
  text_display_.setColor(sf::Color::Black);
  text_display_.setStyle(sf::Text::Bold);

  text_display_background_.setFillColor(sf::Color(248, 240, 112));
  text_display_background_.setOutlineThickness(5);
  text_display_background_.setOutlineColor(sf::Color(208, 192, 88));
}

DisplayMessage::~DisplayMessage() {

}

bool DisplayMessage::Update(Game& game) {
  // Update the message display (as always).
  text_display_background_.setSize(
    sf::Vector2f(game.window().getSize().x - 10,
                 (game.window().getSize().y / 4) - 10));
  int box_start_x = 5;
  int box_start_y = game.window().getSize().y -
                    text_display_background_.getSize().y - 5;
  text_display_background_.setPosition(
    game.window().mapPixelToCoords(sf::Vector2i(box_start_x, box_start_y)));
  text_display_.setPosition(
    game.window().mapPixelToCoords(sf::Vector2i(box_start_x + 15,
                                                box_start_y)));

  game.window().draw(text_display_background_);
  game.window().draw(text_display_);

  switch (state_) {
    case DisplayMessage::WAITING_FOR_INTERACT_KEY_PRESS:
      return WaitingForInteractKeyPress(game);
    case DisplayMessage::WAITING_FOR_INTERACT_KEY_RELEASE:
      return WaitingForInteractKeyRelease(game);
    case DisplayMessage::DISPLAYING_MESSAGE:
      return DisplayingMessage(game);
    case DisplayMessage::END:
    default:
      return true;
  }
}

const std::vector<std::string>& DisplayMessage::messages() const {
  return messages_;
}

bool DisplayMessage::WaitingForInteractKeyPress(Game& game) {
  if (game.action_map().isActive("interact")) {
    state_ = DisplayMessage::WAITING_FOR_INTERACT_KEY_RELEASE;
  }

  return false;
}

bool DisplayMessage::WaitingForInteractKeyRelease(Game& game) {
  if (game.action_map().isActive("interact")) {
    return false;
  }

  if (next_state_ == DisplayMessage::END) {
    message_index_++;
    characters_displayed_ = 0;
    next_state_ = DisplayMessage::DISPLAYING_MESSAGE;

    if (message_index_ == messages_.size()) {
      return true;
    }
  }

  state_ = DisplayMessage::DISPLAYING_MESSAGE;
  return false;
}

bool DisplayMessage::DisplayingMessage(Game& game) {
  // Only do this if the correct amount of time has passed.
  if (not game.action_map().isActive("running") and
      last_character_displayed_.getElapsedTime() < sf::milliseconds(100)) {
    return false;
  }

  // If we have already displayed all the characters, the wait for them to press
  // the interact key.
  if (characters_displayed_ == messages_[message_index_].size()) {
    state_ = DisplayMessage::WAITING_FOR_INTERACT_KEY_PRESS;
    next_state_ = DisplayMessage::END;
    return false;
  }

  // Display the next character.
  characters_displayed_++;
  text_display_.setString(
    messages_[message_index_].substr(0, characters_displayed_));

  last_character_displayed_.restart();
  return false;
}

}} // namespace engine::action

