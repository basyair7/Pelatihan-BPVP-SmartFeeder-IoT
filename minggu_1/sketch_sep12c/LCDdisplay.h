/*! @file LCDdisplay.h
 * @version 1.0.0
*/

#include "Arduino.h"
#include "Wire.h"
#include "LiquidCrystal_I2C.h"

class LCDdisplay {
public:
  // Constructor with default size
  LCDdisplay(int cols = 16, int rows = 2) : 
    cols(cols), rows(rows), lcd(0x27, cols, rows) {}

  // Initialize LCD function
  void init();
  // clear LCD function
  void clear();
  // backlight on/off
  void backlight(bool state);
  // display
  void print(const String& x, const uint8_t col, const uint8_t row);

private:
  int cols; int rows;

private:
  LiquidCrystal_I2C lcd;
};