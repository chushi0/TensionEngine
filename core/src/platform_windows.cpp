#include "platform_windows.h"
#ifdef PLATFORM_WINDOWS

#include "app.h"
#include <Windows.h>
#include <string>

namespace tension {
namespace core {
namespace platform_windows {

static HWND hwnd;
static constexpr int WM_USER_MESSAGE = WM_USER;

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam,
                                LPARAM lParam) {
  switch (msg) {
  case WM_CLOSE:
    DestroyWindow(hwnd);
    break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  case WM_USER_MESSAGE:
    app::HandleMessage((void *)lParam);
    break;
  default:
    return DefWindowProc(hwnd, msg, wParam, lParam);
  }
  return NULL;
}

std::string GetWindowsPlatformString() {
  HMODULE hNtDll = LoadLibraryA("ntdll.dll");
  if (hNtDll) {
    typedef void(WINAPI * pfRTLGETNTVERSIONNUMBERS)(DWORD *, DWORD *, DWORD *);
    pfRTLGETNTVERSIONNUMBERS pfRtlGetNtVersionNumbers =
        (pfRTLGETNTVERSIONNUMBERS)::GetProcAddress(hNtDll,
                                                   "RtlGetNtVersionNumbers");
    if (pfRtlGetNtVersionNumbers) {
      DWORD dwMajorVersion, dwMinorVerion, dwBuildNumber;
      pfRtlGetNtVersionNumbers(&dwMajorVersion, &dwMinorVerion, &dwBuildNumber);
      dwBuildNumber &= 0xffff;
      FreeLibrary(hNtDll);
      return std::string("Windows ") + std::to_string(dwMajorVersion) +
             std::string(".") + std::to_string(dwMinorVerion) +
             std::string(".") + std::to_string(dwBuildNumber);
    }
    FreeLibrary(hNtDll);
  }
  return std::string();
}

void WindowsInit() {
  HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);
  WNDCLASS wndClass = {};
  wndClass.style = CS_HREDRAW | CS_VREDRAW;
  wndClass.lpfnWndProc = WndProc;
  wndClass.cbClsExtra = 0;
  wndClass.cbWndExtra = 0;
  wndClass.hInstance = hInstance;
  wndClass.hIcon = NULL;
  wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wndClass.lpszMenuName = NULL;
  wndClass.lpszClassName = "TensionEngineWindowClass";
  RegisterClass(&wndClass);
  hwnd = CreateWindow("TensionEngineWindowClass", "OpenGL",
                      WS_EX_LAYERED | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU |
                          WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
                      CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL,
                      hInstance, NULL);
  ShowWindow(hwnd, SW_SHOW);
}

int WindowsLooperRun() {
  MSG msg;
  while (GetMessage(&msg, nullptr, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return (int)msg.wParam;
}

void WindowsDispatchMessage(void *message) {
  PostMessage(hwnd, WM_USER_MESSAGE, 0, (LONG_PTR)message);
}

uint64_t GetTimeElapsed() { return GetTickCount64(); }

void Sleep(uint64_t time) {
  constexpr uint64_t max = (~0) >> 1;
  while (time > max) {
    ::Sleep(max);
    time -= max;
  }
  if (time > 0) {
    ::Sleep(time);
  }
}

} // namespace platform_windows
} // namespace core
} // namespace tension
#endif
