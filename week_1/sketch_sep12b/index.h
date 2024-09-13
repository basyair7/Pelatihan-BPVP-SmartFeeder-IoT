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
    instance().test3();
  }

private:
  // for ultrasonic sensor
  float time, distance;
  const uint8_t TriggerPin = 9;
  const uint8_t EchoPin    = 10;
  unsigned long lastMillis = 0;

  // for led
  const int LED_PINS[3] = { 2, 3, 4 };

private:
  void _setup();
  float getDistance(uint32_t _delay);
  void test1();
  void test2();
  void test3();

};