#ifndef _ENGINE_ACTION_DISPLAY_MESSAGE_H_
#define _ENGINE_ACTION_DISPLAY_MESSAGE_H_

#include "engine/action/action.h"
#include "engine/utility/resource_loader.h"

#include "game.h"

namespace engine {
namespace action {

class DisplayMessage : public Action {
public:
  static const int kMessageBorderSize = 5;
  static const int kMessagePaddingX = 15;
  static const int kMessagePaddingY = 5;

  enum State {
    // We are currently waiting for the interact key to be released.
    WAITING_FOR_INTERACT_KEY_RELEASE,

    // Wait for the interact key to be pressed.
    WAITING_FOR_INTERACT_KEY_PRESS,

    // We are currently displaying the message. This will be the state during
    // the whole drawing animation (e.g. revealing the text a little bit at a
    // time).
    DISPLAYING_MESSAGE,

    // We are in the ending state (yay).
    END,
  };

  // Constructor + Destructor.
  DisplayMessage(Game& game, const std::vector<std::string>& messages);
  virtual ~DisplayMessage();

  // Manage the message.
  virtual bool Update(Game& game);

  // Getters + Setters.
  const std::vector<std::string>& messages() const;

private:
  std::vector<std::string> messages_;

  // Current state we are in.
  State state_;
  State next_state_;

  // How much of the message we have already displayed.
  unsigned int message_index_;
  unsigned int characters_displayed_;
  unsigned int start_offset_;
  sf::Clock last_character_displayed_;

  // On-screen text...
  sf::Text* current_row_;
  sf::Text text_display_row_1_;
  sf::Text text_display_row_2_;
  sf::RectangleShape text_display_background_;
  std::shared_ptr<sf::Font> font_;

  // State methods.
  bool WaitingForInteractKeyPress(Game& game);
  bool WaitingForInteractKeyRelease(Game& game);
  bool DisplayingMessage(Game& game);
};

}} // namespace engine::action

#endif  // _ENGINE_ACTION_DISPLAY_MESSAGE_H_
