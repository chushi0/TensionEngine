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

void CallApplicationStart() {
  if (ApplicationStartCallback) {
    ApplicationStartCallback();
  }
}

void CallApplicationPause() {
  if (ApplicationPauseCallback) {
    ApplicationPauseCallback();
  }
}

void CallApplicationResume() {
  if (ApplicationResumeCallback) {
    ApplicationResumeCallback();
  }
}

void CallWindowResize(int w, int h) {
  static int oldWidth = w;
  static int oldHeight = h;
  if (WindowResizeCallback) {
    WindowResizeCallback(oldWidth, oldHeight, w, h);
  }
  oldWidth = w;
  oldHeight = h;
}

bool CallFrameUpdate() {
  static uint64_t lastUpdateTime = 0;
  uint64_t currentUpdateTime = GetTimeElapsed();
  if (currentUpdateTime - lastUpdateTime < 1000 / 60) {
    return false;
  }
  float delta = (currentUpdateTime - lastUpdateTime) / 1000.f;
  lastUpdateTime = currentUpdateTime;
  if (FrameUpdateCallback) {
    FrameUpdateCallback(delta);
    return true;
  }
  return false;
}

} // namespace app

int Exec(int argc, char **argv) {
  app::argc = argc;
  app::argv = argv;
  PlatformInit();
  return PlatformLooperRun();
}

#define CALLBACK_PROPERTY(T)                                                   \
  void Set##T##Callback(T func) { app::T##Callback = func; }
DEF_APP_CALLBACKS
#undef CALLBACK_PROPERTY

} // namespace core
} // namespace tension