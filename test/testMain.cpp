//
// Created by f.wimmer on 11.10.2021.
//
#include "stdio.h"

#include "AbstractChannel.h"
#include "ActualServiceProvider.h"
#include "ActualChannel.h"
ActualServiceProvider<10,AbstractChannel<>> notifyProvider(true);
ActualChannel<10> msChannel;
ActualServiceProvider<10,AbstractChannel<int, char*>> notifyProvider2;

#include "ServiceProvider.h"
#include "StdLog.h"


class ChannelX : public IChannelSink<>{
public:
    void channelEvent() override{
        printf("Event called");
    }
};

class ChannelZ : public IChannelSink<>{
public:
    void channelEvent() override{
        printf("Second channel called");
    }
};


ChannelX channelx;
ChannelZ ch;
StdLog stdLog;

int main(){
    stdLog.setAsGlobal();
    Log::error("testmessage \r\n");
    msChannel.addSink(&channelx);
    msChannel.addSink(&ch);
    ServiceProvider<AbstractChannel<>>::setGlobalService("msTick", &msChannel);

    auto service = ServiceProvider<AbstractChannel<>>::getGlobalService("msTick");//->sendChannelEvent();
    if(service != nullptr){
        service->sendChannelEvent();
    }
 return 0;
}