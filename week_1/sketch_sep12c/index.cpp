#include "index.h"

void MyProgram::_setup() {
  lcd->init();
  ChrAnimated.Clear_Scroll_LCD_Left();
  lcd->setCursor(2, 0);
  lcd->print(F("SELAMAT DATANG"));
  lcd->setCursor(8, 1);
  lcd->print(F("DI"));
  lcd->setCursor(2, 2);
  lcd->print(F("BPVP BANDA ACEH"));
  delay(5000);
  lcd->clear();
}

void MyProgram::test1() {
  // String text = "Program Smart Feeder Elektronika";
  // for (int i = 0; i <= (int)(text.length() + 16); i++) {
  //   lcd->printWithCursor(this->ChrAnimated.Scroll_LCD_Left(text), 0, 0);
  //   delay(200);
  // }

  lcd->printWithCursor(F("PROGRAM"), 6, 0);
  lcd->printWithCursor(F("SMART FEEDER"), 4, 1);
  lcd->printWithCursor(F("ELEKTRONIKA"), 4, 2);
  // lcd->printWithCursor<uint32_t>(2023, 4, 3);

  String text = "BY Basyair7";
  for (int i = 0; i <= (int)(text.length() + 5); i++) {
    lcd->printWithCursor<String>(this->ChrAnimated.Scroll_LCD_Left(text), 0, 3);
    delay(200);
  }
  ChrAnimated.Clear_Scroll_LCD_Left();
}