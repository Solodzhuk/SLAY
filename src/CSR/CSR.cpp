#include "CSR.hpp"

void sort(std::vector<int>& arg, std::vector<double> val, int start, int end){
    int top = arg.size();
    for (int n = start; n < end; n++){
        for (int k = 0; n < top - 1; k++){
            if (arg[k] > arg[k+1]){
                int a = arg[k];
                arg[k] = arg[k+1];
                arg[k+1] = a;
                float b = val[k];
                val[k] = val[k+1];
                val[k+1] = b;
            }
        }
        top--;
    }
}

DOK::DOK(std::vector<int> i, std::vector<int> j, std::vector<double> a){
    sort(i, a, 0, i.size());
    std::set<int> i_set(i.begin(), i.end());
    for (int z = 0; z < i_set.size() - 1; z++){  // колбаса)
        sort(j, a, distance(i.begin(), find(i.begin(), i.end(), *next(i_set.begin(), z))), distance(i.begin(), find(i.begin(), i.end(), *next(i_set.begin(), z+1))));
    }

    for (int n = 0; n < i.size(); n++){
        this->matrix.push_back(MatrixElement{i[n], j[n], a[n]});
    }
}

double DOK::access(const int& i, const int& j){
    for (int n = 0; n < matrix.size(); n++){
        if ((matrix[n].i == i) && (matrix[n].j == j)){
            return matrix[n].v;
        }
    }
    return std::numeric_limits<double>::quiet_NaN();
}

CSR::CSR(DOK data){
    int cur_i = 0;
    int count = 0;
    for (int n = 0; n < data.matrix.size(); n++){
        values.push_back(data.matrix[n].v);
        cols.push_back(data.matrix[n].i);
        if (cur_i != data.matrix[n].i){
            rows.push_back(count);
        }
        count++;
    }
}

double CSR::access(const int& i, const int& j){
    for (int n = rows[j]; n < rows[j+1]; n++){
        if (cols[n] == i){
            return values[n];
        }
    }
}