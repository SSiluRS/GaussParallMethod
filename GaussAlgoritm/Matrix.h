#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <math.h>
#include <omp.h>
#include <iomanip>

class Matrix {
private:
    int n;
    int m;
    std::vector<double> m_data;
public:
    Matrix(int n = 0, int m = 0);
    Matrix(int n);
    Matrix(const Matrix& other);
    int rows() const;
    int cols() const;
    void resize(int new_n, int new_m);
    void resize(int new_size);
    double* get_data();
    static bool is_equal(double x, double y);
    void create_from_another_matrix(double* data, int n, int m);
    void set_row(int row_i, double* row);
    double& operator()(int row, int col);
    const double& operator()(int row, int col) const;
    void swap_rows(int i, int j);
    void print() const;
    void printRow(int i) const;
    bool create_random_matrix(int n, int m);
    bool read_from_file(const std::string& filename);
    bool write_to_file(const std::string& filename) const;
    void clearAll() {m_data.clear();}
    ~Matrix() {clearAll();}
};