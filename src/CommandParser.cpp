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
        char const * msg = nullptr;
        if(pEnd == mCurrent)
            msg = ("Error during parsing: not found");
        else
            msg = ("Error during parsing: overflow");

        throw Exception(msg);
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
        throw Exception{"separator not found"};
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

