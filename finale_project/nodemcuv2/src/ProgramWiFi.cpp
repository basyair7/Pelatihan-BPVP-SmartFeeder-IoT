/*! @file programWiFi.cpp
 *  @version 3.0.15
*/

#include <programWiFi>
#include <BootButton>

String ssid_sta, password_sta;
String Name_AP, Password_AP;
String LOCALIPServer;
bool WifiState;

// run program if WiFi connecting 
void ProgramWiFi::onWiFiConnect(const WiFiEventStationModeGotIP& event) 
{
    TSprintln(F(""));
    TSprint(F("Connected to : ")); TSprintln(ssid_sta);
    TSprint(F("IP Address : ")); TSprint(event.ip);
    LOCALIPServer = event.ip.toString().c_str();
}

// run prorgam if WiFi disconnect
void ProgramWiFi::onWiFiDisconnect(const WiFiEventStationModeDisconnected& event) 
{
    WiFi.disconnect();
    WiFi.begin(ssid_sta, password_sta);
}

void ProgramWiFi::setup(const String SSID, const String PASSWORD_SSID, const String NAME_AP, const String PASSWORD_AP) 
{
    ssid_sta = SSID; password_sta = PASSWORD_SSID;
    Name_AP = NAME_AP; Password_AP = PASSWORD_AP;
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
    WiFi.begin(ssid_sta, password_sta);
    Serial.print(F("Connecting to WiFi..."));
    while(WiFi.status() != WL_CONNECTED) {
        bootbutton.WiFiMode();
        TSprint(F("."));
        delay(500);
    }

    // RSSI
    Serial.print(F("\nRRSI : "));
    Serial.println(WiFi.RSSI());

    // initializing Access Point
    // WiFi.softAP(Name_AP, Password_AP);
    // get IP Address
    // LOCALIPServer = WiFi.softAPIP().toString().c_str();
    // Serial.print(F("IP Address Server : "));
    // Serial.println(LOCALIPServer);
    // Serial.println();
}

// run program mode AP
void ProgramWiFi::Mode_AP() {
    // setup WiFi mode AP
    WiFi.mode(WIFI_AP);
    
    // initializing Access Point
    WiFi.softAP(Name_AP, Password_AP);

    // get IP Address
    LOCALIPServer = WiFi.softAPIP().toString().c_str();
    Serial.print(F("IP Address : "));
    Serial.println(LOCALIPServer);
    Serial.println();
}

/* program initialize wifi
 * Mode AP = true
 * Mode AP STA = false
*/
void ProgramWiFi::initWiFi(bool state) {
    LEDBoard ledboard;
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
