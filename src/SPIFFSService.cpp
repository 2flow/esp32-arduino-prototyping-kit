//
// Created by f.wimmer on 08.10.2021.
//
#include <SPIFFS.h>
#include <FS.h>
#include "SPIFFSService.h"
#include "ServiceProvider.h"

void SPIFFSService::init() {
// Try to mount SPIFFS without formatting on failure
    if (!SPIFFS.begin(false)) {
        // If SPIFFS does not work, we wait for serial connection...

        Serial.println("Start formating");

        // If the user did not accept to try formatting SPIFFS or formatting failed:
        if (!SPIFFS.begin(true)) {
            Serial.println("SPIFFS not available. Stop.");
            while(true);
        }
        Serial.println("SPIFFS has been formated.");
    }
    Serial.println("SPIFFS has been mounted.");
}

void SPIFFSService::useAsFSService() {
    ServiceProvider<FS>::setGlobalService(&SPIFFS);

}
