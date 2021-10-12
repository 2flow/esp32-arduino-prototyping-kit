//
// Created by f.wimmer on 12.10.2021.
//

#ifndef TUTORIAL_STDLOG_H
#define TUTORIAL_STDLOG_H

#include "Log.h"

class StdLog : public Log {
protected:
    void onError(char const* msg, ...) override;

    void onInfo(char const* msg, ...) override;

    void onDebug(char const* msg, ...) override;

    LogLevel onGetLogLevel() override;
};


#endif //TUTORIAL_STDLOG_H
