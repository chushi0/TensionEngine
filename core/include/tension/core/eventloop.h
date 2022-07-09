#pragma once

namespace tension {
namespace core {

struct Message {
  int what;
  int arg1;
  int arg2;
  void *obj;
  void (*handler)(Message *message);

  // internal use
  Message *next;
};

// 获取一个空消息
Message *obtainMessage();

} // namespace core
} // namespace tension