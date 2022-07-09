#pragma once

#include <tension/core/app.h>

namespace tension {
namespace core {
namespace app {

#define DEF_APP_CALLBACKS                                                      \
  CALLBACK_PROPERTY(ApplicationStart);                                         \
  CALLBACK_PROPERTY(ApplicationPause);                                         \
  CALLBACK_PROPERTY(ApplicationResume);                                        \
  CALLBACK_PROPERTY(WindowResize);                                             \
  CALLBACK_PROPERTY(FrameUpdate);
#define CALLBACK_PROPERTY(T) extern T T##Callback
DEF_APP_CALLBACKS
#undef CALLBACK_PROPERTY

void HandleMessage(void *message);

} // namespace app
} // namespace core
} // namespace tension