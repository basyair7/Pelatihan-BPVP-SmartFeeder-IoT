#include "Arduino.h"

#define ON  0x1
#define OFF 0x0

class MyProgram {
public:
  static MyProgram& instance() {
    static MyProgram instance;
    return instance;
  }

  static void main() {
    instance()._setup();
    for(;;) {
      // instance().test1();
      instance().test2();
    }
  }

private:
  const int potensioPIN = A7;
  static const int LED_COUNT = 3;
  const int LED_PINS[LED_COUNT] = { 3, 4, 5 };
  int potensioValue;
  void _setup();
  void test1();
  void test2();

};