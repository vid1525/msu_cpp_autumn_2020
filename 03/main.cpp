#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "Matrix.h"

int main() {
    std::string testInputFolder = "tests";
    std::string testOutputFolder = "test_output";
    std::ifstream testFiles("tests/test_list");
    std::string filename;

    while (testFiles >> filename) {
        std::ifstream fileInput(testInputFolder + "/" + filename);
        std::ofstream tmpFileOutput(testOutputFolder + "/tmp");

                          /// GETING ANSWER ///

        int n;
        int rowA, colA;
        int rowB, colB;
        fileInput >> n >> rowA >> colA >> rowB >> colB;
        Matrix A(rowA, colA);
        Matrix B(rowB, colB);
        A.printMatrix(tmpFileOutput);
        B.printMatrix(tmpFileOutput);
        while (n--) {
            std::string command;
            fileInput >> command;
            if (command == "getCol") {
                tmpFileOutput << "A.getColumns() == "
                        << A.getColumns() << "\tB.getColumns() == "
                        << B.getColumns() << "\n";
            } else if (command == "getRow") {
                tmpFileOutput << "A.getRows() == "
                        << A.getRows() << "\tB.getRows() == "
                        << B.getRows() << "\n";
            } else if (command == "*=") {
                int value;
                fileInput >> value;
                A *= value;
                B *= value;
                A.printMatrix(tmpFileOutput);
                B.printMatrix(tmpFileOutput);
            } else if (command == "=") {
                A = B;
                A.printMatrix(tmpFileOutput);
                B.printMatrix(tmpFileOutput);
            } else if (command == "+") {
                (A + B).printMatrix(tmpFileOutput);
            } else if (command == "==") {
                tmpFileOutput << (A == B) << "\n";
            } else if (command == "!=") {
                tmpFileOutput << (A != B) << "\n";
            } else if (command == "[][]") {
                int ind1, ind2;
                fileInput >> ind1 >> ind2;
                tmpFileOutput << "A[" << ind1 << "][" << ind2 << "] == "
                        << A[ind1][ind2] << "\tB[" << ind1 << "][" << ind2
                        << "] == " << B[ind1][ind2] << "\n";
            } else if (command == "set") {
                std::string s;
                int ind1, ind2, value;
                fileInput >> s >> ind1 >> ind2 >> value;
                if (s == "A") {
                    A[ind1][ind2] = value;
                } else {
                    B[ind1][ind2] = value;
                }
            } else if (command == "get") {
                A.printMatrix(tmpFileOutput);
                B.printMatrix(tmpFileOutput);
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
