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
  float getDistance1 = getDistance(TRIGGER_PINS[0], ECHO_PINS[0]);
	float getDistance2 = getDistance(TRIGGER_PINS[1], ECHO_PINS[1]);
	const float LimitDistance = 5.0;
	if (getDistance1 < LimitDistance || getDistance2 < LimitDistance) {
		// sensor 2 terpicu, menunggu sensor 1 untuk outcoming
		if (getDistance1 < LimitDistance) {
			sensorDetected1 = true;
		}

		if (getDistance2 < LimitDistance && sensorDetected1) {
			Serial.println(F("Selamat Jalan"));
			digitalWrite(LED_PINS[1], HIGH);
			delay(2000);
			digitalWrite(LED_PINS[1], LOW);
		}

		if (getDistance2 < LimitDistance) {
			sensorDetected2 = true;
		}

		if (getDistance1 < LimitDistance && sensorDetected2) {	
			Serial.println(F("Selamat Datang"));
			digitalWrite(LED_PINS[0], HIGH);
			delay(2000);
			digitalWrite(LED_PINS[0], LOW);
		}
	}

	if (sensorDetected1 && sensorDetected2 && getDistance1 > LimitDistance && getDistance2 > LimitDistance) {
		sensorDetected1 = sensorDetected2 = false;
	}

	delay(50);
}

float MyProgram::getDistance(uint8_t triggerPin, uint8_t echoPin) {
  // Trigger Program
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Echo program
  return pulseIn(echoPin, HIGH) * 0.034 / 2;
}