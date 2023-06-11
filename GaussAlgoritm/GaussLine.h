#pragma once

#include "Matrix.h"

class GaussLine {
public: 
    bool solve(Matrix& A, Matrix& b);
    Matrix getSolution();
private:
    Matrix x;
};