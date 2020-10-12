
Make options:
    make test (make all) - build test file (executable file)
    make clean - clear folder from *.o files and test
    make help - get README.md file


Common info:
    test.cpp - file with source code of tester for Allocator
        For correct testing of Allocator class test.cpp uses the
        inherited from Allocator class DebugAllocator (with public methods
        getOffset() and getAllocSize). It was necessary to make offset and
        allocSize private for common user.

    Allocator.cpp - file with source code of Allocator and DebugAllocator


Test mode:
    1.
    All tests are contained in test folder.
    To add new test file you should create test file,
    add this file in test folder and add filename to testfile_list.txt.
    (Filename should not contain space characters)


    All output files for test are contained in test_output folder.
    To add new test file you should create test file,
    add this file in test folder and add filename to testfile_list.txt.
    (Filename should not contain space characters)


    TEST INPUT- AND OUTPUT- FILES SHOULD HAVE SAME NAMES.


    Test input file contains:
        1) N - number of operations with Allocator
        2) next N lines contain t (0 - makeAllocator, 1 - alloc, 2 - reset)
            if t == 0 or t == 1 then this line contain t and m
                    (type of operation and lenght of alloc memory)
            if t == 2: then this line contain only t
                    (type of operation)

    Test output file contains:
        test output file contain N lines
        (is the same number as in test case) with 2 or 3 numbers:
          nullptr_flag(is in line if in test was called function alloc()),
          offset and allocSize

        (offset - current offset in allocated memory,
         allocSize - current allocated memory,
         nullptr_flag == 1 if alloc returned not nullptr,
         otherwise nullptr_flag == 0)


    2.
    To test correctness of memory allocation you should launch in terminal:
        valgrind -q ./test (if valgrind is installed already)
    If valgrind is not installed then you should install it.
