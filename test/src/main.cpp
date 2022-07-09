#include <GL/glew.h>
#include <iostream>
#include <tension/core.h>

void ApplicationStart() {
  std::cout << "Hello, world!" << std::endl;
  std::cout << tension::core::GetCurrentPlatformString() << std::endl;
  glClearColor(1, 0, 0, 0);
}

void FrameUpdate(float timeElapsed) {
  glClear(GL_COLOR_BUFFER_BIT);
  std::cout << "Update " << timeElapsed << std::endl;
}

int main(int argc, char **argv) {
  tension::core::WindowsConfig config = {};
  config.title = "Tension Engine Test";
  config.width = 1280;
  config.height = 720;
  tension::core::SetWindowsConfig(&config);
  tension::core::SetApplicationStartCallback(ApplicationStart);
  tension::core::SetFrameUpdateCallback(FrameUpdate);
  return tension::core::Exec(argc, argv);
}