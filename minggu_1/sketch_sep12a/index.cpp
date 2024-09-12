#include "index.h"

void MyProgram::_setup() {
  Serial.begin(9600);
  pinMode(this->potensioPIN, INPUT);

  for (int i = 0; i < this->LED_COUNT; i++) {
    pinMode(this->LED_PINS[i], OUTPUT);
  }
}

void MyProgram::test1() {
  this->potensioValue = analogRead(this->potensioPIN);
  Serial.print(F("Potensio Value : "));
  Serial.println(this->potensioValue);

  // if (this->potensioValue > 600) {
  //   digitalWrite(this->LED_PINS[0], ON);
  //   digitalWrite(this->LED_PINS[1], OFF);
  // }
  
  // else if (this->potensioValue < 600) {
  //   digitalWrite(this->LED_PINS[0], OFF);
  //   digitalWrite(this->LED_PINS[1], ON);
  // }

  this->potensioValue > 600 ? digitalWrite(this->LED_PINS[0], ON) : digitalWrite(this->LED_PINS[0], OFF);
  this->potensioValue < 600 ? digitalWrite(this->LED_PINS[1], ON) : digitalWrite(this->LED_PINS[1], OFF);

  delay(50);
}

void MyProgram::test2() {
  this->potensioValue = analogRead(this->potensioPIN);
  Serial.print(F("Potensio Value : "));
  Serial.println(this->potensioValue);

  // if (this->potensioValue < 300) {
  //   digitalWrite(this->LED_PINS[0], ON);
  //   digitalWrite(this->LED_PINS[1], OFF);
  //   digitalWrite(this->LED_PINS[2], OFF);
  // }

  // else if (this->potensioValue > 300 && this->potensioValue < 600) {
  //   digitalWrite(this->LED_PINS[0], OFF);
  //   digitalWrite(this->LED_PINS[1], ON);
  //   digitalWrite(this->LED_PINS[2], OFF);
  // }

  // else if (this->potensioValue > 600) {
  //   digitalWrite(this->LED_PINS[0], OFF);
  //   digitalWrite(this->LED_PINS[1], OFF);
  //   digitalWrite(this->LED_PINS[2], ON);
  // }

  int ledIndex = (this->potensioValue < 300) ? 0 : (this->potensioValue > 300 && this->potensioValue < 600) ? 1 : 2;
  for (int i = 0; i < this->LED_PINS; i++) {
    digitalWrite(this->LED_PINS[i], i == ledIndex ? ON : OFF);
  }

  delay(50);
}