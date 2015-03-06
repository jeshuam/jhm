#ifndef _ENGINE_ACTION_DISPLAY_MESSAGE_H_
#define _ENGINE_ACTION_DISPLAY_MESSAGE_H_

#include "engine/action/action.h"

namespace engine {
namespace action {

class DisplayMessage : public Action {
public:
  // Constructor + Destructor.
  DisplayMessage(const std::string& message);
  virtual ~DisplayMessage();

  // Manage the message.
  virtual bool Update(Game& game);

  // Getters + Setters.
  const std::string& message() const;

private:
  std::string message_;
};

}} // namespace engine::action

#endif  // _ENGINE_ACTION_DISPLAY_MESSAGE_H_
