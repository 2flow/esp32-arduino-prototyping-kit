//
// Created by f.wimmer on 11.10.2021.
// TODO("Move to global prototyping lib")

#ifndef ESP32PROROTYPINGLIB_SERVICEPROVIDER_H
#define ESP32PROROTYPINGLIB_SERVICEPROVIDER_H

#include "stdlib.h"

template <typename TService>
class ServiceProvider {
public:
    virtual TService* getService(char const *serviceName) const = 0;
    virtual TService* getService() const = 0;

    virtual void setService(char const *serviceName, TService* service)  = 0;
    virtual void setService(TService*  service) = 0;

    static void setServiceProvider(ServiceProvider<TService>* serviceProvider);
    static ServiceProvider<TService>* getServiceProvider();

    static TService* getGlobalService(char const *serviceName = nullptr);
    static void setGlobalService(char const *serviceName, TService* service);
    static void setGlobalService(TService *service);

    virtual ~ServiceProvider() = default;
private:
    static ServiceProvider<TService>* sServiceProvider;
};
template<typename TService>
ServiceProvider<TService>* ServiceProvider<TService>::sServiceProvider = nullptr;

template<typename TService>
void ServiceProvider<TService>::setServiceProvider(ServiceProvider<TService> *serviceProvider) {
    sServiceProvider = serviceProvider;
}

template<typename TService>
ServiceProvider<TService> *ServiceProvider<TService>::getServiceProvider() {
    return sServiceProvider;
}

template<typename TService>
TService *ServiceProvider<TService>::getGlobalService(const char *serviceName) {
    if(sServiceProvider != nullptr){
        return sServiceProvider->getService(serviceName);
    }else{
        // TODO("write to error loging");
        return nullptr;
    }
}

template<typename TService>
void ServiceProvider<TService>::setGlobalService(const char *serviceName, TService *service) {
    if(sServiceProvider != nullptr){
        return sServiceProvider->setService(serviceName, service);
    }else{
        // TODO("write to error loging");
    }
}

template<typename TService>
void ServiceProvider<TService>::setGlobalService(TService *service) {
    if(sServiceProvider != nullptr){
        return sServiceProvider->setService(service);
    }else{
        // TODO("write to error loging");
    }
}


#endif //ESP32PROROTYPINGLIB_SERVICEPROVIDER_H
