//
// Created by f.wimmer on 12.10.2021.
//

#ifndef ESP32PROROTYPINGLIB_COMMANDPARSER_H
#define ESP32PROROTYPINGLIB_COMMANDPARSER_H


class CommandParser {
public:
    CommandParser(char* buffer, int length);

    int getNextInt();
    bool skipSeparator();

    bool getError() const;

private:
    char* mpBuffer;
    char* mpEnd;
    char* mCurrent;
    char* mNextSeparator;
    char mSeparatorChar = ',';
    char mEscapeChar = '\\';

    bool mIsError = false;
};


#endif //ESP32PROROTYPINGLIB_COMMANDPARSER_H
