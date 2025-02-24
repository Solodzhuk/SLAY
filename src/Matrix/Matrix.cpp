#include "Matrix.hpp"

Matrix::Matrix(){
    this->col_size = 0;
    this->row_size = 0;
}
Matrix::Matrix(int row_size, int col_size){
    this->col_size = col_size;
    this->row_size = row_size;
    this->mat.resize(col_size*row_size, 0);
}

std::pair<int, int> Matrix::shape(){
    return std::make_pair(row_size, col_size);
}

double Matrix::operator()(int i, int j){
    return mat[(i-1) * col_size + (j-1)];
};

void Matrix::operator()(int i, int j, double val){
    mat[(i-1) * col_size + (j-1)] = val;
}

std::vector<double> Matrix::operator*(const std::vector<double>& one){
    std::vector<double> res;
    double sum = 0;
    for (int i = 1; i < this->shape().first + 1; i++){
        for (int j = 1; j < this->shape().second + 1; j++){
            sum += (*this)(i, j) * one[j-1];
        }
        res.push_back(sum);
        sum = 0;
    }
    return res;
}

Matrix Matrix::operator*(Matrix& one){
    int n1 = this->shape().first;
    int m1= this->shape().second;
    int n2 = one.shape().first;
    int m2= one.shape().second;
    Matrix res(n1, m2);
    for (int i = 1; i < n1 + 1; i++){
        for (int j = 1; j < m2 + 1; j++){
            double sum = 0;
            for (int z = 1; z < m1 + 1; z++){
                sum += (*this)(i, z) * one(z, j);
            }
            res(i, j, sum);
        }
    }
    return res;
}

Matrix Matrix::transpose(){
    Matrix res(this->col_size, this->row_size);
    for (int i = 1; i < this->col_size + 1; i++){
        for (int j = 1; j < this->row_size + 1; j++){
            res(i, j, (*this)(j, i));
        }
    }
    return res;
}

Matrix make_eye(int size){
    Matrix res(size, size);
    for (int i = 1; i < size + 1; i++){
        res(i, i, 1);
    }
    return res;
}

std::vector<double> Matrix::get_col(int j){
    std::vector<double> res(this->row_size);
    for (int i = 0; i < this->row_size; i++){
        res[i] = (*this)(i+1, j);
    }
    return res;
}

std::vector<double> Matrix::get_col(int j, int i_start, int i_end){
    std::vector<double> res(i_end - i_start);
    for (int i = i_start; i < i_end; i++){
        res[i-1] = (*this)(i, j);
    }
    return res;
}