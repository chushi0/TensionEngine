#pragma once

#if defined(TENSION_CORE_EXPORT)
#define TENSION_CORE_FUNC __declspec(dllexport)
#elif defined(TENSION_CORE_STATIC)
#define TENSION_CORE_FUNC extern
#else
#define TENSION_CORE_FUNC __declspec(dllimport)
#endif

#define TENSION_CORE_CALL __stdcall