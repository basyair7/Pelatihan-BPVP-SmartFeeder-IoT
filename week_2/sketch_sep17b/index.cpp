#include "index.h"

void MyProgram::_setup(void) {
  Serial.begin(9600); // inisialisasikan serial baudrate
  
  // inisialisasikan pin sensor Trigger
  for (const auto i : this->TRIGGER_PINS) {
    pinMode(i, OUTPUT);
  }
  // inisialisasikan pin sensor Echo
  for (const auto i : this->ECHO_PINS) {
    pinMode(i, INPUT);
  }
  // inisialisasikan pin LED
  for (const auto i : this->LED_PINS) {
    pinMode(i, OUTPUT);
  }
}

void MyProgram::test1(void) {
  // ambil data sensor ultrasonic
  float getDistance1 = this->getDistance(this->TRIGGER_PINS[0], this->ECHO_PINS[0]);
  float getDistance2 = this->getDistance(this->TRIGGER_PINS[1], this->ECHO_PINS[1]);

  const float LimitDistance = 5.0; // 5cm

  if (getDistance1 < LimitDistance || getDistance2 < LimitDistance) {
    // sensor 1 terpicu, menunggu sensor 2 untuk incoming
    if (getDistance1 < LimitDistance && !this->sensorDetected1) {
      this->sensorDetected1 = true;
    }

    if (getDistance2 < LimitDistance && this->sensorDetected1) {
      this->incoming = true;
    }

    // sensor 2 terpicu, menunggu sensor 1 untuk outcoming
    if (getDistance2 < LimitDistance && !this->sensorDetected2) {
      this->sensorDetected2 = true;
    }

    if (getDistance1 < LimitDistance && this->sensorDetected2) {
      this->outcoming = true;
    }
  }

  // jalankan program led / pesan "selamat datang"
  if (this->incoming) {
    Serial.println(F("Selamat Datang"));
    digitalWrite(this->LED_PINS[0], HIGH);
    delay(2000);
    digitalWrite(this->LED_PINS[0], LOW);

    // reset flag incoming beserta sensorDetected
    this->incoming = this->sensorDetected1 = this->sensorDetected2 = false;
  }

  // jalankan program led / pesan "selamat jalan"
  if (this->outcoming) {
    Serial.println(F("Selamat Jalan"));
    digitalWrite(this->LED_PINS[1], HIGH);
    delay(2000);
    digitalWrite(this->LED_PINS[1], LOW);

    // reset flag outcoming beserta sensorDetected
    this->outcoming = this->sensorDetected1 = this->sensorDetected2 = false;
  }

  delay(50);
}

float MyProgram::getDistance(uint8_t triggerPin, uint8_t echoPin) {
  float _time, value;

  // Trigger Program
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Echo program
  _time = pulseIn(echoPin, HIGH);
  value = _time * 0.034 / 2;

  return value;
}