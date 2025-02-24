#pragma once
#include <vector>

class Matrix{
    private:
    int col_size;
    int row_size;
    std::vector<double> mat;
    public:
    Matrix();
    Matrix(int row_size, int col_size);
    std::pair<int, int> shape();
    double operator()(int i, int j);
    void operator()(int i, int j, double val);
    std::vector<double> operator*(const std::vector<double>& one);
    Matrix operator*(Matrix& one); 

    Matrix transpose();
    std::vector<double> get_col(int j);
    std::vector<double> get_col(int j, int i_start, int i_end);
};

Matrix make_eye(int size);