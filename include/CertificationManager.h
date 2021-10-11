//
// Created by f.wimmer on 08.10.2021.
//

#ifndef ESP32PROROTYPINGLIB_CERTIFICATIONMANAGER_H
#define ESP32PROROTYPINGLIB_CERTIFICATIONMANAGER_H


#include <SSLCert.hpp>
#include "FS.h"
class CertificationManager {
public:
    /**
     * Will load or create a ssl certificate
     * loading from file system is currently not supported
     * @param host          the host for which the file should be created in case it needs to be created
     * @param fileSystem    if the certificate should be loaded and stored on a filesystem
     */
    static void loadCertificate(char const *host, FS* fileSystem = nullptr, char const *fsPath = nullptr);
    static httpsserver::SSLCert & getCertificate();

private:
    static bool sIsInEEPROM;
    static httpsserver::SSLCert sCert;
    static bool sAvailable;

    static void calculateChecksum(uint8_t &previous, uint8_t const *pData, size_t len);
    static bool createCertificate(std::basic_string<char> host);
    static bool loadFromEEPROM();
    static bool saveToEEPROM();
    static bool loadWithEEPROM(char const * const host);
};


#endif //ESP32PROROTYPINGLIB_CERTIFICATIONMANAGER_H
