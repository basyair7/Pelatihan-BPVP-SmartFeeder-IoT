#include "index.h"
#include "envBlynk.h"
#include "BlynkSimpleEsp8266.h"

#define PIN_POTENSIO    A0

BlynkTimer TIMER;
ProgramWiFi WIFIPROGRAM;

const int LED_PINS[2] = { D4, D5 };
int value = 0;

BLYNK_WRITE(V1) {
    int paramBlynk = param.asInt();

    digitalWrite(LED_PINS[0], paramBlynk == 1 ? HIGH : LOW);
    Blynk.virtualWrite(V3, digitalRead(LED_PINS[0]));
    Serial.print(F("LED STATUS : "));
    Serial.println(digitalRead(LED_PINS[0]) ? "ON" : "OFF");
}

BLYNK_WRITE(V2) {
    int paramBlynk = param.asInt();
    digitalWrite(LED_PINS[1], paramBlynk == 1 ? HIGH : LOW);
    Blynk.virtualWrite(V4, digitalRead(LED_PINS[1]));
    Serial.print(F("LED STATUS : "));
    Serial.println(digitalRead(LED_PINS[1]) ? "ON" : "OFF");
}

void potensio(void) {
    value = map(analogRead(PIN_POTENSIO), 16, 1024, 0, 100);
    Serial.print(F("Potensio Value : "));
    Serial.println(value);

    Blynk.virtualWrite(V0, value);
}

void MyProgram::_setup(void) {
    Serial.begin(9600);
    for (const auto i : LED_PINS) {
        pinMode(i, OUTPUT);
    }

    pinMode(PIN_POTENSIO, INPUT);
    WIFIPROGRAM.begin();
    Blynk.begin(BLYNK_AUTH_TOKEN, WIFIPROGRAM.SSID.c_str(), WIFIPROGRAM.PASSWORD.c_str());

    TIMER.setInterval(50L, potensio);
}

void MyProgram::_loop(void) {
    Blynk.run();
    TIMER.run();
}
