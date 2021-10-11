//
// Created by f.wimmer on 08.10.2021.
// Needs to go into a global package
//

#ifndef ESP32PROROTYPINGLIB_SERVICEPROVIDER_H
#define ESP32PROROTYPINGLIB_SERVICEPROVIDER_H
#include "Arduino.h"
template <typename TService>
class ServiceProvider {
public:
    /**
     * Return the service from the id, if the id is not given the first service will be returned
     * @param id For future use if there are multiple services of the same type
     * @return
     */
    static TService* getService(size_t id = 0);
    static TService* getServiceMaybe(size_t id = 0);
    static bool isServiceAvailable();

    static void setService(TService* service);
private:
    static TService* mService;
};


template <typename TService>
TService* ServiceProvider<TService>::mService = nullptr;

template <typename TService>
TService* ServiceProvider<TService>::getService(size_t id) {
    if(mService != nullptr){
        return mService;
    }else{
        Serial.println("Unable to get service. Stopping forever!");
        while (true){
            delay(1000);
        }
    }
}

template <typename TService>
TService* ServiceProvider<TService>::getServiceMaybe(size_t id) {
    return mService;
}

template<typename TService>
void ServiceProvider<TService>::setService(TService *service) {
    mService = service;
}

template<typename TService>
bool ServiceProvider<TService>::isServiceAvailable() {
    return mService != nullptr;
}


#endif //ESP32PROROTYPINGLIB_SERVICEPROVIDER_H
