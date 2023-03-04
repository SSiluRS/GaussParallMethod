#pragma once

#include "Matrix.h"


class Gauss{
private:
  int a_n, a_m, b_n, b_m;
  CODE code;
public:
  Matrix a;
  Matrix b;
  virtual Matrix run() = 0;  
  std::string getCODE();
  CODE createAMatrix(int n, int m, float** source);
  CODE createAMatrix(int n, int m, std::string filename);
  CODE createBMatrix(int n, int m, float** source);
  CODE createBMatrix(int n, int m, std::string filename);
};