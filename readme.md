# ESP32 Prototyping Library

The library provides a few easy to use functionalities which allow to

# Modules
## Named Channels
The goal of this is to be create a public subscribe message service inside the application.
This enables the possibility to transfer information between source and sink, without that they know each other directly.
The channels need to be created in the beginning of the program. As soon es they are registered application parts
can observe them.


# Troubles
## Undefined modules
If there is a not found headerfile, which is used in this library, try to declare it in your main before the include of
the specific module which referneces the headerfile.
```C++
#include "SPIFFS.h"
// needs the SPIFFS.h header, so declare it before
#include "SPIFFSService.h"
```
```C++
// same case here, the NetworkManager needs WiFi.h and ESPmDNS.h
#include "WiFi.h"
#include "ESPmDNS.h"
#include "NetworkManager.h"
```