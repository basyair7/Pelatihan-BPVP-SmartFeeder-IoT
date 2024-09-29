/*! @file BootButton.hpp
 *  @version 1.0.0
*/

#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include <pushbutton.h>
#include "variable.h"

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
                EEPROM.put(EEPROM_BLYNK_ADDR, wifiState);
                EEPROM.commit();
				delay(5);
                Serial.println(F("MODE BLYNK : "));
                Serial.println(wifiState ? "DISABLE" : "ENABLE");
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
