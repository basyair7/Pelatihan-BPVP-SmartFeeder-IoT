#include "index.h"

void MyProgram::_setup() {
  lcd->init();
  pinMode(this->TriggerPin, OUTPUT);
  pinMode(this->EchoPin, INPUT);
  delay(1000);
}

void MyProgram::test1() {
  float distance = this->getDistance(50);
  
  if ((unsigned long) (millis() - this->lastMillis1) >= 500) {
    this->lastMillis1 = millis();
    
    lcd->clear();
    lcd->printWithCursor(F("Jarak: "), 0, 0);
    lcd->printWithCursor(distance, 7, 0);
    lcd->printWithCursor(F("cm"), 12, 0);
  }
}

float MyProgram::getDistance(uint16_t _delay) {
  static bool isWaitingForEcho = false;
  float value, time;
  if ((unsigned long) (millis() - this->lastMillis2) >= (long unsigned int) _delay) {
    this->lastMillis2 = millis();
    // trigger sensor
    digitalWrite(this->TriggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(this->TriggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->TriggerPin, LOW);

    isWaitingForEcho = true;
  }

  if (isWaitingForEcho) {
    time = pulseIn(this->EchoPin, HIGH);
    value = time * 0.034 / 2;
    
    isWaitingForEcho = false;
  }

  return value;
}
