#include <WebServer.h>
#include "WIFISETTING.h"

void WebServer::RecoveryPage(AsyncWebServerRequest *req) {
    this->file = openfile("/WEB/html/recovery.html", LFS_READ);
    if (!this->file) {
        req->send(404, "text/plain", "File not found");
        return;
    }

    // read file content
    size_t fileSize = file.size();
    char* htmlBuffer = new char[fileSize + 1];
    file.readBytes(htmlBuffer, fileSize);
    htmlBuffer[fileSize] = '\0';
    file.close();

    // get ip address
    IPAddress clientIP = req->client()->localIP();
    this->LOCALIP = clientIP.toString();

    const char* placeholders[] = {
        "%LOCALIP%",
        "%VERSIONPROJECT%", "%HWVERSION%", "%SWVERSION%",
        "%BUILDDATE%", "%FIRMWAREREGION%",
        "%LOCALIP%", "%SSIDAP%", "%PASSWORDAP%", "%SSIDSTA%", "%PASSWORDSTA%",
        "%LOCALIP%", "%LOCALIP%"
    };

    const char* tags_html[] = {
        this->LOCALIP.c_str(),
        String(VERSIONPROJECT).c_str(), String(HWVERSION).c_str(), String(SWVERSION).c_str(),
        String(BUILDDATE).c_str(), String(REGION).c_str(),
        this->LOCALIP.c_str(), String(SSID_AP).c_str(), String(PASSWORD_AP).c_str(),
        String(SSID_STA).c_str(), String(PASSWORD_STA).c_str(),
        this->LOCALIP.c_str(), this->LOCALIP.c_str()
    };

    String page = htmlBuffer;
    for (int i = 0; i < (int)(sizeof(tags_html)/sizeof(tags_html[0])); i++)
    {
        page.replace(placeholders[i], tags_html[i]);
    }

    req->send_P(200, "text/html", page.c_str());
    delete[] htmlBuffer;
    
}