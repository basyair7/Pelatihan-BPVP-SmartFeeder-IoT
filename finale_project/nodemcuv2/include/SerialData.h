/*! @file SerialData.h
 *  @version 1.0.0
*/

#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>

class SerialData {
public:
    SerialData(uint8_t rx, uint8_t tx) : myserial(rx, tx) { /*TODO(Not yet implement)*/ }
    void sendDistance(float __distance__);

    void sendBlynkCmd(bool __auto__, bool __switch__);

    void runSendData(long __delay__);

private:
    SoftwareSerial myserial;

private:
    float __distance__;
    bool __auto__, __switch__;
    unsigned long LastSendData = 0;
};