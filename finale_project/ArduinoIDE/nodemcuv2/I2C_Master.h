/*! @file I2C_Master.h
 *  @version 1.0.0
*/

#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include <Wire.h>

class I2C_Master {
public:
  I2C_Master(uint8_t slaveAddress) : _slaveAddress(slaveAddress) { /*TODO(Not yet implemented)*/ }

  void begin(uint8_t __SDA__, uint8_t __SCL__) {
    Wire.begin(__SDA__, __SCL__);
  }

  void setCapacity(float capacity) {
    this->__capacity__ = capacity;
  }

  void setBlynkCmd(bool auto_state, bool switch_state) {
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
    if ((unsigned long)(millis() - this->LastSendData) >= (unsigned long)__delay__) {
      this->LastSendData = millis();
      StaticJsonDocument<500> data;

      data["capacity"]         = this->__capacity__;
      data["blynk"]["auto"]    = this->__auto_state__;
      data["blynk"]["switch"]  = this->__switch_state__;
      data["timers"]["timer1"] = this->__Timer1__;
      data["timers"]["timer2"] = this->__Timer2__;
      data["timers"]["timer3"] = this->__Timer3__;

      // Serialisasi JSON dan kirim data ke Arduino Uno (slave)
      char jsonBuffer[500];
      size_t n = serializeJson(data, jsonBuffer);

      Wire.beginTransmission(_slaveAddress);  // Mulai transmisi
      Wire.write(jsonBuffer, n);  // Mengirim data JSON
      Wire.endTransmission();
    }
  }

private:
  String __Timer1__ = "7:0:0", __Timer2__ = "12:0:0", __Timer3__ = "17:0:0";
  int __capacity__;
  bool __auto_state__, __switch_state__;
  unsigned long LastSendData = 0;

private:
  uint8_t _slaveAddress;
};