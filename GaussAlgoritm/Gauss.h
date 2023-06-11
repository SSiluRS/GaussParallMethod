#pragma once

#include "Matrix.h"


class Gauss {
protected:
	Matrix* a;
	Matrix* b;
	Matrix* x;
	int n;
	float eps;
	CODE code;
public:
	Gauss();
	virtual CODE run() = 0;
	std::string getCODE();
	CODE createAMatrix(int n, float** source);
	CODE createAMatrix(int n, std::string filename);
	CODE createBMatrix(int n, float** source);
	CODE createBMatrix(int n, std::string filename);
	CODE createXMatrix(int n, float** source);
	CODE getA(Matrix*& a);
	CODE getB(Matrix*& b);
	CODE getX(Matrix*& x);
	bool test1();
	bool test2();

};