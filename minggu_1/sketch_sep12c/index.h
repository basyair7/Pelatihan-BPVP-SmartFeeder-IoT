#include "Arduino.h"
#include "LCDdisplay.h"
#include "LiquidCrystal_animated.h"

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
  LCDdisplay* lcd = new LCDdisplay(20, 4);
  LiquidCrystal_animated ChrAnimated = LiquidCrystal_animated(20);

private:
  void _setup();
  void test1();
};