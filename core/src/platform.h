#pragma once

#include <tension/core/platform.h>
namespace tension {
namespace core {

// 初始化（窗口、OpenGL环境等）
void PlatformInit();
// 主循环（不一定是渲染线程）
int PlatformLooperRun();

} // namespace core
} // namespace tension