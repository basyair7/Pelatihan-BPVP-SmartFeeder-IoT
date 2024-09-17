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
  float getDistance1 = this->getDistance(this->TRIGGER_PINS[0], this->ECHO_PINS[0]);
  float getDistance2 = this->getDistance(this->TRIGGER_PINS[1], this->ECHO_PINS[1]);

  // cek setiap 500ms untuk kedua sensor
  if ((unsigned long)(millis() - this->LastTime_GetDistance) > 500) {
    this->LastTime_GetDistance = millis();

    if (getDistance1 < 20 || getDistance2 < 20) {
      // sensor 2 terpicu, menunggu sensor 1 untuk outcoming
      if (getDistance2 < 20 && !this->sensorDetected1 && !this->sensorDetected2) {
        this->sensorDetected1 = true;
      }
      else if (getDistance1 < 20 && this->sensorDetected1) {
        this->outcoming = true;
      }

      // sensor 1 terpicu, menunggu sensor 2 untuk incoming
      if (getDistance1 < 20 && !this->sensorDetected1 && !this->sensorDetected2) {
        this->sensorDetected2 = true;
      }
      else if (getDistance2 < 20 && this->sensorDetected2) {
        this->incoming = true;
      }
    }
  }

  // tampilkan hasil deteksi
  if (this->incoming || this->outcoming) {
    Serial.println(incoming ? "Selamat Datang" : "Terima Kasih");
    digitalWrite(this->LED_PINS[0], incoming ? HIGH : LOW);
    digitalWrite(this->LED_PINS[1], outcoming ? HIGH : LOW);

    // reset flag setelah mencetak pesan
    this->sensorDetected1 = this->sensorDetected2 = this->incoming = this->outcoming = false;
  }
}

float MyProgram::getDistance(uint8_t triggerPin, uint8_t echoPin) {
  float _time, value;

  // Trigger Program
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(10);

  // Echo program
  _time = pulseIn(echoPin, HIGH);
  value = _time * 0.034 / 2;

  return value;
}