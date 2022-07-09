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