#pragma once

#include "global.h"

namespace tension {
namespace core {

// 程序启动
typedef void (*ApplicationStart)();
// 程序暂停（失去焦点）
typedef void (*ApplicationPause)();
// 程序恢复（获得焦点）
typedef void (*ApplicationResume)();
// 窗口大小改变
typedef void (*WindowResize)(int oldWidth, int oldHeight, int newWidth,
                             int newHeight);
// 每帧刷新
typedef void (*FrameUpdate)(float timeElapsed);

// 程序入口（启动消息循环）
TENSION_CORE_FUNC int TENSION_CORE_CALL Exec(int argc, char **argv);

TENSION_CORE_FUNC void TENSION_CORE_CALL
SetApplicationStartCallback(ApplicationStart func);
TENSION_CORE_FUNC void TENSION_CORE_CALL
SetApplicationPauseCallback(ApplicationPause func);
TENSION_CORE_FUNC void TENSION_CORE_CALL
SetApplicationResumeCallback(ApplicationResume func);
TENSION_CORE_FUNC void TENSION_CORE_CALL
SetWindowResizeCallback(WindowResize func);
TENSION_CORE_FUNC void TENSION_CORE_CALL
SetFrameUpdateCallback(FrameUpdate func);

} // namespace core
} // namespace tension