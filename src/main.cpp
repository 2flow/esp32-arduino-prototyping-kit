#include <Arduino.h>
#include "AbstractChannel.h"
#include "ActualServiceProvider.h"
#include "ActualChannel.h"
#include "MSTick.h"
ActualServiceProvider<10,AbstractChannel<>> notifyProvider(true);
ActualChannel<10> msChannel;
ActualServiceProvider<10,AbstractChannel<int, char*>> notifyProvider2;

#include "ServiceProvider.h"





void setup() {
    notifyProvider.setService("msTick", &msChannel);
    // write your initialization code here
    MSTick::init();

}

void loop() {
// write your code here
}