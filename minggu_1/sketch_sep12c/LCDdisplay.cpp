/*! @file LCDdisplay.cpp
 * @version 1.0.0
*/

#include "LCDdisplay.h"

// initialize LCD Program
void LCDdisplay::init() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

// Clear LCD program
void LCDdisplay::clear() {
  lcd.clear();
}

// Backlight LCD program
void LCDdisplay::backlight(bool state) {
  if (state) lcd.backlight();
  else lcd.noBacklight();
}

// display program
void LCDdisplay::print(const String& x, const uint8_t col, const uint8_t row) {
  lcd.setCursor(col, row);
  lcd.print(x);
}