#include "app.h"
#include "platform.h"

namespace tension {
namespace core {

namespace app {

static int argc;
static char **argv;
#define CALLBACK_PROPERTY(T) T T##Callback = nullptr
DEF_APP_CALLBACKS
#undef CALLBACK_PROPERTY

static uint64_t lastFrameTime;

static void LoopHandler(void *) {
  uint64_t currentFrameTime = GetTimeElapsed();
  uint64_t delta = currentFrameTime - lastFrameTime;
  if (1000 / 60 > delta) {
    Sleep(1000 / 60 - delta);
  }
  currentFrameTime = GetTimeElapsed();
  if (FrameUpdateCallback) {
    FrameUpdateCallback((currentFrameTime - lastFrameTime) / 1000.f);
  }
  lastFrameTime = currentFrameTime;

  auto msg = new Message;
  msg->handler = app::LoopHandler;
  DispatchMessage(msg);
}

void HandleMessage(void *message) {
  auto msg = (Message *)message;
  msg->handler(msg->data);
  delete msg;
}

} // namespace app

int TENSION_CORE_CALL Exec(int argc, char **argv) {
  app::argc = argc;
  app::argv = argv;
  PlatformInit();
  if (app::ApplicationStartCallback) {
    app::ApplicationStartCallback();
  }
  auto msg = new Message;
  msg->handler = app::LoopHandler;
  DispatchMessage(msg);
  return PlatformLooperRun();
}

#define CALLBACK_PROPERTY(T)                                                   \
  void TENSION_CORE_CALL Set##T##Callback(T func) { app::T##Callback = func; }
DEF_APP_CALLBACKS
#undef CALLBACK_PROPERTY

void DispatchMessage(Message *message) { PlatformDispatchMessage(message); }

} // namespace core
} // namespace tension