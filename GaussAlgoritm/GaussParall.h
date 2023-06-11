#pragma once
#include <mpi.h>

#include "Matrix.h"

class GaussParall {
public:
    GaussParall(int rank, int size);
    bool solve(Matrix& A, Matrix& b);
    Matrix getSolution();
private:
    int rank, size;
    Matrix x;
};


