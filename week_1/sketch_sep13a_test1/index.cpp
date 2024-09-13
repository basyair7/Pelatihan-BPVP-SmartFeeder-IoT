#include "index.h"

void MyProgram::_setup() {
  Serial.begin(9600);
  lcd->init();
  pinMode(this->TriggerPin, OUTPUT);
  pinMode(this->EchoPin, INPUT);
  for (const auto i : this->LED_PINS) {
    pinMode(i, OUTPUT);
  }
}

void MyProgram::test1() {
  float distance = this->getDistance(50);
  if ((unsigned long) (millis() - this->LastMillis1) >= 1000) {
    lcd->clear();
    lcd->printWithCursor<String>(F("PERSEDIAAN ADA"), 0, 0);
  
    int indexLED = (distance < 20) ? 0 : (distance > 20 && distance < 100) ? 1 : 2;
    for (int i = 0; i < this->LED_COUNT; i++) {
      digitalWrite(this->LED_PINS[i], i == indexLED ? HIGH : LOW);
    }
  
    if (indexLED == 2) {
      lcd->printWithCursor(F("PERSEDIAAN HABIS"), 0, 0);
    }

    this->LastMillis1 = millis();
  }  

  delay(50);
}

float MyProgram::getDistance(uint16_t _delay) {
  static bool isWaitingForEcho = false;
  float value, _time;
  
  if ((unsigned long) (millis() - this->LastMillis2) >= (long unsigned int) _delay) {
    this->LastMillis2 = millis();
    // Trigger Program
    digitalWrite(this->TriggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(this->TriggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->TriggerPin, LOW);

    isWaitingForEcho = true;
  }

  if (isWaitingForEcho) {
    _time = pulseIn(this->EchoPin, HIGH);
    value = _time * 0.034 / 2;
    isWaitingForEcho = false;
  }

  return value;
}
