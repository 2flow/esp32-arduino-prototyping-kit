//
// Created by f.wimmer on 11.10.2021.
// TODO("Move to global prototyping lib")

#ifndef ESP32PROROTYPINGLIB_ABSTRACTCHANNEL_H
#define ESP32PROROTYPINGLIB_ABSTRACTCHANNEL_H

#include <cstddef>

template <typename ...Types>
class IChannelSink{
public:
    virtual void channelEvent(Types... args) = 0;

    virtual ~IChannelSink() = default;
};


template <typename ...Types>
class AbstractChannel {
public:
    void sendChannelEvent(Types...);
    virtual void addSink(IChannelSink<Types...>* sink) = 0;

    virtual  ~AbstractChannel() = default;

protected:
    inline virtual size_t onGetSinkCount() = 0;
    inline virtual IChannelSink<Types...>* onGetChannel(size_t id) = 0;
};

template<typename... Types>
void AbstractChannel<Types...>::sendChannelEvent(Types... args) {
    size_t sinkCount = onGetSinkCount();

    for(size_t i = 0; i < sinkCount; i++){
        auto channel = onGetChannel(i);
        channel->channelEvent(args...);
    }
}


#endif //ESP32PROROTYPINGLIB_ABSTRACTCHANNEL_H
