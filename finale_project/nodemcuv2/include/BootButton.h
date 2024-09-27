/*! @file BootButton.hpp
 *  @version 3.0.15
*/

#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include <pushbutton.h>
#include <variable.h>

class BootButton {
public:
    BootButton(uint8_t pin, uint8_t mode) : bootBtn(pin, mode) { }
    
    void begin() {
        bootBtn.init();
        wifiState = EEPROM.read(EEPROM_BLYNK_ADDR);
    }
    
    void WiFiMode() {
        currentButtonState = bootBtn.digitalReadPushButton();
        if (currentButtonState != lastButtonState)
            buttonChange = true;

        if (buttonChange) {
            if (currentButtonState == LOW) {
                wifiState = !wifiState;
                EEPROM.write(EEPROM_BLYNK_ADDR, wifiState);
                Serial.println(F("Change Mode WiFi : "));
                Serial.println(wifiState ? "MODE BLYNK : DISABLE" : "MODE BLYNK : ENABLE");
                delay(2000);
                ESP.reset();
            }
            buttonChange = false;
        }
        lastButtonState = currentButtonState;
    }
    
private:
    PushButtonDigital bootBtn;
    bool currentButtonState = false;
    bool lastButtonState    = false;
    bool buttonChange       = false;
    bool wifiState          = false;
};
