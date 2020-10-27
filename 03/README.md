
MAKE OPTIONS:

    make test (make all) - build main file (executable file)
    make clean - clear folder from *.o files
    make help - get README.md file


COMMON INFO:

    main.cpp - file with source code of testing program

    Matrix.cpp - file with source code of class Matrix and proxy-class 
                 MatrixRow.

MATRIX INTERFACE:

    Matrix(const int rows, const int columns) -- create matrix with given parameters

    int getColumns() const -- get count of columns in matrix

    int getRows() const -- get count of rows in matrix

    Matrix &operator *=(const int value) -- multiply matrix by value
                    (returns result of operation)

    Matrix &operator =(const Matrix &value) -- assign one matrix to another
                    (return assigned matrix)

    int &operator[][](const int index1, const int index2) const -- returns an
                    link to element in matrix by indices index1 and index2
                    (if one of indices is out of range then will be called
                    exception "out of range")

    Matrix operator +(const Matrix &value) const -- returns sum of two
                    matrices (if matrix sizes are not compatible then will be called
                    exception)

    bool operator ==(const Matrix &value) const -- 1 if A == B and 0 otherwise
                    (if matrix sizes are not compatible then will be called
                    exception)

    bool operator !=(const Matrix &value) const -- 1 if A != B and 0 otherwise
                    (if matrix sizes are not compatible then will be called
                    exception)

    void printMatrix(std::ostream &fout) const -- prints matrix in stream


TEST MODE:

    1.
    All tests are contained in test folder.
    To add new test file you should create test file,
    add this file in test folder and add filename to testfile_list.txt.

    During testing will be created new file (tmp file) in folder test_output.
    Result of work of Matrix will be written in tmp and then content from tmp
    will be compared with necessary file in test_output folder.

    Test program works with two matrices

    TEST INPUT- AND OUTPUT- FILES SHOULD HAVE SAME NAMES.

    Test input file contains:
        1) N - number of tests queries
        2) initial Matrix sizes of A and B (respectively)
        3) next N lines contain test queries which are one of:
            getCol - prints count of Columns in A and B (respectively)
            getRow - prints count of Rows in A and B (respectively)
            *= value - multiplies both matrices by value
            = - assign matrix B to matrix A
            [][] ind1 ind2 - get element A[ind1][ind2] and element B[ind1][ind2]
            + - prints sum of matrix A and B (A and B must be the same by size)
            == - prints 1 if A == B and 0 otherwise
            != - prints 1 if A != B and 0 otherwise
            set [MatrixName] ind1 ind2 value - assign value to matrix element
                              with indices ind1 and ind2 in matrix with MatrixName
            get - prints both of matrices

    For better understanding of test process see more informatino in main.cpp and
    test samples in test and test_output folders.

    2.
    To test correctness of memory allocation you should launch in terminal:
        valgrind -q ./test (if valgrind is installed already)
    If valgrind is not installed then you should install it.
