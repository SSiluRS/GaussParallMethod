#include "Matrix.h"

bool Matrix::is_equal(double x, double y) {
    return std::fabs(x - y) < 1e-6;
}

Matrix::Matrix(int n, int m) : n(n), m(m), m_data(n* m) {}

Matrix::Matrix(int n) : n(n), m(1), m_data(n) {}

Matrix::Matrix(const Matrix& other) : n(other.n), m(other.m), m_data(other.m_data) {}

int Matrix::rows() const {
    return n;
}

int Matrix::cols() const {
    return m;
}

void Matrix::resize(int new_n, int new_m) {
    m_data.resize(new_m*new_n);
    m = new_m;
    n = new_n;
}

void Matrix::resize(int new_size) {
    m_data.resize(new_size);
}

double* Matrix::get_data() {
    return m_data.data();
}

void Matrix::set_row(int row_i, double* row)
{
#pragma omp parallel for
    for (int i = 0; i < m; i++)
    {
        (*this)(row_i, i) = row[i];
    }
}

void Matrix::create_from_another_matrix(double* data, int n, int m) {
    this->n = n;
    this->m = m;
    //std::cout << &m_data<<"\n";
    m_data.clear();
    //std::cout << &m_data << "\n\n";

    for (int i = 0; i < n*m; i++)
    {
        m_data.push_back(data[i]);
        //m_data[i] = data[i];
    }
}

bool Matrix::create_random_matrix(int n, int m)
{
    this->n = n;
    this->m = m;
    m_data.clear();
    m_data.resize(n * m);
    //int i = 0;

    for (int i = 0; i < n * m; i++)
    {
        double value = rand();
        m_data[i] = value;

    }


    return true;
}


double& Matrix::operator()(int row, int col) {
    return m_data[row * m + col];
}

const double& Matrix::operator()(int row, int col) const {
    return m_data[row * m + col];
}

void Matrix::swap_rows(int i, int j) {
#pragma omp parallel for
    for (int k = 0; k < m; k++) {
        std::swap((*this)(i, k), (*this)(j, k));
    }
}

void Matrix::print() const {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << std::setw(10)<< (*this)(i, j);
        }
        std::cout << std::endl;
    }
}

void Matrix::printRow(int i) const
{
    for (int j = 0; j < m; j++) {
        std::cout << (*this)(i, j) << " ";
    }
    std::cout << std::endl;
}

bool Matrix::read_from_file(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Error: could not open file \"" << filename << "\" for reading." << std::endl;
        return false;
    }

    std::string line;
    if (!std::getline(in, line)) {
        std::cerr << "Error: file \"" << filename << "\" is empty." << std::endl;
        return false;
    }

    std::stringstream ss(line);
    if (!(ss >> n >> m)) {
        std::cerr << "Error: invalid matrix size in file \"" << filename << "\"." << std::endl;
        return false;
    }
    m_data.clear();
    m_data.resize(n * m);

    int i = 0;
    while (std::getline(in, line)) {
        std::stringstream ss(line);
        for (int j = 0; j < m; j++) {
            if (!(ss >> (*this)(i, j))) {
                std::cerr << "Error: invalid matrix element in file \"" << filename << "\"." << std::endl;
                return false;
            }
        }
        i++;
    }
    in.close();
    return true;
}

bool Matrix::write_to_file(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) {
        std::cout << "File error!" << std::endl;
        return false;
    }

    out << n << " " << m << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            out << (*this)(i, j) << " ";
        }
        out << std::endl;
    }

    return true;
}
