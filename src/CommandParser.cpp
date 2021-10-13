//
// Created by f.wimmer on 12.10.2021.
//

#include "cstdlib"
#include "CommandParser.h"
#include "Log.h"

CommandParser::CommandParser(char const * buffer, int length) : mpBuffer(buffer) {
    mpEnd = buffer + length;
    mCurrent = buffer;
}

int CommandParser::getNextInt() {
    char* pEnd = nullptr;
    int value = strtol(mCurrent, &pEnd, 10);

    if((pEnd == mCurrent) || (pEnd > mpEnd)){
        mIsError = true;
        if(pEnd == mCurrent)
            Log::error("Error during parsing: not found");
        else
            Log::error("Error during parsing: overflow");

        return 0;
    }

    mCurrent = pEnd;
    return value;
}

bool CommandParser::getError() const {
    return mIsError;
}

bool CommandParser::skipSeparator() {
    if(*mCurrent == mSeparatorChar)
    {
        mCurrent ++;
    }else{
        mIsError = true;
    }

    return mIsError;
}

bool CommandParser::moveCursor(int by) {
    auto newPos = mCurrent + by;
    if((newPos > mpEnd) || (newPos < mpBuffer)){
        return false;
    }else{
        mCurrent = newPos;
        return true;
    }
}

void CommandParser::setEscapeChar(char escChar) {
    mEscapeChar = escChar;
}

char CommandParser::getEscapeChar() const {
    return mEscapeChar;
}

void CommandParser::setSeparator(char separator) {
    mSeparatorChar = separator;
}

char CommandParser::getSeparator() const {
    return mSeparatorChar;
}

