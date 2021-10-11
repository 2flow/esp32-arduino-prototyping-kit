//
// Created by f.wimmer on 11.10.2021.
//

#ifndef ESP32PROROTYPINGLIB_CHANNELDI_H
#define ESP32PROROTYPINGLIB_CHANNELDI_H

#include "AbstractChannelDI.h"
#include "AbstractChannel.h"
template <int CHANNEL_COUNT, typename ...Types>
class ChannelDI : AbstractChannelDI<Types...> {
public:
    AbstractChannel<Types...>* getChannel(char *channelName) const override;
private:
    AbstractChannel<Types...>* mChannels[CHANNEL_COUNT];
    char* mChannelNames[CHANNEL_COUNT];
};



#endif //ESP32PROROTYPINGLIB_CHANNELDI_H
