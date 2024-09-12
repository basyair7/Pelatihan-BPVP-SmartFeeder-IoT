#include "index.h"
#include "Arduino.h"

void MyProgram::_setup() {
  Serial.begin(9600);
  for (int i = 0; i < LED_COUNT; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }
}

void MyProgram::test1() {
  potensioValue   = analogRead(A0);
  LEDBrightness1  = potensioValue / 4;
  LEDBrightness2  = 255 - LEDBrightness1;
  analogWrite(3, LEDBrightness1);
  analogWrite(4, LEDBrightness2);

  Serial.print(F("LEDBrightness1 : "));
  Serial.println(LEDBrightness1);
  Serial.print(F("LEDBrightness2 : "));
  Serial.println(LEDBrightness2);

  delay(10);
}

void MyProgram::test2() {
  potensioValue   = analogRead(A0);
  LEDBrightness1  = map(potensioValue, 0, 1023, 0, 255);
  LEDBrightness2  = map(potensioValue, 0, 1023, 255, 0);
  analogWrite(4, LEDBrightness1);
  analogWrite(5, LEDBrightness2);
  delay(10);
}

void MyProgram::test3() {
  potensioValue = analogRead(A0);
  int delayTime = map(potensioValue, 0, 1023, 100, 1000);

  for (int i = 0; i < LED_COUNT; i++) {
    for (int j = 0; j < LED_COUNT; j++) {
      analogWrite(LED_PINS[j], (i == j) ? 255 : 0);
    }

    delay(delayTime);
  }
}

void MyProgram::test4() {
  potensioValue = analogRead(A0);
  int state = map(potensioValue, 0, 1023, 0, 100);
}
