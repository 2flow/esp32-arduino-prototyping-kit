//
// Created by f.wimmer on 08.10.2021.
//

#ifndef ESP32PROROTYPINGLIB_NETWORKMANAGER_H
#define ESP32PROROTYPINGLIB_NETWORKMANAGER_H

/**
 * The NetworkManager takes care of connecting and maintaining the network
 */
class NetworkManager {
public:
    static void start(const char *ssid, const char *password, char const *dnsName, bool waitForConnection = true);
    static bool isConnected();
    static bool addMDNSService(char const* service, char const* protocol, uint16_t port);
private:
    static bool sWifiStarted;
};

#endif //ESP32PROROTYPINGLIB_NETWORKMANAGER_H
