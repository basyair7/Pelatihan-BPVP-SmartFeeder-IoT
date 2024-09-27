#include "main.h"
#include "EEPROM.h"

#include "BootButton.h"
#include "ultrasonic.h"
#include "ProgramWiFi.h"
#include "WebServer.h"
#include "SerialData.h"

#include "WIFISETTING.h"
#include "variable.h"

#include "envBlynk.h"
#include "BlynkSimpleEsp8266.h"

BlynkTimer TIMER;

ProgramWiFi programWiFi;
WebServer webServer(80);
SerialData serialData(RX_TX, TX_RX);

BootButton bootBtn(BOOTBUTTON, INPUT);
Ultrasonic ultrasonic(TRIG_PIN, ECHO_PIN);

unsigned long LastTimeGetDistance = 0, LastTimeLED = 0;
bool __switch_state__ = false, __auto__ = false;
float distance;

BLYNK_WRITE(V1) {
	int paramBlynk = param.asInt();
	__switch_state__ = (paramBlynk == 1 ? true : false);
}

BLYNK_WRITE(V2) {
	int paramBlynk = param.asInt();
	__auto__ = (paramBlynk == 1 ? true : false);
}

void getDistance(void) {
	if ((unsigned long) (millis() - LastTimeGetDistance) >= 100) {
		LastTimeGetDistance = millis();

		distance = ultrasonic.getDistance();
		Serial.print(F("Jarak : "));
		Serial.print(distance);
		Serial.println(F(" cm"));

		Blynk.virtualWrite(V0, distance);
	}
}

void indikator(void) {
	if ((unsigned long) (millis() - LastTimeLED) >= 100) {
		LastTimeLED = millis();

		if (distance < 5 || distance > 14) {
			digitalWrite(LED_YELLOW, HIGH);
			digitalWrite(LED_RED, LOW);
		}

		if (distance >= 15) {
			digitalWrite(LED_YELLOW, LOW);
			digitalWrite(LED_RED, HIGH);
		}
	}
}

void setup() {
	Serial.begin(115200);
	ultrasonic.begin();
	bootBtn.begin();

	pinMode(LED_RED, OUTPUT);
	pinMode(LED_YELLOW, OUTPUT);

	programWiFi.setup(SSID_STA, PASSWORD_STA, SSID_AP, PASSWORD_AP);
	
	bool wifiState = EEPROM.read(EEPROM_BLYNK_ADDR);
	programWiFi.initWiFi(wifiState);
	webServer.Serverinit();

	TIMER.setInterval(100L, getDistance);
}

void loop() {
	indikator();
	serialData.sendBlynkCmd(__auto__, __switch_state__);
	serialData.sendDistance(distance);
	serialData.runSendData(50);

	Blynk.run();
	TIMER.run();
}