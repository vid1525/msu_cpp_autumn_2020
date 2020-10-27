#include <iostream>
#include "Matrix.h"

int main() {
    Matrix a(5, 7);
    a.printMatrix(std::cout);
    a = a;
    a.printMatrix(std::cout);
    return 0;
}
