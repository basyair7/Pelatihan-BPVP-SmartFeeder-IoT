#include "index.h"

void MyProgram::_setup() {
  Serial.begin(9600);
  pinMode(this->TriggerPin, OUTPUT);
  pinMode(this->EchoPin, INPUT);

  for (int i = 0; i < this->LED_COUNT; i++) {
    pinMode(this->LED_PINS[i], OUTPUT);
  }
}

// program membaca jarak
void MyProgram::test1() {
  digitalWrite(this->TriggerPin, LOW);
  delayMicroseconds(50);
  digitalWrite(this->TriggerPin, HIGH);
  delayMicroseconds(50);
  digitalWrite(this->TriggerPin, LOW);
  delayMicroseconds(50);

  this->time = pulseIn(this->EchoPin, HIGH);
  this->distance = this->time * 0.034 / 2;

  Serial.print(F("Jarak : "));
  Serial.print(this->distance);
  Serial.println(F("cm"));
  delay(50);
}

// program dengan menggunakan millis
void MyProgram::test2() {
  unsigned long currentMillis = millis();
  static bool isWaitingForEcho = false;

  if ((unsigned long) (currentMillis - this->lastMillis) >= (long unsigned int) 50) {
    // Trigger sensor
    digitalWrite(this->TriggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(this->TriggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->TriggerPin, LOW);

    this->lastMillis = currentMillis;
    isWaitingForEcho = true;
  }

  if (isWaitingForEcho) {
    // baca sinyal dari Echo sensor
    this->time = pulseIn(this->EchoPin, HIGH);
    this->distance = this->time * 0.034 / 2;

    // Tampilkan jarak
    Serial.print(F("Jarak : "));
    Serial.print(this->distance);
    Serial.println(F("cm"));

    // Reset untuk mengaktifkan trigger kembali
    isWaitingForEcho = false;
  }
}

void MyProgram::test3() {
  this->distance = getDistance(50);

  int indexPins = (this->distance < 10) ? 0 : (this->distance > 10 && this->distance < 20) ? 1 : 2;
  for (int i = 0; i < this->LED_COUNT; i++) {
    digitalWrite(this->LED_PINS[i], (i == indexPins) ? HIGH : LOW);
  }

  delay(50);
}

float MyProgram::getDistance(uint32_t _delay) {
  static bool isWaitingForEcho = false;
  float value, time;
  if ((unsigned long) (millis() - this->lastMillis) >= (long unsigned int) _delay) {
    // Trigger sensor
    digitalWrite(this->TriggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(this->TriggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->TriggerPin, LOW);

    this->lastMillis = millis();
    isWaitingForEcho = true;
  }

  if (isWaitingForEcho) {
    time = pulseIn(this->EchoPin, HIGH);
    value = time * 0.034 / 2;

    isWaitingForEcho = false;
  }

  return value;
}