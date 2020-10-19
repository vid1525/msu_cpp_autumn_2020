#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdint>
#include <functional>

#ifndef PARSER_H
#define PARSER_H

class TokenParser {
public:

    TokenParser();

    void SetDigitTokenCallback(std::function<void(uint64_t, void *)> f);
    void SetStringTokenCallback(std::function<void(std::string, void *)> f);
    void SetStartCallback(std::function<void(void *)> f);
    void SetFinishCallback(std::function<void(void *)> f);

    void Parse(const std::string str, void *userClass);

    std::function<void (void *)> StartCallback;
    std::function<void (void *)> FinishCallback;

private:
    std::function<void (uint64_t, void *)> DigitCallback;
    std::function<void (std::string, void *)> StringCallback;
};

#endif
