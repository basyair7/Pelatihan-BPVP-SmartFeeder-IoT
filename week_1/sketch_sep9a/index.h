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
    // instance()._blink();
    // instance()._blink2();
    instance()._blink3();
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
        digitalWrite(LED_PINS[j], (i == j) ? HIGH : LOW);
      }

      delay(500);

      Serial.print(F("LED "));
      Serial.print(i + 1);
      Serial.println(F(" OFF"));
    }
  }

  void _blink2() {
    for (int i = 0; i < 2; i++) {
      digitalWrite(LED_PINS[i], HIGH);
      delay(1000);
    }

    for (int i = 0; i < 2; i++) {
      digitalWrite(LED_PINS[i], LOW);
      delay(1000);
    }

    for (int i = 0; i < 2; i++) {
      digitalWrite(LED_PINS[i], HIGH);
    }

    delay(1000);
    
    for (int i = 0; i < 2; i++) {
      digitalWrite(LED_PINS[i], LOW);
    }

    delay(1000);
  }

  void _blink3() {
    for (int i = 0; i < 3; i++) {
      this->_MessageLED(i + 1, 1);

      for (int j = 0; j < 3; j++) {
        digitalWrite(LED_PINS[j], (i == j) ? HIGH : LOW);
      }
      
      if (i == 2) {
        for (int k = 0; k < 3; k++) {
          this->_MessageDelay(ARR_DELAY[k]);
          delay(ARR_DELAY[k]);
          if (k == 2) {
            digitalWrite(LED_PINS[2], LOW);
            digitalWrite(LED_PINS[1], HIGH);
            delay(ARR_DELAY[k]);
            digitalWrite(LED_PINS[1], LOW);
          }
        }
      }
      else {
        this->_MessageDelay(ARR_DELAY[i]);
        delay(ARR_DELAY[i]);
      }

      this->_MessageLED(i + 1, 0);
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

  void _MessageLED(int pin, int value) {
    Serial.print(F("\nLED "));
    Serial.print(pin);
    Serial.println(value ? " ON" : " OFF");
  }

  void _MessageDelay(int _delay) {
    Serial.print(F("DELAY : "));
    Serial.print(_delay);
    Serial.println(F("ms"));
  }

  void _SerialMessage() {
    if (Serial.available() > 0) {
      String message = Serial.readString();
      Serial.println(message);
    }
  }

private:
  static const int LED_COUNT = 3;
  const int LED_PINS[LED_COUNT] = {2, 3, 4}; // PIN 2, 3, 4
  const int ARR_DELAY[3] = {6000, 1500, 700};
};

