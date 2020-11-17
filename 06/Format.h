#ifndef FORMAT_H
#define FORMAT_H

#include <string>
#include <sstream>
#include <vector>
#include <exception>

class FormatException : public std::exception {
private:
    std::string errorType;
public:
    FormatException(const std::string &errorMsg) : errorType(errorMsg) {}

    const char *what() const noexcept {
        return errorType.c_str();
    }
};

template <typename CurArg>
void append(std::vector<std::string> &vectorArgs, CurArg currentArg) {
    std::stringstream str;
    str << currentArg;
    vectorArgs.push_back(std::string(str.str()));
}

template <typename CurArg, typename... Args>
void makeVector(std::vector<std::string> &vectorArgs, CurArg &&currentArg) {
    append(vectorArgs, currentArg);
}

template <typename CurArg, typename... Args>
void makeVector(std::vector<std::string> &vectorArgs, CurArg &&currentArg, Args&&... args) {
    append(vectorArgs, currentArg);
    makeVector(vectorArgs, std::forward<Args>(args)...);
}

template <typename... Args>
std::string format(const std::string &formatString, Args&&... args) {
    std::vector<std::string> vectorArgs;
    makeVector(vectorArgs, std::forward<Args>(args)...);

    std::string answer;
    int64_t len = static_cast<int64_t>(formatString.size());
    for (int64_t i = 0; i < len; ) {
        if (formatString[i] == '{') {
            int64_t j = i + 1;
            while (j < len && formatString[j] != '}' && formatString[j] != '{') {
                ++j;
            }

            if (j == len) {
                std::stringstream str;
                str << "No closing bracket in the end\n";
                throw FormatException(std::string(str.str()));
            }

            if (formatString[j] == '{') {
                std::stringstream str;
                str << "Doubled open bracket index: " << j << "\n";
                throw FormatException(std::string(str.str()));
            }

            int64_t index;
            try {
                index = std::stoll(formatString.substr(i + 1, j - i));
            } catch (const std::exception &invalid_value) {
                std::stringstream str;
                str << "Invalid argument\nindex: [" << i << ".." << j << "]\n";
                throw FormatException(std::string(str.str()));
            }

            if (index < 0 || index >= static_cast<int64_t>(vectorArgs.size())) {
                std::stringstream str;
                str << "Index out of range index: " << index << "\n";
                throw FormatException(std::string(str.str()));
            }

            answer += vectorArgs[index];
            i = j + 1;
        } else if (formatString[i] == '}') {
            std::stringstream str;
            str << "Invalid } index: " << i << "\n";
            throw FormatException(std::string(str.str()));
        } else {
            answer += formatString[i];
            ++i;
        }
    }
    return answer;
}

#endif
