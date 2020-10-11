
Make options:
    make test (make all) - build test file (executable file)
    make clean - clear folder from *.o files and test
    make help - get README.md file

Test mode:
    1.
    All tests are contained in test folder. To add new test file you should
    create test file, add this file in test folder and add filename to testfile_list.txt.
    (Filename should not contain space characters)

    All output files for test are contained in test_output folder. To add new test file you
    should create test file, add this file in test folder and add filename to testfile_list.txt.
    (Filename should not contain space characters)

    Test input and output files should have same names.

    test file contains:
        1) N - number of operations with Allocator
        2) next N lines contain t (0 - makeAllocator, 1 - alloc, 2 - reset)
            if t == 0 or t == 1 then this line contain t and m
                    (type of operation and lenght of alloc memory)
            if t == 2: then this line contain only t
                    (type of operation)
    test output file:
        test output file contain N lines (is the same number as in test case) with 3 numbers
        offset, allocSize
        (offset - current offset in allocated memory, allocSize - current allocated memory)

    2.
    To test correctness of memory allocation you should launch in terminal:
        valgrind ./test (if valgrind is installed already)
    If valgrind is not installed then you should install it.
