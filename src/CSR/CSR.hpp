#pragma once

#include <unordered_map>
#include <vector>
#include <set>
#include <bits/stdc++.h>
#include <limits>

struct MatrixElement {
    int i;
    int j;
    double v;
};

void sort(std::vector<int>& arg, std::vector<double> val, int start, int end);

class DOK {
    public:
        std::vector<MatrixElement> matrix;

        DOK(std::vector<int> i, std::vector<int> j, std::vector<double> a);
        double access(const int& i, const int& j);
};

class CSR {
    private:
        std::vector<double> values;
        std::vector<int> cols;
        std::vector<int> rows;
    public:
        CSR(DOK data);
        double access(const int& i, const int& j);
};