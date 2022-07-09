#pragma once
#include <string>
#include <tension/core/platform.h>

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#define PLATFORM_WINDOWS

namespace tension {
namespace core {
namespace platform_windows {

// 获取当前操作系统版本信息
std::string GetWindowsPlatformString();
// 初始化
void WindowsInit();
// 主循环
int WindowsLooperRun();
// 获取当前时间
uint64_t GetTimeElapsed();
// 休眠指定时间
void Sleep(uint64_t time);

// 设置启动配置
void SetWindowsConfig(WindowsConfig *config);

} // namespace platform_windows
} // namespace core
} // namespace tension
#endif