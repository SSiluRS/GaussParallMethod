#include "../Header Files/GaussLine.h"

Matrix GaussLine::run(){
  Matrix a;
  a.createMatrix(3,3);
  a.fillMatrix("../data/data.bin");
  return a;
}