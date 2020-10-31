#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "BigInt.h"

int main() {
    std::string testInputFolder = "tests";
    std::string testOutputFolder = "test_output";
    std::ifstream testFiles("tests/test_list");
    std::string filename;

    while (testFiles >> filename) {
        std::ifstream fileInput(testInputFolder + "/" + filename);
        std::ofstream tmpFileOutput(testOutputFolder + "/" + filename);

                          /// GETING ANSWER ///

        int k;
        fileInput >> k;
        while (k--) {
            int cmd;
            fileInput >> cmd;
            if (cmd == 1) {
                BigInt a, b;
                long long x, y;
                fileInput >> x >> y;
                a = x;
                b = y;
                tmpFileOutput << a << " " << b << "\n";
            } else if (cmd == 2) {
                long long x, y;
                fileInput >> x >> y;
                BigInt a(x), b(y);
                tmpFileOutput << a << " " << b << "\n";
            } else if (cmd == 3) {
                std::string x, y;
                fileInput >> x >> y;
                BigInt a(x), b(y);
                tmpFileOutput << a << " " << b << "\n";
            } else if (cmd == 4) {
                std::string x, y;
                fileInput >> x >> y;
                BigInt a(x), b(y);
                tmpFileOutput << (a < b) << " " << (a > b)
                        << " " << (a == b) << " " << (a != b) << " "
                        << (a >= b) << " " << (a <= b) << "\n";
            } else if (cmd == 5) {
                std::string x;
                long long y;
                fileInput >> x >> y;
                BigInt a(x);
                tmpFileOutput << (a > y) << " " << (a < y) << " " << (a >= y)
                        << " " << (a <= y) << " " << (a == y) << " "
                        << (a != y) << "\n";
            } else if (cmd == 6) {
                std::string x, y;
                fileInput >> x >> y;
                BigInt a(x), b(y);
                tmpFileOutput << a + b << "\n" << a - b << "\n" << a * b << "\n";
            } else if (cmd == 7) {
                std::string x, y;
                fileInput >> x >> y;
                BigInt a(x), b(y);
                a += b;
                tmpFileOutput << a << "\n" << b << "\n";
            } else if (cmd == 8) {
                std::string x, y;
                fileInput >> x >> y;
                BigInt a(x), b(y);
                a -= b;
                tmpFileOutput << a << "\n" << b << "\n";
            } else if (cmd == 9) {
                std::string x, y;
                fileInput >> x >> y;
                BigInt a(x), b(y);
                a *= b;
                tmpFileOutput << a << "\n" << b << "\n";
            } else if (cmd == 10) {
                std::string x;
                long long y;
                fileInput >> x >> y;
                BigInt a(x);
                a += y;
                tmpFileOutput << a << "\n" << y << "\n";
            } else if (cmd == 11) {
                std::string x;
                long long y;
                fileInput >> x >> y;
                BigInt a(x);
                a -= y;
                tmpFileOutput << a << "\n" << y << "\n";
            } else if (cmd == 12) {
                std::string x;
                long long y;
                fileInput >> x >> y;
                BigInt a(x);
                a *= y;
                tmpFileOutput << a << "\n" << y << "\n";
            }
            tmpFileOutput << "\n";
        }
        tmpFileOutput.close();
        fileInput.close();

                            /// TESTING ///
/*
        std::ifstream tmpFileInput(testOutputFolder + "/tmp");
        std::ifstream ansFileInput(testOutputFolder + "/" + filename);

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

        tmpFileInput.close();
        ansFileInput.close();

*/
    }

    testFiles.close();
    return 0;
}
