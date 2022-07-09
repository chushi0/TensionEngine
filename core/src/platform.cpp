#include "platform.h"
#include "platform_windows.h"
#include <tension/core/platform.h>

namespace tension {
namespace core {

Platform TENSION_CORE_CALL GetCurrentPlatform() {
#if defined(PLATFORM_WINDOWS)
  return Platform::Windows;
#else
  return Platform::Unknown;
#endif
}

std::string TENSION_CORE_CALL GetCurrentPlatformString() {
#if defined(PLATFORM_WINDOWS)
  return platform_windows::GetWindowsPlatformString();
#else
  return std::string();
#endif
}

uint64_t TENSION_CORE_CALL GetTimeElapsed() {
#if defined(PLATFORM_WINDOWS)
  return platform_windows::GetTimeElapsed();
#else
  return -1;
#endif
}

void PlatformInit() {
#if defined(PLATFORM_WINDOWS)
  platform_windows::WindowsInit();
#endif
}

int PlatformLooperRun() {
#if defined(PLATFORM_WINDOWS)
  return platform_windows::WindowsLooperRun();
#else
  return -1;
#endif
}

void PlatformDispatchMessage(void *message) {
#if defined(PLATFORM_WINDOWS)
  platform_windows::WindowsDispatchMessage(message);
#endif
}

void TENSION_CORE_CALL Sleep(uint64_t time) {
#if defined(PLATFORM_WINDOWS)
  platform_windows::Sleep(time);
#endif
}

} // namespace core
} // namespace tension