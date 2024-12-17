#include <functional>
#include <iostream>
#include <stack>

class Deferrer {
public:
  Deferrer() {}
  ~Deferrer() { callAll(); }

  void addCall(std::function<void()> &&func) {
    _callStack.push(std::forward<decltype(func)>(func));
  }

private:
  std::stack<std::function<void()>> _callStack;

  void callAll() {
    while (!_callStack.empty()) {
      _callStack.top()();
      _callStack.pop();
    }
  }
};

// We might want perfect forwarding here, but that's in the TODO list for now
#define defer(...)                                                             \
  do {                                                                         \
    auto deferred = std::bind(__VA_ARGS__);                                    \
    __deferrer.addCall(deferred);                                              \
  } while (0);

#define allow_deferred() Deferrer __deferrer;

class A {
public:
  A() {}
  ~A() { std::cout << "Finishing A..." << std::endl; }
  void f() { std::cout << "Inside A::f" << std::endl; }
};

void func(int &val) {
  A a;
  // the allow_deferred call should be after all local variable declarations
  allow_deferred();

  defer(&A::f, &a);

  val = 1;

  for (int i = 0; i < 4; i++) {
    defer([=]() { std::cout << i << std::endl; });
  }

  defer([&val]() { val = 42; });
}
