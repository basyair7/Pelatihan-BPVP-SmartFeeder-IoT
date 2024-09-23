
#pragma once

#include "Arduino.h"
#include "ESP8266WiFi.h"

class ProgramWiFi {
public:
    void begin() {
        WiFi.mode(WIFI_STA);
        while (WiFi.status() != WL_CONNECTED) {
            for (int i = 0; i < numNetwork; i++) {
                Serial.print(F("Trying to connect to SSID"));
                Serial.println(this->LIST_SSID[i]);

                WiFi.begin(LIST_SSID[i].c_str(), LIST_PASS[i].c_str());

                int attempt = 0;
                while (WiFi.status() != WL_CONNECTED && attempt < 10) {
                    delay(1000L);
                    Serial.print(F("."));
                    attempt++;
                }

                if (WiFi.status() == WL_CONNECTED) {
                    Serial.println();
                    Serial.print(F("Connected to : "));
                    Serial.print(this->LIST_SSID[i]);
                    Serial.print(F(" ("));
                    Serial.print(this->LIST_PASS[i]);
                    Serial.println(F(")"));

                    this->SSID = this->LIST_SSID[i];
                    this->PASSWORD = this->LIST_PASS[i];
                    return;
                }

                Serial.println();
                Serial.println(F("Failed to connected, trying next to SSID..."));
            }

            Serial.println(F("Retrying all networks after a brief delay..."));
            delay(5000); // Wait for 5 seconds before retrying all networks
        }
    }

public:
    String SSID = "", PASSWORD = "";

private:
    const String LIST_SSID[3] = { "elektronika@BPVPACEH", "Free_wifi@BPVP.BandaAceh", "@Wifi.com 23" };
    const String LIST_PASS[3] = { "elektronika23", "", "Hostpot_ahul7" };
    const int numNetwork = sizeof(LIST_SSID) / sizeof(LIST_SSID[0]);
};
