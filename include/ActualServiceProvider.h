//
// Created by f.wimmer on 11.10.2021.
// TODO("Move to global prototyping lib")

#ifndef ESP32PROROTYPINGLIB_ACTUALSERVICEPROVIDER_H
#define ESP32PROROTYPINGLIB_ACTUALSERVICEPROVIDER_H

#include "stdlib.h"
#include <cstddef>
#include <string.h>
#include "ServiceProvider.h"

template <int SERVICE_MAX_COUNT, typename TService>
class ActualServiceProvider : public ServiceProvider<TService> {
public:
    ActualServiceProvider(bool setAsGlobal = false);

    TService* getService(char const *serviceName) const override;
    TService* getService() const override;

    void setService(char const *serviceName, TService* service) override;
    void setService(TService*  service) override;

private:
    TService* mServices[SERVICE_MAX_COUNT + 1];
    char const * mServiceNames[SERVICE_MAX_COUNT + 1];

    size_t mServiceCount = 0;
};

template<int SERVICE_MAX_COUNT, typename TService>
TService *ActualServiceProvider<SERVICE_MAX_COUNT, TService>::getService(const char *serviceName) const {
    if(serviceName == nullptr){
        return mServices[SERVICE_MAX_COUNT];
    }else{
        for(size_t i = 0; i < mServiceCount; i++){
            if(strcmp(serviceName, mServiceNames[i]) == 0){
                return mServices[i];
            }
        }
    }

    return nullptr;
}

template<int SERVICE_MAX_COUNT, typename TService>
void ActualServiceProvider<SERVICE_MAX_COUNT, TService>::setService(const char *serviceName, TService *service) {
    for(size_t i = 0; i < mServiceCount; i++){
        if(strcmp(serviceName, mServiceNames[i]) == 0){
            mServices[i] = service;
            return;
        }
    }

    if(mServiceCount < SERVICE_MAX_COUNT) {
        mServices[mServiceCount] = service;
        mServiceNames[mServiceCount] = serviceName;

        mServiceCount++;
    }else{
        // TODO log something
    }
}

template<int SERVICE_MAX_COUNT, typename TService>
TService *ActualServiceProvider<SERVICE_MAX_COUNT, TService>::getService() const {
    return mServices[SERVICE_MAX_COUNT];
}

template<int SERVICE_MAX_COUNT, typename TService>
void ActualServiceProvider<SERVICE_MAX_COUNT, TService>::setService(TService *service) {
    mServices[SERVICE_MAX_COUNT] = service;
}

template<int SERVICE_MAX_COUNT, typename TService>
ActualServiceProvider<SERVICE_MAX_COUNT, TService>::ActualServiceProvider(bool setAsGlobal) {
    if(setAsGlobal){
        ServiceProvider<TService>::setServiceProvider(this);
    }
}


#endif //ESP32PROROTYPINGLIB_ACTUALSERVICEPROVIDER_H
