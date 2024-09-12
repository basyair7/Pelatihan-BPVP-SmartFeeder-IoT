#include "Arduino.h"

#define public public:

class MyProgram {
  static const int LED_COUNT = 4;
  int potensioValue = 0;
  int LEDBrightness1, LEDBrightness2;
  const int LED_PINS[LED_COUNT] = { 2, 3, 4, 5 };
  void _setup();
  void test1();
  void test2();
  void test3();
  void test4();
  
  public static MyProgram& instance() {
    static MyProgram instance;
    return instance;
  }
  
  public static void main() {
    instance()._setup();
    
    while(1) {  
      // instance().test1();
      // instance().test2();
      // instance().test3();
      instance().test4();
    }
  }
};