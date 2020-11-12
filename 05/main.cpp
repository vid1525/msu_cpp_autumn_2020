#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "Serializer.h"

struct Data1 {
    uint64_t a;
    bool b;
    uint64_t c;

    template <typename Serializer>
    Error serialize(Serializer &serializer)
    {
        return serializer(a, b, c);
    }
};

struct Data2 {
    bool a;
    bool b;
    bool c;
    bool d;
    template <typename Serializer>
    Error serialize(Serializer &serializer) {
        return serializer(a, b, c, d);
    }
};

struct Data3 {
    uint64_t a;
    uint64_t b;
    uint64_t c;
    uint64_t d;
    template <typename Serializer>
    Error serialize(Serializer &serializer) {
        return serializer(a, b, c, d);
    }
};

struct Data4 {
    bool a;
    uint64_t b;
    template <typename Serializer>
    Error serialize(Serializer &serializer) {
        return serializer(a, b);
    }
};


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
        fileInput >> n;
        for (int i = 0; i < n; ++i) {
            int t;
            fileInput >> t;
            if (t == 1) {
                Deserializer des(fileInput);
                Data1 val;
                if (des.load(val) != Error::NoError) {
                    tmpFileOutput << "-1\n";
                    continue;
                }
                tmpFileOutput << std::boolalpha << val.a << " " << val.b << " " << val.c << "\n";

                Serializer ser(tmpFileOutput);
                ser.save(val);
                tmpFileOutput << "\n";
            } else if (t == 2) {
                Deserializer des(fileInput);
                Data2 val;
                if (des.load(val) != Error::NoError) {
                    tmpFileOutput << "-1\n";
                    continue;
                }
                tmpFileOutput << std::boolalpha << val.a << " "
                        << val.b << " " << val.c << " " << val.d << "\n";

                Serializer ser(tmpFileOutput);
                ser.save(val);
                tmpFileOutput << "\n";
            } else if (t == 3) {
                Deserializer des(fileInput);
                Data3 val;
                if (des.load(val) != Error::NoError) {
                    tmpFileOutput << "-1\n";
                    continue;
                }
                tmpFileOutput << std::boolalpha << val.a << " "
                        << val.b << " " << val.c << " " << val.d << "\n";

                Serializer ser(tmpFileOutput);
                ser.save(val);
                tmpFileOutput << "\n";
            } else if (t == 4) {
                Deserializer des(fileInput);
                Data4 val;
                if (des.load(val) != Error::NoError) {
                    tmpFileOutput << "-1\n";
                    continue;
                }
                tmpFileOutput << std::boolalpha << val.a << " " << val.b << "\n";

                Serializer ser(tmpFileOutput);
                ser.save(val);
                tmpFileOutput << "\n";
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
