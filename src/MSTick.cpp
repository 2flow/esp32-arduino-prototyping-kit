//
// Created by f.wimmer on 08.10.2021.
//

#include "MSTick.h"
#include "ServiceProvider.h"
#include "AbstractChannel.h"

static bool isMSTick = false;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

hw_timer_t* MSTick::sHWTimer = nullptr;
bool MSTick::sIsInited = false;
void IRAM_ATTR on1MS()
{
    portENTER_CRITICAL_ISR(&timerMux);
    if(!isMSTick) {
        isMSTick = true;
    }
    portEXIT_CRITICAL_ISR(&timerMux);
}

void MSTick::init(size_t coreTickInMhz ) {

    if(!sIsInited) {
        // Configure the Prescaler at 80 the quarter of the ESP32 is cadence at 80Mhz
        // 80000000 / 80 = 1000000 tics / seconde
        sHWTimer = timerBegin(0, coreTickInMhz, true);
        timerAttachInterrupt(sHWTimer, &on1MS, true);

        timerAlarmWrite(sHWTimer, 1000, true);
        timerAlarmEnable(sHWTimer);

        sIsInited = true;
    }
}

void MSTick::loop() {
    ServiceProvider<AbstractChannel<>>::getGlobalService("msTick")->sendChannelEvent();
}
