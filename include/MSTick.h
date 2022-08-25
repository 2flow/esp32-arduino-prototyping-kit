//
// Created by f.wimmer on 08.10.2021.
//

#ifndef ESP32PROROTYPINGLIB_MSTICK_H
#define ESP32PROROTYPINGLIB_MSTICK_H

#include "esp32-hal-timer.h"

class IEventReceiver{
public:

};

class MSTick {
public:
    static void init(bool publishToService = false, size_t coreTickInMhz = 80);
    static bool loop();

private:
    static bool sIsInited;
    static hw_timer_t* sHWTimer;
    static bool sPublishToService;
};


#endif //ESP32PROROTYPINGLIB_MSTICK_H
