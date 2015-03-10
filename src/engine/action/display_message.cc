#include "display_message.h"

namespace engine {
namespace action {

DisplayMessage::DisplayMessage(Game& game,
                               const std::vector<std::string>& messages)
    : messages_(messages)
    , state_(DisplayMessage::WAITING_FOR_INTERACT_KEY_RELEASE)
    , next_state_(DisplayMessage::DISPLAYING_MESSAGE)
    , message_index_(0), characters_displayed_(0), start_offset_(0)
    , current_row_(&text_display_row_1_)
    , font_(utility::resource_loader::cache.acquire(
              thor::Resources::fromFile<sf::Font>("maps/fomt/fomt.ttf"))) {
  text_display_row_1_.setFont(*font_);
  text_display_row_1_.setCharacterSize(32);
  text_display_row_1_.setColor(sf::Color::Black);
  text_display_row_1_.setStyle(sf::Text::Bold);

  text_display_row_2_.setFont(*font_);
  text_display_row_2_.setCharacterSize(32);
  text_display_row_2_.setColor(sf::Color::Black);
  text_display_row_2_.setStyle(sf::Text::Bold);

  text_display_background_.setFillColor(sf::Color(248, 240, 112));
  text_display_background_.setOutlineThickness(-kMessageBorderSize);
  text_display_background_.setOutlineColor(sf::Color(208, 192, 88));

  // Get the screen coordinates to display the message on.
  sf::Vector2u window_size = game.window().getSize();
  double message_height_percent = 1.0 / 4.0;

  // Message box starts at the top left of the screen.
  sf::Vector2f message_start(game.window().mapPixelToCoords({
    int(window_size.x * 0.0),
    int(window_size.y * (1.0 - message_height_percent))
  }));

  // Message box ends at the bottom right of the screen.
  sf::Vector2f message_end(game.window().mapPixelToCoords({
    int(window_size.x * 1.0),
    int(window_size.y * 1.0)
  }));

  sf::Vector2f message_size(message_end.x - message_start.x,
                            message_end.y - message_start.y);

  // Update the message display (as always).
  text_display_background_.setSize(message_size);
  text_display_background_.setPosition(message_start);

  sf::Vector2f text_start_1({message_start.x + kMessagePaddingX,
                             message_start.y + kMessagePaddingY});
  sf::Vector2f text_start_2({message_start.x + kMessagePaddingX,
                             message_start.y + 45 + kMessagePaddingY});
  text_display_row_1_.setPosition(text_start_1);
  text_display_row_2_.setPosition(text_start_2);
}

DisplayMessage::~DisplayMessage() {

}

bool DisplayMessage::Update(Game& game) {
  game.window().draw(text_display_background_);
  game.window().draw(text_display_row_1_);
  game.window().draw(text_display_row_2_);

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
    current_row_ = &text_display_row_1_;
    text_display_row_1_.setString("");
    text_display_row_2_.setString("");
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
  std::string new_string = messages_[message_index_].substr(
    0 + start_offset_, characters_displayed_ - start_offset_);
  current_row_->setString(new_string);

  // If the last character displayed was a space, check the next word (all
  // characters up to but not including the next space) and determine whether
  // we can fit the whole word on the current row. If we can't, move to the
  // next row.
  if (new_string.back() == ' ') {
    // Find the next word.
    size_t next_space = messages_[message_index_].find(
      ' ', characters_displayed_);
    if (next_space == std::string::npos) {
      next_space = messages_[message_index_].size();
    }

    std::string next_word = messages_[message_index_].substr(
      characters_displayed_, next_space - characters_displayed_);

    // Add the new word to the message box and check the bounds. Kinda brute
    // forcey but it shouldn't slow things down that much if the text isn't
    // actually rendered.
    current_row_->setString(new_string + " " + next_word);

    // Get the new dimensions of the string box.
    sf::FloatRect text_box_size = current_row_->getLocalBounds();

    // Reset the current row.
    current_row_->setString(new_string);

    // If the text box size is too large, then switch to the next line.
    if (text_box_size.width >= text_display_background_.getSize().x -
                                      kMessageBorderSize - kMessagePaddingX) {
      current_row_ = &text_display_row_2_;
      start_offset_ = characters_displayed_;
    }
  }

  last_character_displayed_.restart();
  return false;
}

}} // namespace engine::action

