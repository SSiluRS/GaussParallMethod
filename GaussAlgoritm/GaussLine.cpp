#include "GaussLine.h"



bool GaussLine::solve(Matrix& A, Matrix& b) {
	
	int n = A.rows();
	int m = A.cols();
	Matrix x(n,1);

	bool show_steps = false;

	for (int i = 0; i < n; i++)
	{
		int maxki = i;
		double max = A(i, i);
		for (int k = i+1; k < n; k++)
		{
			double cur_elem = A(k, i);
			if (std::fabs(cur_elem) > std::fabs(max)) {
				max = cur_elem;
				maxki = k;
			}
		}
		if (i != maxki) {
			A.swap_rows(i, maxki);
			b.swap_rows(i, maxki);
		}
		for (int k = i + 1; k < n; k++)
		{
			double multiplier = A(k, i) / A(i, i);
			for (int j = i; j < m; j++)
			{
				A(k, j) -= multiplier * A(i, j);
				A(k, j) = A(k, j);
				if (Matrix::is_equal(std::fabs(A(k, j)), 0.))
					A(k, j) = 0;
			}
			b(k, 0) -= multiplier * b(i, 0);
			if (Matrix::is_equal(std::fabs(b(k, 0)), 0.))
				b(k, 0) = 0;
		}
	}

	bool isZero = false;
	for (int i = 0; i < n; i++)
	{
		isZero = false;
		for (int j = 0; j < n; j++)
		{
			if (Matrix::is_equal(std::fabs(A(i, j)), 0.)) {
				isZero = true;
			}
			else {
				isZero = false;
				break;
			}
		}
	}
	if (isZero) {
		return false;
	}

	x(n - 1, 0) = b(n-1,0) / A(n-1,m-1);
	for (int i = n - 2; i >= 0; i--)
	{
		double summ = 0;
		for (int j = i + 1; j < n; j++)
		{
			summ += A(i,j) * x(j,0);
		}
		
		x(i,0) = (b(i,0) - summ) / A(i,i);
	}
	this->x = x;

	return true;
}

Matrix GaussLine::getSolution()
{
	return x;
}




//A.print();
