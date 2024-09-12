#include "Arduino.h"
#include "Wire.h"
#include "LiquidCrystal_I2C.h"

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
  LiquidCrystal_I2C* lcd = new LiquidCrystal_I2C(0x27, 20, 4);

private:
  void _setup();
  void test1();
};