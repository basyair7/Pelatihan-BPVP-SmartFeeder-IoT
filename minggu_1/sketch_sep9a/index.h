#include "Arduino.h"

class HelloWorld {
public:
  static HelloWorld& instance() {
    static HelloWorld instance;
    return instance;
  }

  static void begin(void) {
    instance()._begin();
  }

  static void serialHelloWorld(void) {
    instance()._serialHelloWorld();
  }

  static void blink(void) {
    instance()._blink();
  }

  static void pwm(void) {
    instance()._pwm();
  }

  static void SerialMessage(void) {
    instance()._SerialMessage();
  }

private:
  void _begin() {
    Serial.begin(9600);
    for (int i = 0; i < LED_COUNT; i++) {
      pinMode(LED_PINS[i], OUTPUT);
    }
  }

  void _serialHelloWorld() {
    Serial.println("\nHello, World!\n");
  }

  void _blink() {
    for (int i = 0; i < LED_COUNT; i++) {
      Serial.print(F("LED "));
      Serial.print(i + 1);
      Serial.println(F(" ON"));

      for (int j = 0; j < LED_COUNT; j++) {
        if (i == j) {
          digitalWrite(LED_PINS[j], HIGH);
        }
        else {
          digitalWrite(LED_PINS[j], LOW);
        }
      }

      delay(500);

      Serial.print(F("LED "));
      Serial.print(i + 1);
      Serial.println(F(" OFF"));
    }
  }

  void _pwm() {
    for (int i = 0; i <= 255; i++) {
      analogWrite(LED_BUILTIN, i);
      Serial.print("LED PWM : ");
      Serial.println(i);
      delay(100);
    }

    for (int j = 255; j >= 0; j--) {
      analogWrite(LED_BUILTIN, j);
      Serial.print("LED PWM : ");
      Serial.println(j);
      delay(100);
    }
  }

  void _SerialMessage() {
    if (Serial.available() > 0) {
      String message = Serial.readString();
      Serial.println(message);
    }
  }

private:
  const int LED_PINS[3] = {2, 3, 13};
  const int LED_COUNT = 3;
};

