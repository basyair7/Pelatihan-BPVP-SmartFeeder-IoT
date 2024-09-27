/*! @file ultrasonic.h
 *  @version 1.0.0
*/

#pragma once

#include "Arduino.h"

class Ultrasonic {
public:
    Ultrasonic(uint8_t TriggerPin, uint8_t EchoPin) {
        this->_TriggerPin = TriggerPin;
        this->_EchoPin    = EchoPin;
    }

    void begin() {
        pinMode(this->_TriggerPin, OUTPUT);
        pinMode(this->_EchoPin, INPUT);
    }

    float getDistance() {
        digitalWrite(this->_TriggerPin, LOW);
        delayMicroseconds(2);
        digitalWrite(this->_TriggerPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(this->_TriggerPin, LOW);

        return pulseIn(this->_EchoPin, HIGH) * 0.034 / 2;
    }

private:
    uint8_t _TriggerPin, _EchoPin;
};