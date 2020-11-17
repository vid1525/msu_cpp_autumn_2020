#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include "Format.h"

bool CorrectFormat() {
    return format("abcd = {0} {1} {0} {2} {2}", 156, -78, "aaa") == "abcd = 156 -78 156 aaa aaa";
}

bool InvalidIndex1() {
    try {
        format("{156}", 87, "265", 984861);
    } catch (const FormatException &e) {
        std::cerr << e.what() << "\n";
        return true;
    }
    return false;
}

bool InvalidIndex2() {
    try {
        format("{-2}", 87, "265", 984861);
    } catch (const FormatException &e) {
        std::cerr << e.what() << "\n";
        return true;
    }
    return false;
}

bool InvalidArgument1() {
    try {
        format("{bef  a}", 87, "265", 984861);
    } catch (const FormatException &e) {
        std::cerr << e.what() << "\n";
        return true;
    }
    return false;
}

bool InvalidArgument2() {
    try {
        format("{}", 87, "265", 984861);
    } catch (const FormatException &e) {
        std::cerr << e.what() << "\n";
        return true;
    }
    return false;
}

bool NoClosingBracket() {
    try {
        format("{1} {2} { aernof", 87, "265", 984861);
    } catch (const FormatException &e) {
        std::cerr << e.what() << "\n";
        return true;
    }
    return false;
}

bool DoubledBracket() {
    try {
        format("{1} {2} {{15}}", 87, "265", 984861);
    } catch (const FormatException &e) {
        std::cerr << e.what() << "\n";
        return true;
    }
    return false;
}

bool NoOpeningBracket() {
    try {
        format("1} {2} {{15}}", 87, "265", 984861);
    } catch (const FormatException &e) {
        std::cerr << e.what() << "\n";
        return true;
    }
    return false;
}

int main() {
    std::vector<std::function<bool()>> tests{
        CorrectFormat,
        InvalidIndex1,
        InvalidIndex2,
        InvalidArgument1,
        InvalidArgument2,
        NoClosingBracket,
        DoubledBracket,
        NoOpeningBracket
    };

    for (int i = 0; i < static_cast<int>(tests.size()); ++i) {
        std::cout << i + 1 << " -- " << (tests[i]() ? "ok\n" : "WA\n");
    }

    std::ifstream tmpFileInput("test_error.log");
    std::ifstream ansFileInput("error.log");

    int lineNum = 0;
    while (true) {
        std::string outputStr;
        std::string testStr;
        bool flagOutput = false, flagTest = false;
        if (!(ansFileInput >> outputStr)) {
            flagOutput = true;
        }
        if (!(tmpFileInput >> testStr)) {
            flagTest = true;
        }
        ++lineNum;
        if (flagOutput ^ flagTest) {
            std::cerr << "ERROR: " << "\nOne file is longer then other\n";
            exit(1);
        }
        if (flagTest && flagOutput) {
            break;
        }
        if (outputStr != testStr) {
            std::cerr << "ERROR: " << "\nWrong Answer line: " << lineNum << "\n";
            exit(1);
        }
    }
    std::cout << "error.log -- " << "ok\n";

    tmpFileInput.close();
    ansFileInput.close();
    return 0;
}
