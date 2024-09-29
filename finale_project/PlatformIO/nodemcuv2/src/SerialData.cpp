/*! @file SerialData.cpp
 *  @version 1.0.0
*/

#include "SerialData.h"
#include <ArduinoJson.h>

void SerialData::setDistance(float distance) {
    this->__distance__ = distance;
}

void SerialData::setBlynkCmd(bool auto_state, bool switch_state)
{
    this->__auto_state__   = auto_state;
    this->__switch_state__ = switch_state;
}

void SerialData::setTimeAuto(const String Timer1, const String Timer2, const String Timer3)
{
	this->__Timer1__ = Timer1;
	this->__Timer2__ = Timer2;
	this->__Timer3__ = Timer3;
}

void SerialData::runSendData(long __delay__) {
    if ((unsigned long) (millis() - this->LastSendData) >= (unsigned long)__delay__) {
        this->LastSendData = millis();
        StaticJsonDocument<500> data;

        data["distance"]         = this->__distance__;
        data["blynk"]["auto"]    = this->__auto_state__;
        data["blynk"]["switch"]  = this->__switch_state__;
		data["timers"]["timer1"] = this->__Timer1__;
		data["timers"]["timer2"] = this->__Timer2__;
		data["timers"]["timer3"] = this->__Timer3__;

        serializeJson(data, myserial);
    }
}