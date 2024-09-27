/*! @file programWiFi.cpp
 *  @version 3.0.15
*/

#include <ProgramWiFi.h>
#include <BootButton.h>

// run program if WiFi connecting 
void ProgramWiFi::onWiFiConnect(const WiFiEventStationModeGotIP& event) 
{
    Serial.println(F(""));
    Serial.print(F("Connected to : ")); Serial.println(this->__SSID_STA__);
    Serial.print(F("IP Address : ")); Serial.println(event.ip);
    this->LOCALIPServer = event.ip.toString().c_str();
}

// run prorgam if WiFi disconnect
void ProgramWiFi::onWiFiDisconnect(const WiFiEventStationModeDisconnected& event) 
{
    WiFi.disconnect();
    WiFi.begin(this->__SSID_STA__, this->__PASSWORD_STA__);
}

void ProgramWiFi::setup(const String __SSID_STA__, const String __PASSWORD_STA__, const String __SSID_AP__, const String __PASSWORD_AP__) 
{
    this->__SSID_STA__ = __SSID_STA__; this->__PASSWORD_STA__ = __PASSWORD_STA__;
    this->__SSID_AP__  = __SSID_AP__; this->__PASSWORD_AP__ = __PASSWORD_AP__;
}

// run program mode STA
void ProgramWiFi::Mode_STA() {
    BootButton bootbutton(BOOTBUTTON, INPUT);
    // setup WiFi mode AP STA
    // WiFi.mode(WIFI_AP_STA);
    WiFi.mode(WIFI_STA);

    // register event handlers
    wifiConnectHandler = WiFi.onStationModeGotIP(std::bind(&ProgramWiFi::onWiFiConnect, this, std::placeholders::_1));
    wifiDisconnectHandler = WiFi.onStationModeDisconnected(std::bind(&ProgramWiFi::onWiFiDisconnect, this, std::placeholders::_1));

    // initializing WiFi and Connecting to an SSID
    WiFi.begin(this->__SSID_STA__, this->__PASSWORD_STA__);
    Serial.print(F("Connecting to WiFi..."));
    while(WiFi.status() != WL_CONNECTED) {
        bootbutton.WiFiMode();
        Serial.print(F("."));
        delay(500);
    }

    // RSSI
    Serial.print(F("\nRRSI : "));
    Serial.println(WiFi.RSSI());
}

// run program mode AP
void ProgramWiFi::Mode_AP() {
    // setup WiFi mode AP
    WiFi.mode(WIFI_AP);
    
    // initializing Access Point
    WiFi.softAP(this->__SSID_AP__, this->__PASSWORD_AP__);

    // get IP Address
    this->LOCALIPServer = WiFi.softAPIP().toString().c_str();
    Serial.print(F("IP Address : "));
    Serial.println(this->LOCALIPServer);
    Serial.println();
}

/* program initialize wifi
 * Mode AP = true
 * Mode AP STA = false
*/
void ProgramWiFi::initWiFi(bool state) {
    WifiState = state;
    Serial.print(F("\nMode WiFi : "));
    Serial.println(state ? "MODE_AP" : "MODE_STA");
    if(state) {
        Mode_AP();
    } 
    else {
        Mode_STA();
    }
}
