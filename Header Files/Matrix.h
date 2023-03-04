#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <map>

#define CODE unsigned short

static std::map<CODE,std::string> codes{{0,"OK!"},{1,"Matrix is not created!"},{2,"The sizes of the matrices do not match!"},{3,"File error!"},{4,"Invalid string!"},
{5,"Indexing error!"}};



/*
  0 - OK!
  1 - Matrix is not created!
  2 - The sizes of the matrices do not match!
  3 - File error!
  4 - Invalid string!
  5 - Indexing error!
*/

class Matrix {
private:
  int n;
  int m;
  float** array;
  CODE code;

public:
  Matrix();

  int getRowCnt();
  int getColCnt();
  std::string getCODE();
  CODE createMatrix(int n, int m);
  CODE fillMatrix(std::string filename);
  CODE fillMatrix(float** source, int rows, int columns);
  CODE addRow(float* row, int c);
  CODE addRow(std::string row);
  CODE addColumn(float *column, int c);
  CODE addColumn(std::string column);
  CODE getRow(int rowNumber, float* row);
  CODE getColumn(int columnNumber, float* row);
  CODE toString(std::string &str);
  CODE switchRows(int sourceRowNumber, int distRowNumber);
  CODE deleteZeroRows();
  CODE multiplyRow(int rowNumber, float multiplier);
  CODE addMultipliedRowToAnother(int firstRowNumber, int secondRowNumber, float multiplier);
  CODE subtractRow(int firstRowNumber, int secondRowNumber);

  ~Matrix();
};