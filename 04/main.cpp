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
        std::ofstream tmpFileOutput(testOutputFolder + "/tmp");

                          /// GETING ANSWER ///

        int k;
        fileInput >> k;
        while (k--) {
            int cmd;
            fileInput >> cmd;
            if (cmd == 1) {

            } else if (cmd == 2) {

            } else if (cmd == 3) {

            }
        }
        tmpFileOutput.close();
        fileInput.close();

                            /// TESTING ///

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
    }

    testFiles.close();
    return 0;
}
