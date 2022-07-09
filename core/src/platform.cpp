#include "platform.h"
#include "platform_windows.h"
#include <tension/core/platform.h>

namespace tension {
namespace core {

Platform GetCurrentPlatform() {
#if defined(PLATFORM_WINDOWS)
  return Platform::Windows;
#else
  return Platform::Unknown;
#endif
}

std::string GetCurrentPlatformString() {
#if defined(PLATFORM_WINDOWS)
  return platform_windows::GetWindowsPlatformString();
#else
  return std::string();
#endif
}

uint64_t GetTimeElapsed() {
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

void SetWindowsConfig(WindowsConfig *config) {
#if defined(PLATFORM_WINDOWS)
  platform_windows::SetWindowsConfig(config);
#endif
}

void Sleep(uint64_t time) {
#if defined(PLATFORM_WINDOWS)
  platform_windows::Sleep(time);
#endif
}

} // namespace core
} // namespace tension