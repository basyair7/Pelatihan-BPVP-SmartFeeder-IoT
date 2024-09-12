#include "index.h"

void MyProgram::_setup() {
  lcd->init();
  lcd->backlight();
  lcd->clear();
}

void MyProgram::test1() {
  lcd->setCursor(0, 0);
  lcd->print(F("Hello, World"));
}