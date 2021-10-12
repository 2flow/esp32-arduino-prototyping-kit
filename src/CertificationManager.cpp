//
// Created by f.wimmer on 08.10.2021.
//

#include <EEPROM.h>
#include "CertificationManager.h"

#define MAGIC_BYTE_1 0x5B
#define MAGIC_BYTE_2 0x47

#define MAGIC_BYTE_1_POS 0
#define MAGIC_BYTE_2_POS 1
#define CERT_LEN_POS 2
#define PK_LEN_POS 4
#define CERT_DATA_POS 6

using namespace httpsserver;

httpsserver::SSLCert CertificationManager::sCert = SSLCert();
bool CertificationManager::sAvailable = false;
bool CertificationManager::sIsInEEPROM = true;

void CertificationManager::calculateChecksum(uint8_t &previous, const uint8_t *pData, size_t len) {
    for(size_t i = 0; i < len; i ++){
        previous ^= pData[i];
    }
}

bool CertificationManager::createCertificate(std::basic_string<char> host) {
    auto logMsg = "Create certificate for host '" + host + "' ";
    Serial.println(logMsg.c_str());
    int result = createSelfSignedCert(
            sCert,
            KEYSIZE_1024,
            "CN=" + host + ".local,O=FancyCompany,C=DE",
            "20190101000000",
            "20300101000000"
    );

    // Now check if creating that worked
    if (result != 0) {
        Serial.printf("Cerating certificate failed. Error Code = 0x%02X, check SSLCert.hpp for details\r\n", result);
        return false;
    }
    Serial.printf("Creating the certificate was successful Code = 0x%02X \r\n",result);

    return true;
}

bool CertificationManager::saveToEEPROM() {
    uint8_t checkSum = MAGIC_BYTE_2;
    uint16_t certLen = sCert.getCertLength();
    uint16_t pkLen = sCert.getPKLength();
    calculateChecksum(checkSum, (uint8_t*)&certLen, 2);
    calculateChecksum(checkSum, (uint8_t*)&pkLen, 2);

    uint8_t *pCertificate = sCert.getCertData();
    uint8_t *pPK = sCert.getPKData();

    calculateChecksum(checkSum, pCertificate, certLen);
    calculateChecksum(checkSum, pPK, pkLen);

    EEPROM.write(MAGIC_BYTE_1_POS, MAGIC_BYTE_1);
    EEPROM.write(MAGIC_BYTE_2_POS, MAGIC_BYTE_2);
    EEPROM.writeUShort(CERT_LEN_POS, certLen);
    EEPROM.writeUShort(PK_LEN_POS, pkLen);

    EEPROM.writeBytes(CERT_DATA_POS, pCertificate, certLen);
    EEPROM.writeBytes(CERT_DATA_POS + certLen, pPK, pkLen);
    EEPROM.write(CERT_DATA_POS + certLen + pkLen, checkSum);

    if(EEPROM.commit()) {
        Serial.println("Successfully saved certificate");
        return true;
    }
    else {
        Serial.println("Unable to save certificate");
        return false;
    }
}

bool CertificationManager::loadFromEEPROM() {
    Serial.println("Load certificate from memory ...");
    uint16_t certLen = EEPROM.readUShort(CERT_LEN_POS);
    uint16_t pkLen = EEPROM.readUShort(PK_LEN_POS);

    auto pCertificate = new uint8_t[certLen];
    auto pPK = new uint8_t[pkLen];

    if(EEPROM.readBytes(CERT_DATA_POS, pCertificate, certLen) != certLen)
    {
        Serial.println("unable to load Certificate from memory");
        delete[] pCertificate;
        delete[] pPK;
        return false;
    }

    if(EEPROM.readBytes(CERT_DATA_POS + certLen, pPK, pkLen) != pkLen)
    {
        Serial.println("unable to load pk from memory");
        delete[] pCertificate;
        delete[] pPK;
        return false;
    }

    uint8_t checkSumInMemory = EEPROM.read(CERT_DATA_POS + certLen + pkLen);
    uint8_t calcChecksum = MAGIC_BYTE_2;

    calculateChecksum(calcChecksum, (uint8_t *)&certLen, 2);
    calculateChecksum(calcChecksum, (uint8_t *)&pkLen, 2);
    calculateChecksum(calcChecksum, pCertificate, certLen);
    calculateChecksum(calcChecksum, pPK, pkLen);

    if(checkSumInMemory != calcChecksum){
        Serial.println("Checksumms do not match");
        return false;
    }

    sCert.setCert(pCertificate, certLen);
    sCert.setPK(pPK, pkLen);

    Serial.println("loaded Certificate from memory");
    Serial.println();

    return true;
}

httpsserver::SSLCert &CertificationManager::getCertificate() {
    return sCert;
}

void CertificationManager::loadCertificate(const char *host, FS *fileSystem, char const *fsPath) {

    if(!sAvailable) {
        if ((fileSystem != nullptr) && (fsPath != nullptr) && true) {
            // TODO implement with file system
        } else {
            EEPROM.begin(4000);
            sAvailable = loadWithEEPROM(host);
        }

    }

}

bool CertificationManager::loadWithEEPROM(char const * const host) {
    uint8_t magic1 = EEPROM.readByte(0);
    uint8_t magic2 = EEPROM.readByte(1);

    Serial.printf("magic bytes: 1: 0x%02X/2: 0x%02X \r\n",magic1, magic2);

    if ((magic1 == MAGIC_BYTE_1) && (magic2 == MAGIC_BYTE_2)) {
        if (!loadFromEEPROM()) {
            sAvailable = createCertificate(host);
        }else{
            sAvailable = true;
        }

    } else {
        sAvailable = createCertificate(host);
        if(sAvailable){
            saveToEEPROM();
        }
    }

    return sAvailable;
}

