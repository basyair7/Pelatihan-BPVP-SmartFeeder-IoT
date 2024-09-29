/*! @file SerialData.h
 *  @version 1.0.0
*/

#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>

class SerialData {
public:
    SerialData(uint8_t rx, uint8_t tx) : myserial(rx, tx) { /*TODO(Not yet implemented)*/ }
    void setDistance(float distance);

    void setBlynkCmd(bool auto_state, bool switch_state);
	
	void setTimeAuto(const String Timer1, const String Timer2, const String Timer3);

    void runSendData(long __delay__);

private:
    SoftwareSerial myserial;

private:
    String __Timer1__ = "7:0:0", __Timer2__ = "12:0:0", __Timer3__ = "17:0:0";
    float __distance__;
    bool __auto_state__, __switch_state__;
	unsigned long LastSendData = 0;
};