//
// Created by f.wimmer on 11.10.2021.
//

#ifndef ESP32PROROTYPINGLIB_ABSTRACTCHANNELDI_H
#define ESP32PROROTYPINGLIB_ABSTRACTCHANNELDI_H
#include "AbstractChannel.h"

template <typename ... Types>
class AbstractChannelDI {
public:
    virtual AbstractChannel<Types...>* getChannel(char *channelName) const = 0;

    static void setChannelDI(AbstractChannelDI<Types...>* channelDI);
    static AbstractChannelDI<Types...>* getChannelDI();

    virtual ~AbstractChannelDI() = default;
private:
    static AbstractChannelDI<Types...>* sChannelDI;
};


#endif //ESP32PROROTYPINGLIB_ABSTRACTCHANNELDI_H
