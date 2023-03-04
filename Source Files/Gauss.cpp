#include "../Header Files/Gauss.h"


std::string Gauss::getCODE(){
return codes[code];
}

CODE Gauss::createAMatrix(int n, int m, float** source){
  auto ret = a.createMatrix(n,m);
  ret = a.fillMatrix(source, n, m);
  return code = ret;
}

CODE Gauss::createAMatrix(int n, int m, std::string filename){
  auto ret = a.createMatrix(n,m);
  ret = a.fillMatrix(filename);
  return code = ret;
}

CODE Gauss::createBMatrix(int n, int m, float** source){
  auto ret = b.createMatrix(n,m);
  ret = b.fillMatrix(source, n, m);
  return code = ret;
}

CODE Gauss::createBMatrix(int n, int m, std::string filename){
  auto ret = a.createMatrix(n,m);
  ret = a.fillMatrix(filename);
  return code = ret;
}