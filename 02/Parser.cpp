#include "Parser.h"

TokenParser::TokenParser() {
    DigitCallback = [](const int, void *) {};
    StringCallback = [](std::string, void *) {};
    StartCallback = [](void *) {};
    FinishCallback = [](void *) {};
}

void TokenParser::SetDigitTokenCallback(std::function<void(int, void *)> f) {
    DigitCallback = f;
}
void TokenParser::SetStringTokenCallback(std::function<void(std::string, void *)> f) {
    StringCallback = f;
}
void TokenParser::SetStartCallback(std::function<void(void *)> f) {
    StartCallback = f;
}
void TokenParser::SetFinishCallback(std::function<void(void *)> f) {
    FinishCallback = f;
}

void TokenParser::Parse(const std::string str, void *userClass) {
    auto it = str.begin();
    do {
        while (it != str.end() && isspace((unsigned char) *it)) {
            ++it;
        }
        if (it == str.end()) {
            break;
        }

        std::stringstream curToken;
        if (!isspace((unsigned char) *it) && !isdigit((unsigned char) *it)) {
            while (it != str.end()
                   && !isspace((unsigned char) *it) && !isdigit((unsigned char) *it)) {
                curToken << *it;
                ++it;
            }
            if (it != str.end() && isdigit((unsigned char) *it)) {
                std::cerr << "Wrong format of parsed string\nSpace expected between tokens\n";
                exit(1);
            }
            StringCallback(curToken.str(), userClass);
        } else {
            while (it != str.end() && isdigit((unsigned char) *it)) {
                curToken << *it;
                ++it;
            }
            if (it != str.end()
                    && !isspace((unsigned char) *it) && !isdigit((unsigned char) *it)) {
                std::cerr << "Wrong format of parsed string\nSpace expected between tokens\n";
                exit(1);
            }
            long long val;
            curToken >> val;
            DigitCallback(val, userClass);
        }
    } while (1);
}
