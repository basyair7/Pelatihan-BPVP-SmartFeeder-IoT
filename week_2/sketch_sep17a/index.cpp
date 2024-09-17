#include "index.h"

void MyProgram::_setup(void) {
  Serial.begin(9600);
  for (const auto i : this->LED_PINS) {
    pinMode(i, OUTPUT);
  }
}

void MyProgram::test1(void) {
  if ((unsigned long) (millis() - this->LastMillis1) >= 2000) {
    this->LastMillis1 = millis();
    this->LEDState1 = !this->LEDState1;
    Serial.print(F("LED 1: "));
    Serial.println(this->LEDState1 ? "ON" : "OFF");
  }

  if ((unsigned long) (millis() - this->LastMillis2) >= 4000) {
    this->LastMillis2 = millis();
    this->LEDState2 = !this->LEDState2;
    Serial.print(F("LED 2: "));
    Serial.println(this->LEDState2 ? "ON" : "OFF");
  }

  digitalWrite(this->LED_PINS[0], this->LEDState1);
  digitalWrite(this->LED_PINS[1], this->LEDState2);
}

void MyProgram::test2(void) {
  unsigned long currentTime = millis();

  for (int i = 0; i < (int)(sizeof(this->LED_PINS)/sizeof(this->LED_PINS[0])); i++) {
    if ((unsigned long) (currentTime - *lastMillis[i]) >= intervals[i]) {
      *lastMillis[i] = currentTime;
      *LEDStates[i] = !(*LEDStates[i]);

      Serial.println("LED " + String(i+1) + ": " + String(*LEDStates[i] ? "ON" : "OFF"));
    }

    digitalWrite(this->LED_PINS[i], *LEDStates[i] ? HIGH : LOW);
  }
}