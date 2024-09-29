/*! @file I2CProgram.h
 *  @version 1.0.0
*/

#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include <Wire.h>

class I2C_Slave {
public:
  I2C_Slave(uint8_t slaveAddress) : _slaveAddress(slaveAddress) { /*TODO(Not yet implemented)*/ }

  void begin() {
    Wire.begin(_slaveAddress);
  }

  void getTimeAuto(String* Timer1, String* Timer2, String* Timer3) {
    *Timer1 = this->__Timer1__;
    *Timer2 = this->__Timer2__;
    *Timer3 = this->__Timer3__;
  }

  void getBlynkCmd(bool* auto_state, bool* switch_state) {
    *auto_state   = this->__auto_state__;
    *switch_state = this->__switch_state__;
  }

  int getCapacity() {
    return this->__capacity__;
  }

  void run() {
    if (Wire.available()) {
      this->receiveEvent(Wire.available());
    }
    else {
      Serial.println(F("I2C_Slave not available"));
    }
  }

private:
  void receiveEvent(int bytes) {
    StaticJsonDocument<500> data;
    char jsonBuffer[500];
    int index = 0;

    while (Wire.available()) {
      jsonBuffer[index++] = Wire.read();  // Membaca data yang diterima dari NodeMCU
    }
    jsonBuffer[index] = '\0';  // Menutup string

    DeserializationError err = deserializeJson(data, jsonBuffer);
    if (!err) {
      uint8_t code_getData = data["getdata"];
      if (code_getData) {
        this->__capacity__     = data["capacity"];
        this->__auto_state__   = data["blynk"]["auto"];
        this->__switch_state__ = data["blynk"]["switch"];

        this->__Timer1__ = data["timers"]["timer1"].as<String>();
        this->__Timer2__ = data["timers"]["timer2"].as<String>();
        this->__Timer3__ = data["timers"]["timer3"].as<String>();
      }
    } else {
      Serial.print(F("Error Deserialization : "));
      Serial.println(err.c_str());
    }
  }

private:
  String __Timer1__, __Timer2__, __Timer3__;
  int __capacity__;
  bool __auto_state__, __switch_state__;

private:
  uint8_t _slaveAddress;
};
