//
// Created by f.wimmer on 11.10.2021.
//

#ifndef ESP32PROROTYPINGLIB_ACTUALCHANNEL_H
#define ESP32PROROTYPINGLIB_ACTUALCHANNEL_H

#include "AbstractChannel.h"

template <int MAX_OBSERVER_COUNT ,typename ...Types>
class ActualChannel : public AbstractChannel<Types...> {
public:
    void addSink(IChannelSink<Types...>* sink) override;
protected:
    inline size_t onGetSinkCount() override;
    inline IChannelSink<Types...>* onGetChannel(size_t id) override;

private:

    IChannelSink<Types...>* mChannels[MAX_OBSERVER_COUNT];
    size_t mCurrentChannelsCount = 0;
};

template<int MAX_OBSERVER_COUNT, typename... Types>
void ActualChannel<MAX_OBSERVER_COUNT, Types...>::addSink(IChannelSink<Types...>* sink) {
    if(mCurrentChannelsCount < MAX_OBSERVER_COUNT){
        mChannels[mCurrentChannelsCount] = sink;
        mCurrentChannelsCount++;
    }else{
        // TODO Add logging for channel count overflow
    }
}

template<int MAX_OBSERVER_COUNT, typename... Types>
IChannelSink<Types...> *ActualChannel<MAX_OBSERVER_COUNT, Types...>::onGetChannel(size_t id) {
    return mChannels[id];
}

template<int MAX_OBSERVER_COUNT, typename... Types>
size_t ActualChannel<MAX_OBSERVER_COUNT, Types...>::onGetSinkCount() {
    return mCurrentChannelsCount;
}


#endif //ESP32PROROTYPINGLIB_ACTUALCHANNEL_H
