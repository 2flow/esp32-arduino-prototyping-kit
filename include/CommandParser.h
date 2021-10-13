//
// Created by f.wimmer on 12.10.2021.
//

#ifndef ESP32PROROTYPINGLIB_COMMANDPARSER_H
#define ESP32PROROTYPINGLIB_COMMANDPARSER_H


class CommandParser {
public:
    struct ParserParameter {
        char const * const & mpBuffer;
        char const* & mpEnd;
        char const* & mCurrent;
        char const* & mNextSeparator;
        char & mSeparatorChar;
        char & mEscapeChar;
        bool & isError;
    };

    CommandParser(char const * buffer, int length);

    int getNextInt();
    bool skipSeparator();

    bool moveCursor(int by);

    // region Getter Setter
    void setEscapeChar(char escChar);
    char getEscapeChar() const;

    void setSeparator(char separator);
    char getSeparator() const;
    // endregion

    bool getError() const;

    template <typename TResult>
    TResult runExtension(TResult(*extension)(ParserParameter&));

private:
    char const * const mpBuffer;
    char const* mpEnd;
    char const* mCurrent;
    char const* mNextSeparator;
    char mSeparatorChar = ',';
    char mEscapeChar = '\\';

    bool mIsError = false;
};

template<typename TResult>
TResult CommandParser::runExtension(TResult (*extension)(ParserParameter&)) {
    ParserParameter parameter{
            mpBuffer,
            mpEnd,
            mCurrent,
            mNextSeparator,
            mSeparatorChar,
            mEscapeChar,
            mIsError
    };

    return extension(parameter);
}

#endif //ESP32PROROTYPINGLIB_COMMANDPARSER_H
