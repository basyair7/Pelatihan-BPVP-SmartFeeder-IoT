#include "Arduino.h"
#include "envBlynk.h"
#include "BlynkSimpleEsp8266.h"
#include "WiFiProgram.h"
#include "ultrasonic.h"

#define TRIGGER_PIN   D5
#define ECHO_PIN      D6

Ultrasonic* hcsr04_1 = new Ultrasonic(TRIGGER_PIN, ECHO_PIN);
ProgramWiFi* programWiFi = new ProgramWiFi();
BlynkTimer timer;

void bacaSensor(void) {
  float getDistance = hcsr04_1->getDistance();
  Serial.print(F("Jarak : "));
  Serial.print(getDistance);
  Serial.println(F(" cm"));

  Blynk.virtualWrite(V0, getDistance);
  delay(100);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  hcsr04_1->begin();
  programWiFi->begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, programWiFi->SSID.c_str(), programWiFi->PASSWORD.c_str());

  timer.setInterval(100L, bacaSensor);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();
}
