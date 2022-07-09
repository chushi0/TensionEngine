#pragma once
#include <string>

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#define PLATFORM_WINDOWS

namespace tension {
namespace core {
namespace platform_windows {

std::string GetWindowsPlatformString();
void WindowsInit();
int WindowsLooperRun();
void WindowsDispatchMessage(void *message);
uint64_t GetTimeElapsed();
void Sleep(uint64_t time);

} // namespace platform_windows
} // namespace core
} // namespace tension
#endif