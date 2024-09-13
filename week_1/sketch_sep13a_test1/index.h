#include "Arduino.h"
#include "LCDdisplay.h"

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
    instance().test1();
  }

private:
  // define LED pins
  static const int LED_COUNT = 3;
  const int LED_PINS[LED_COUNT] = { 3, 4, 5 };
  // define Ultrasonic Pins
  const byte TriggerPin = 9;
  const byte EchoPin    = 10;
  LCDdisplay* lcd = new LCDdisplay(20, 4);

private:
  void _setup();
  void test1();

private:
  unsigned long LastMillis1 = 0, LastMillis2 = 0;
  float getDistance(uint16_t _delay);
  
};
