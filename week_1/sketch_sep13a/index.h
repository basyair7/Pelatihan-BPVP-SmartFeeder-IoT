#include "Arduino.h"
#include "LCDdisplay.h"
//#include "LiquidCrystal_animated.h"

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
  const uint8_t TriggerPin  = 9;
  const uint8_t EchoPin     = 10;

private:
  void _setup();
  void test1();
  float getDistance(uint16_t _delay);

private:
  LCDdisplay* lcd = new LCDdisplay(20, 4);
  unsigned long lastMillis1 = 0, lastMillis2 = 0;
//  LiquidCrystal_animated ChrAnimated = LiquidCrystal_animated(20);
};
