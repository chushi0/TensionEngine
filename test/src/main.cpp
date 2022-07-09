#include <iostream>
#include <tension/core.h>

void ApplicationStart() {
  std::cout << "Hello, world!" << std::endl;
  std::cout << tension::core::GetCurrentPlatformString() << std::endl;
}

void FrameUpdate(float timeElapsed) {
  std::cout << "Update " << timeElapsed << std::endl;
}

int main(int argc, char **argv) {
  tension::core::SetApplicationStartCallback(ApplicationStart);
  tension::core::SetFrameUpdateCallback(FrameUpdate);
  return tension::core::Exec(argc, argv);
}