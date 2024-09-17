#include "Arduino.h"

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
    // instance().test1();
    instance().test2();
  }

private:
  const int LED_PINS[2] = { 7, 8 };

private:
  void _setup(void);
  void test1(void);
  void test2();

private:
  bool LEDState1 = false;
  bool LEDState2 = false;
  unsigned long LastMillis1 = 0;
  unsigned long LastMillis2 = 0;

private:
  const unsigned long intervals[2] = { 2000, 4000 };
  bool* LEDStates[2] = { &this->LEDState1, &this->LEDState2 };
  unsigned long* lastMillis[2] = { &this->LastMillis1, &this->LastMillis2 };
};