#pragma once

#include <stdint.h>

#if defined(TENSION_CORE_EXPORT)
#define TENSION_CORE_FUNC extern __declspec(dllexport)
#define GLEW_STATIC
#elif defined(TENSION_CORE_STATIC)
#define TENSION_CORE_FUNC extern
#else
#define TENSION_CORE_FUNC extern __declspec(dllimport)
#endif

#define TENSION_CORE_CALL __stdcall