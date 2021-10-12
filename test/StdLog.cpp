//
// Created by f.wimmer on 12.10.2021.
//
#include <cstdarg>
#include "stdio.h"
#include "StdLog.h"

void StdLog::onError(char const *msg, ...) {
    va_list args;
            va_start(args, msg);
    printf(msg, args);
            va_end(args);
}

void StdLog::onInfo(char const *msg, ...) {
    va_list args;
            va_start(args, msg);
    printf(msg, args);
            va_end(args);
}

void StdLog::onDebug(char const *msg, ...) {
    va_list args;
            va_start(args, msg);
    printf(msg, args);
            va_end(args);
}

Log::LogLevel StdLog::onGetLogLevel() {
    return LogLevel::Debug;
}

