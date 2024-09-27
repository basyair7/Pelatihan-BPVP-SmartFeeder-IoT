#include "main.h"
#include "WIFISETTING.h"
#include "ProgramWiFi.h"
#include "WebServer.h"
#include "EEPROM.h"
#include "variable.h"
#include "envBlynk.h"
#include "BlynkSimpleEsp8266.h"

BlynkTimer TIMER;
ProgramWiFi programWiFi;
WebServer webServer(80);

void setup() {
	Serial.begin(115200);
	programWiFi.setup(SSID_STA, PASSWORD_STA, SSID_AP, PASSWORD_AP);
	
	bool wifiState = EEPROM.read(EEPROM_BLYNK_ADDR);
	programWiFi.initWiFi(wifiState);
	webServer.Serverinit();
}

void loop() {
	
}