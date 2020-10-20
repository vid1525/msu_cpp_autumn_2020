#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <map>
#include "Parser.h"

class Counter { /// counter of frequency of different tokens
public:
    void insert(int x) {
        ++dig[x];
    }
    void insert(std::string s) {
        ++str[s];
    }
    void printDig() {
        for (auto i : dig) {
            fout << i.first << " " << i.second << "\n";
        }
        fout << "\n";
    }
    void printStr() {
        for (auto i : str) {
            fout << i.first << " " << i.second << "\n";
        }
        fout << "\n";
    }
    void printDiff() {
        fout << "======================================\n";
    }
    void print(const std::string s) {
        fout << s;
    }
    void setFout(const std::string filename) {
        fout.open(filename);
    }
    void closeFout() {
        fout.close();
    }

    Counter () {}
    ~Counter () {
        fout.close();
    }
private:
    std::map<int, int> dig;
    std::map<std::string, int> str;
    std::ofstream fout;
};

void digToken(int x, Counter &a) {
    a.insert(x);
}

void strToken(std::string x, Counter &a) {
    a.insert(x);
}

void startCallback(Counter &a) {
    a.print("Input your test strings\n");
}

void finishCallback(Counter &a) {
    a.print("Testing is finished\n");
}

int main() {
    std::string testInputFolder = "tests";
    std::string testOutputFolder = "test_output";
    std::ifstream testFiles("tests/test_list");
    std::string filename;

    while (testFiles >> filename) {
        std::ifstream inputFileStream(testInputFolder + '/' + filename);
        std::string inputStr;
        Counter val;
        TokenParser<Counter> ps;

        // Result Generating

        val.setFout(testOutputFolder + "/tmp");

        ps.SetStartCallback(startCallback);
        ps.SetFinishCallback(finishCallback);
        ps.SetDigitTokenCallback(digToken);
        ps.SetStringTokenCallback(strToken);

        ps.StartCallback(val);
        while (getline(inputFileStream, inputStr)) {
            ps.Parse(inputStr, val);
            val.printDig();
            val.printStr();
            val.printDiff();
        }
        ps.FinishCallback(val);

        val.closeFout();

        inputFileStream.close();

        /// Testing

        std::ifstream outputFileStream(testOutputFolder + '/' + filename);
        std::ifstream tmpFile(testOutputFolder + "/tmp");
        int lineNum = 0;
        while (true) {
            std::string outputStr;
            std::string testStr;
            bool flagOutput = false, flagTest = false;
            if (!(outputFileStream >> outputStr)) {
                flagOutput = true;
            }
            if (!(tmpFile >> testStr)) {
                flagTest = true;
            }
            ++lineNum;
            if (flagOutput ^ flagTest) {
                std::cerr << "ERROR: "
                        << filename << "\nOne file is longer then other\n";
                exit(1);
            }
            if (flagTest && flagOutput) {
                break;
            }
            if (outputStr != testStr) {
                std::cerr << "ERROR: " << filename
                        << "\nWrong Answer line: " << lineNum << "\n";
                exit(1);
            }
        }
        std::cout << filename << " -- " << "ok\n";
        outputFileStream.close();
        tmpFile.close();
    }

    testFiles.close();
    return 0;
}
