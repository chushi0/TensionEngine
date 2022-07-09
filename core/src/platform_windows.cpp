#include "platform_windows.h"
#ifdef PLATFORM_WINDOWS

#include "app.h"
#include <Windows.h>
#include <string>
#include <thread>

#include <GL/glew.h>
#pragma comment(lib, "opengl32")

namespace tension {
namespace core {
namespace platform_windows {

static WindowsConfig config = {};

static HWND hwnd;
static HDC hDC;
static HGLRC hGLRC;

void SetWindowsConfig(WindowsConfig *config) {
  platform_windows::config = *config;
}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam,
                                LPARAM lParam) {
  switch (msg) {
  case WM_CLOSE:
    DestroyWindow(hwnd);
    break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  case WM_ERASEBKGND:
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
  // 取消应用程序缩放
  HINSTANCE hUser32 = LoadLibrary("User32.dll");
  if (hUser32) {
    typedef BOOL(WINAPI * LPSetProcessDPIAware)(void);
    LPSetProcessDPIAware pSetProcessDPIAware =
        (LPSetProcessDPIAware)GetProcAddress(hUser32, "SetProcessDPIAware");
    if (pSetProcessDPIAware) {
      pSetProcessDPIAware();
    }
    FreeLibrary(hUser32);
  }
  // 创建窗口
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
  hwnd = CreateWindow("TensionEngineWindowClass", config.title,
                      WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                      config.width, config.height, NULL, NULL, hInstance, NULL);
  // 创建 OpenGL 环境
  hDC = GetDC(hwnd);
  DWORD pixelFormatFlags =
      PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
  PIXELFORMATDESCRIPTOR pfd = {
      sizeof(PIXELFORMATDESCRIPTOR),
      1,
      pixelFormatFlags, // Flags
      PFD_TYPE_RGBA,    // The kind of framebuffer. RGBA or palette.
      32,               // Colordepth of the framebuffer.
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      config.glDepthBits,   // Number of bits for the depthbuffer
      config.glStencilBits, // Number of bits for the stencilbuffer
      0,                    // Number of Aux buffers in the framebuffer.
      PFD_MAIN_PLANE,
      0,
      0,
      0,
      0};
  int pixelFormat = ::ChoosePixelFormat(hDC, &pfd);
  SetPixelFormat(hDC, pixelFormat, &pfd);
  hGLRC = ::wglCreateContext(hDC);
  wglMakeCurrent(hDC, hGLRC);

  glewInit();

  // 显示窗口
  ShowWindow(hwnd, SW_SHOW);

  // 回调
  app::CallApplicationStart();
}

int WindowsLooperRun() {
  MSG msg;
  while (true) {
    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
      if (msg.message == WM_QUIT) {
        break;
      }
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    } else {
      // 回调
      if (app::CallFrameUpdate()) {
        // 交换缓冲区
        SwapBuffers(hDC);
      } else {
        Sleep(1);
      }
    }
  }
  return (int)msg.wParam;
}

uint64_t GetTimeElapsed() { return GetTickCount64(); }

void Sleep(uint64_t time) {
  constexpr uint64_t max = INT32_MAX;
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
