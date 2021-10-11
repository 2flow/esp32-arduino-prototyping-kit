//
// Created by f.wimmer on 08.10.2021.
//
#include <Arduino.h>
#include <Wifi.h>
#include <ESPmDNS.h>

#include "NetworkManager.h"
bool NetworkManager::sWifiStarted = false;

void NetworkManager::start(const char *hostName, const char *ssid, const char *password, char *dnsName, bool waitForConnection) {
    if (!sWifiStarted) {
        WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
        WiFi.setHostname(hostName);
        WiFiClass::mode(WIFI_STA);
        WiFi.begin(ssid, password);

        while ((WiFiClass::status() != WL_CONNECTED) && waitForConnection) {
            delay(500);
            Serial.print(".");
        }
        Serial.println("Wifi started");

        sWifiStarted = true;

        if (!MDNS.begin(dnsName)) {
            Serial.println("Error starting mDNS");
        }
    }
}

bool NetworkManager::isConnected() {
    return WiFiClass::status() == WL_CONNECTED;
}

bool NetworkManager::addMDNSService(const char *service, const char *protocol, uint16_t port) {
    return MDNS.addService(service, protocol, port);
}
