#include "index.h"
#include "envBlynk.h"
#include "BlynkSimpleEsp8266.h"

#define TRIGGER_PIN   D5
#define ECHO_PIN      D6

Ultrasonic* hcsr04_1 = new Ultrasonic(TRIGGER_PIN, ECHO_PIN);

BlynkTimer TIMER;
ProgramWiFi WIFIPROGRAM;

void bacaSensor(void) {
  float getDistance = hcsr04_1->getDistance();
  Serial.print(F("Jarak : "));
  Serial.print(getDistance);
  Serial.println(F(" cm"));

  Blynk.virtualWrite(V0, getDistance);
  delay(100);
}

void MyProgram::_setup(void) {
  Serial.begin(9600);
  hcsr04_1->begin();
  WIFIPROGRAM.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFIPROGRAM.SSID.c_str(), WIFIPROGRAM.PASSWORD.c_str());

  TIMER.setInterval(100L, bacaSensor);
}

void MyProgram::_loop(void) {
  Blynk.run();
  TIMER.run();
}
