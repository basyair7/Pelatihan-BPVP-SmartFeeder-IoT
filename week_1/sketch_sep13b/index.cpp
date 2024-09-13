#include "index.h"

void MyProgram::_setup() {
  Serial.begin(9600);
  rtc->begin();
  // rtc->autoAdjust();
  lcd->init();
}

void MyProgram::test1() {
  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print(F("Day : "));
  lcd->print(rtc->getDayOfWeek());
  lcd->setCursor(0, 1);
  lcd->print(F("Date: "));
  lcd->print(rtc->datestr());
  lcd->setCursor(0, 2);
  lcd->print(F("Time: "));
  lcd->print(rtc->timestr());

  lcd->printWithCursor(F("Basyair7"), 4, 3);
  delay(1000);
}