#include "SerialData.h"
#include "ArduinoJson.h"

void SerialData::sendDistance(float __distance__) {
    this->__distance__ = __distance__;
}

void SerialData::sendBlynkCmd(bool __auto__, bool __switch__)
{
    this->__auto__   = __auto__;
    this->__switch__ = __switch__;
}

void SerialData::runSendData(long __delay__) {
    if ((unsigned long) (millis() - this->LastSendData) >= (unsigned long)__delay__) {
        this->LastSendData = millis();
        StaticJsonDocument<500> data;

        data["distance"]        = this->__distance__;
        data["blynk"]["auto"]   = this->__auto__;
        data["blynk"]["switch"]   = this->__switch__;

        serializeJson(data, myserial);
    }
}