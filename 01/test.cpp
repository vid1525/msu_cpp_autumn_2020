#include <iostream>
#include <fstream>
#include <string>
#include "Allocator.h"

int main() {
    std::string testInputFolder = "tests";
    std::string testOutputFolder = "test_output";
    std::ifstream testFiles("tests/testfile_list.txt");
    std::string filename;

    while (testFiles >> filename) {
        std::ifstream inputFileStream(testInputFolder + '/' + filename);
        std::ifstream outputFileStream(testOutputFolder + '/' + filename);
        DebugAllocator x;

        int n;
        inputFileStream >> n;
        for (int i = 0; i < n; ++i) {
            int type;
            inputFileStream >> type;
            if (type == 0) {
                uint64_t m;
                inputFileStream >> m;
                x.makeAllocator(m);
            } else if (type == 1) {
                uint64_t m;
                inputFileStream >> m;
                x.alloc(m);
            } else if (type == 2) {
                x.reset();
            }
            uint64_t offset, allocSize;
            outputFileStream >> offset >> allocSize;
            if (offset != x.getOffset() || allocSize != x.getAllocSize()) {
                std::cerr << std::endl << "Wrong answer: test " << filename << std::endl;
                std::cerr << "Correct: offset == " << offset <<
                        " | program offset == " << x.getOffset() << std::endl;
                std::cerr << "Correct: allocSize == " << allocSize <<
                        " | program allocSize == " << x.getAllocSize() << std::endl;
                return 1;
            }
        }
        std::cout << filename << " -- ok" << std::endl;

        inputFileStream.close();
        outputFileStream.close();
    }

    testFiles.close();
    return 0;
}
