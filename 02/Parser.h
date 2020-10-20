#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdint>
#include <functional>

#ifndef PARSER_H
#define PARSER_H

template <typename UserClass>
class TokenParser {
public:

    TokenParser();

    void SetDigitTokenCallback(const std::function<void(uint64_t, UserClass &)> f);
    void SetStringTokenCallback(const std::function<void(std::string, UserClass &)> f);
    void SetStartCallback(const std::function<void(UserClass &)> f);
    void SetFinishCallback(const std::function<void(UserClass &)> f);

    void Parse(const std::string &str, UserClass &);

    std::function<void (UserClass &)> StartCallback;
    std::function<void (UserClass &)> FinishCallback;

private:
    std::function<void (uint64_t, UserClass &)> DigitCallback;
    std::function<void (std::string, UserClass &)> StringCallback;
};


template <typename UserClass>
TokenParser<UserClass>::TokenParser() {
    DigitCallback = [](uint64_t, UserClass &) {};
    StringCallback = [](std::string, UserClass &) {};
    StartCallback = [](UserClass &) {};
    FinishCallback = [](UserClass &) {};
}

template <typename UserClass>
void TokenParser<UserClass>::SetDigitTokenCallback(const std::function<void(uint64_t, UserClass &)> f) {
    DigitCallback = f;
}

template <typename UserClass>
void TokenParser<UserClass>::SetStringTokenCallback(const std::function<void(std::string, UserClass &)> f) {
    StringCallback = f;
}

template <typename UserClass>
void TokenParser<UserClass>::SetStartCallback(const std::function<void(UserClass &)> f) {
    StartCallback = f;
}

template <typename UserClass>
void TokenParser<UserClass>::SetFinishCallback(const std::function<void(UserClass &)> f) {
    FinishCallback = f;
}

template <typename UserClass>
void TokenParser<UserClass>::Parse(const std::string &str, UserClass &userClass) {
    auto it = str.begin();
    do {
        while (it != str.end() && isspace((unsigned char) *it)) {
            ++it;
        }
        if (it == str.end()) {
            break;
        }
        bool stringFlag = false;
        std::stringstream curStream;
        while (it != str.end() && !isspace((unsigned char) *it)) {
            if (!isdigit((unsigned char) *it)) {
                stringFlag = true;
            }
            curStream << *it;
            ++it;
        }
        if (stringFlag) {
            StringCallback(curStream.str(), userClass);
        } else {
            uint64_t x;
            curStream >> x;
            DigitCallback(x, userClass);
        }
    } while (1);
}


#endif
