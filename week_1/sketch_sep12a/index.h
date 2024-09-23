#include "Arduino.h"

#define ON  0x1
#define OFF 0x0

class MyProgram {
public:
  static MyProgram& instance() {
    static MyProgram instance;
    return instance;
  }
  
  static void setup() {
    instance()._setup();
  }

  static void main() {
    for(;;) {
      // instance().test1();
      instance().test2();
    }
  }

private:
  const int potensioPIN = A7;
  const int LED_PINS[3] = { 3, 4, 5 };
  unsigned int potensioValue;
  void _setup();
  void test1();
  void test2();

};