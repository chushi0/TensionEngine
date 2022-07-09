#pragma once

#include <tension/core/platform.h>
namespace tension {
namespace core {

void PlatformInit();
int PlatformLooperRun();
void PlatformDispatchMessage(void *message);

} // namespace core
} // namespace tension