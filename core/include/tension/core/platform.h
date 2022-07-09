#pragma once

#include "global.h"
#include <string>

namespace tension {
namespace core {

enum Platform {
  Windows,
  Android,
  HTML,
  Unknown,
};

// Windows 平台配置
struct WindowsConfig {
  const char *title = "Tension Game"; // 窗口标题
  int width = 640;                    // 窗口宽度
  int height = 480;                   // 窗口高度

  uint8_t glDepthBits = 24;  // 深度测试位数
  uint8_t glStencilBits = 8; // 蒙版测试位数
};

// 设置 Windows 平台的配置，如果当前没有在 Windows 平台上运行，则不执行任何操作
TENSION_CORE_FUNC void TENSION_CORE_CALL
SetWindowsConfig(WindowsConfig *config);

// 获取当前平台类型
TENSION_CORE_FUNC Platform TENSION_CORE_CALL GetCurrentPlatform();
// 获取当前操作系统信息（如版本号）
TENSION_CORE_FUNC std::string TENSION_CORE_CALL GetCurrentPlatformString();

// 获取时间（毫秒）
// 保证自增，但不保证与系统时间相同
TENSION_CORE_FUNC uint64_t TENSION_CORE_CALL GetTimeElapsed();

// 休眠指定时间
TENSION_CORE_FUNC void TENSION_CORE_CALL Sleep(uint64_t time);

} // namespace core
} // namespace tension