//
// Created by f.wimmer on 12.10.2021.
//

#include "Log.h"
#include <cstdarg>

Log* Log::sInstance = nullptr;

void Log::error(char const *msg, ...) {
    if((sInstance != nullptr) && (sInstance->onGetLogLevel() >= LogLevel::Error)){
        va_list args;
        va_start(args, msg);
        sInstance->onError(msg, args);
        va_end(args);
    }
}

void Log::info(char const *msg, ...) {
    if((sInstance != nullptr) && (sInstance->onGetLogLevel() >= LogLevel::Info)){
        va_list args;
                va_start(args, msg);
        sInstance->onInfo(msg, args);
                va_end(args);
    }
}

void Log::debug(char const *msg, ...) {
    if((sInstance != nullptr) && (sInstance->onGetLogLevel() >= LogLevel::Debug)){
        va_list args;
                va_start(args, msg);
        sInstance->onDebug(msg, args);
                va_end(args);
    }
}

void Log::setAsGlobal() {
    sInstance = this;
}


