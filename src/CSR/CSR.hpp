#pragma once

#include <vector>
#include <bits/stdc++.h>
#include <limits>

struct MatrixElement {
    int i;
    int j;
    double v;
};

void sort(std::vector<int>& i, std::vector<int>& j, std::vector<double>& val, int start, int end);

class DOK {
    public:
        std::vector<MatrixElement> matrix;

        DOK(std::vector<int> i, std::vector<int> j, std::vector<double> a);
        double access(const int& i, const int& j);
};

class CSR {
    public:
        // bool transposed; //  他们不知道我太聪明
        std::vector<double> values;
        std::vector<int> cols;
        std::vector<int> rows;
        CSR(DOK data);
        CSR(std::vector<double> values, std::vector<int> cols, std::vector<int> rows);
        double access(const int& i, const int& j);
        // double _access_t(const int& j, const int& i);
        double operator()(const int& i, const int& j);
        CSR transpose();
};

double abs_val(const std::vector<double>& one);

std::vector<double> operator+ (const std::vector<double>& one, const std::vector<double>& two);

std::vector<double> operator- (const std::vector<double>& one, const std::vector<double>& two);

double DOT(const std::vector<double>& one, const std::vector<double>& two);

std::vector<double> operator* (const std::vector<double>& one, const double& two);

std::vector<double> operator* (CSR& one, const std::vector<double>& two);

// void sort(std::vector<int> base, )