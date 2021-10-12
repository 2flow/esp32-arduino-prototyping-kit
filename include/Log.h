//
// Created by f.wimmer on 12.10.2021.
// TODO("Move to global prototyping lib")

#ifndef ESP32PROTOTYPINGLIBLOCAL_LOG_H
#define ESP32PROTOTYPINGLIBLOCAL_LOG_H


class Log {
public:
    static void error(char const* msg, ...);
    static void info(char const* msg, ...);
    static void debug(char const* msg, ...);

    void setAsGlobal();

    virtual ~Log() = default;

protected:
    enum class LogLevel{
        NoLog = 0,
        // only show error output
        Error = 1,
        // dont show debug output
        Info = 2,
        // show all output inclusive
        Debug = 3,
    };

    virtual void onError(char const* msg, ...) = 0;
    virtual void onInfo(char const* msg, ...) = 0;
    virtual void onDebug(char const* msg, ...) = 0;

    virtual LogLevel onGetLogLevel() = 0;



private:
    static Log* sInstance;
};


#endif //ESP32PROTOTYPINGLIBLOCAL_LOG_H
