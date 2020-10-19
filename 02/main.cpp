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
    void printDig(std::ostream &fout) {
        for (auto i : dig) {
            fout << i.first << " " << i.second << "\n";
        }
        fout << "\n";
    }
    void printStr(std::ostream &fout) {
        for (auto i : str) {
            fout << i.first << " " << i.second << "\n";
        }
        fout << "\n";
    }
    void printDiff(std::ostream &fout) {
        fout << "======================================\n";
    }
private:
    std::map<int, int> dig;
    std::map<std::string, int> str;
};

void digToken(int x, void *a) {
    auto b = static_cast<Counter *>(a);
    b->insert(x);
}

void strToken(std::string x, void *a) {
    auto b = static_cast<Counter *>(a);
    b->insert(x);
}

void startCallback(void *a) {
    auto fout = static_cast<std::ostream *>(a);
    *fout << "Input your test strings\n";
}

void finishCallback(void *a) {
    auto fout = static_cast<std::ostream *>(a);
    *fout << "Testing is finished\n";
}

int main() {
    std::string testInputFolder = "tests";
    std::string testOutputFolder = "test_output";
    std::ifstream testFiles("tests/test_list");
    std::string filename;

    while (testFiles >> filename) {
        std::ifstream inputFileStream(testInputFolder + '/' + filename);
        std::ofstream outputTest(testOutputFolder + "/tmp");
        std::string inputStr;
        Counter val;
        TokenParser ps;

        // Result Generating

        ps.SetStartCallback(startCallback);
        ps.SetFinishCallback(finishCallback);
        ps.SetDigitTokenCallback(digToken);
        ps.SetStringTokenCallback(strToken);

        ps.StartCallback(&outputTest);
        while (getline(inputFileStream, inputStr)) {
            ps.Parse(inputStr, &val);
            val.printDig(outputTest);
            val.printStr(outputTest);
            val.printDiff(outputTest);
        }
        ps.FinishCallback(&outputTest);

        inputFileStream.close();
        outputTest.close();

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
