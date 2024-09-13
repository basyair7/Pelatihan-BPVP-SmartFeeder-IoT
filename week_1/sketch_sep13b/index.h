#include "Arduino.h"
#include "LCDdisplay.h"
#include "DS3231rtc.h"

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
  void _setup();
  void test1();

private:
  LCDdisplay* lcd = new LCDdisplay(20, 4);
  DS3231rtc* rtc = new DS3231rtc();
};