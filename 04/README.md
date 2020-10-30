
MAKE OPTIONS:

    make test (make all) - build main file (executable file)
    make clean - clear folder from *.o files
    make help - get README.md file


COMMON INFO:

    main.cpp - file with source code of testing program

    BigInt.cpp - file with source code of class BigInt

    BigInt.h - header for BigInt class

BIGINT INTERFACE:

        BigInt() -- empty constructor (default value is 0)
        BigInt(const int64_t val) -- constructor by integer value
        BigInt(const std::string &str) -- constructor by string
        BigInt(const BigInt &val) -- copy constructor
        BigInt(const BigInt &&val) -- move constructor

            /// Work with BigInt ///
        BigInt operator -() const -- unary minus
        BigInt &operator =(const BigInt &val) -- copy assignment
        BigInt &operator =(const BigInt &&val) -- move assignment
        bool operator >(const BigInt &val) const -- greater
        bool operator >=(const BigInt &val) const -- greater or equal
        bool operator <(const BigInt &val) const -- lower
        bool operator <=(const BigInt &val) const -- lower or equal
        bool operator ==(const BigInt &val) const -- equal
        bool operator !=(const BigInt &val) const -- not equal

        BigInt operator +(const BigInt &val) const -- sum of two BigInt
        BigInt operator -(const BigInt &val) const -- subtraction of two BigInt
        BigInt operator *(const BigInt &val) const -- multiplication of two BigInt
        BigInt &operator *=(const BigInt &val) -- multiply + assignment
        BigInt &operator +=(const BigInt &val) -- sum + assignment
        BigInt &operator -=(const BigInt &val) -- subtraction + assignment


            /// Work with integer ///
        BigInt &operator =(const int64_t val) -- copy assignment
        bool operator >(const int64_t val) const -- greater
        bool operator >=(const int64_t val) const -- greater or equal
        bool operator <(const int64_t val) const -- lower
        bool operator <=(const int64_t val) const -- lower or equal
        bool operator ==(const int64_t val) const -- equal
        bool operator !=(const int64_t val) const -- not equal

        BigInt operator +(const int64_t val) const -- sum of two BigInt
        BigInt operator -(const int64_t val) const -- subtraction of two BigInt
        BigInt operator *(const int64_t val) const -- multiplication of two BigInt
        BigInt &operator *=(const int64_t val) -- multiply + assignment
        BigInt &operator +=(const int64_t val) -- sum + assignment
        BigInt &operator -=(const int64_t val) -- subtraction + assignment


TEST MODE:

    1.
    All tests are contained in test folder.
    To add new test file you should create test file,
    add this file in test folder and add filename to testfile_list.txt.

    During testing will be created new file (tmp file) in folder test_output.
    Result of work of BigInt will be written in tmp and then content from tmp
    will be compared with necessary file in test_output folder.

    ///

    2.
    To test correctness of memory allocation you should launch in terminal:
        valgrind -q ./test (if valgrind is installed already)
    If valgrind is not installed then you should install it.
