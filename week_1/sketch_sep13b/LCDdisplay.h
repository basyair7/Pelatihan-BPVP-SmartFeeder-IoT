/*! @file LCDdisplay.h
 * @version 1.0.0
*/

#include "Arduino.h"
#include "Wire.h"
#include "LiquidCrystal_I2C.h"

#pragma once

class LCDdisplay {
public:
  // Constructor with default size
  LCDdisplay(int cols = 16, int rows = 2) : 
    cols(cols), rows(rows), lcd(0x27, cols, rows) {}

  // Initialize LCD function
  void init() {
    lcd.init();
    lcd.backlight();
    lcd.clear();
  }

  // clear LCD function
  void clear() {
    lcd.clear();
  }

  // backlight on/off
  void backlight(bool state) {
    if (state) lcd.backlight();
    else lcd.noBacklight();
  }

  // setcursor
  void setCursor(uint8_t row, uint8_t col) {
    lcd.setCursor(row, col);
  }

  // printout LCD
  template <typename T> void print(const T& x) {
    lcd.print(x);
  }
  
  template <typename T> void printWithCursor(const T& x, const uint8_t row, const uint8_t col) 
  {
    lcd.setCursor(row, col);
    lcd.print(x);
  }

private:
  int cols; int rows;

private:
  LiquidCrystal_I2C lcd;
};
