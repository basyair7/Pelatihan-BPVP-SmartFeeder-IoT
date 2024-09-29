/*! @file SerialData.h
 *  @version 1.0.1
*/

#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

class SerialData {
public:
  SerialData(uint8_t __rx__, uint8_t __tx__) : myserial(__rx__, __tx__) { /*TODO(NOT yet implemented)*/ }

  void setDistance(float distance) {
    this->__distance__ = distance;
  }

  void setBlynkCmd(bool auto_state, bool switch_state)
  {
    this->__auto_state__   = auto_state;
    this->__switch_state__ = switch_state;
  }

  void setTimeAuto(const String Timer1, const String Timer2, const String Timer3)
  {
    this->__Timer1__ = Timer1;
    this->__Timer2__ = Timer2;
    this->__Timer3__ = Timer3;
  }

  void runSendData(long __delay__) {
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

private:
  String __Timer1__ = "7:0:0", __Timer2__ = "12:0:0", __Timer3__ = "17:0:0";
  float __distance__;
  bool __auto_state__, __switch_state__;
  unsigned long LastSendData = 0;

private:
  SoftwareSerial myserial;

};
