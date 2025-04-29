#include "CSR.hpp"

void sort(std::vector<int>& i, std::vector<int>& j, std::vector<double>& val, int start, int end){
    int j_size = *std::max_element(j.begin(), j.end());
    int top = val.size();
    for (int n = start; n < end; n++){
        for (int k = start; k < top-1; k++){
            if (i[k]*j_size + j[k] > i[k+1]*j_size + j[k+1]){
                int a = i[k];
                i[k] = i[k+1];
                i[k+1] = a;
                a = j[k];
                j[k] = j[k+1];
                j[k+1] = a;
                double b = val[k];
                val[k] = val[k+1];
                val[k+1] = b;
            }
        }
        top--;
    }
}

DOK::DOK(std::vector<int> i, std::vector<int> j, std::vector<double> a){
    sort(i, j, a, 0, a.size());
    for (int n = 0; n < a.size(); n++){
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
    // transposed = false;
    int cur_i = 0;
    int count = 0;
    for (int n = 0; n < data.matrix.size(); n++){
        values.push_back(data.matrix[n].v);
        cols.push_back(data.matrix[n].j);
        if (cur_i != data.matrix[n].i){
            for (int z = cur_i; z < data.matrix[n].i; z++){
                rows.push_back(count);
            }
            cur_i = data.matrix[n].i;
        }
        count++;
    }
    rows.push_back(count);
}

double CSR::access(const int& i, const int& j){
    for (int n = rows[i-1]; n < rows[i]; n++){
        if (cols[n] == j){
            return values[n];
        }
    }
    return std::numeric_limits<double>::quiet_NaN();
}


// double CSR::_access_t(const int& j, const int& i){
//     for (int n = rows[i-1]; n < rows[i]; n++){
//         if (cols[n] == j){
//             return values[n];
//         }
//     }
//     return 0;
// }

double abs_val(const std::vector<double>& one){
    double sum = 0;
    for (auto e:one){
        sum += e*e;
    }
    return sqrt(sum);
}

double CSR::operator()(const int& i, const int& j){
    for (int n = rows[i-1]; n < rows[i]; n++){
        if (cols[n] == j){
            return values[n];
        }
    }
    return 0;
}

std::vector<double> operator+ (const std::vector<double>& one, const std::vector<double>& two){
    std::vector<double> n;
    for (int i = 0; i < one.size(); i++){
        n.push_back(one[i] + two[i]);
    }
    return n; // я хз можно тут возвращать ссылку или нет так что просто скопирую не обижайтесь 我不知道
              // просто мб если вернуть n как ссылку функция подсчистит локальные переменные и будет ссылка ни на что
}

std::vector<double> operator- (const std::vector<double>& one, const std::vector<double>& two){
    std::vector<double> n;
    for (int i = 0; i < one.size(); i++){
        n.push_back(one[i] - two[i]);
    }
    return n;
}

std::vector<double> operator* (const std::vector<double>& one, const double& two){
    std::vector<double> n;
    for (int i = 0; i < one.size(); i++){
        n.push_back(one[i] * two);
    }
    return n;
}

std::vector<double> operator* (CSR& one, const std::vector<double>& two){ 
    std::vector<double> n;
    for (int i = 0; i < one.rows.size()-1; i++){
        double m = 0;
        for (int j = one.rows[i]; j < one.rows[i+1]; j++){
            m += one.values[j]*two[one.cols[j]-1];
        }
        n.push_back(m);
    }
    return n;
}


double DOT(const std::vector<double>& one, const std::vector<double>& two){
    double n = 0;
    for (int i = 0; i < one.size(); i++){
        n += one[i]*two[i];
    }
    return n;
}

CSR::CSR(std::vector<double> values, std::vector<int> cols, std::vector<int> rows){
    this->values = values;
    this->cols = cols;
    this->rows = rows;
}

CSR CSR::transpose(){
    int colsize = *std::max_element(this->cols.begin(), this->cols.end());
    int rowsize = this->rows.size() - 1;
    std::vector<int> tmp = this->cols;
    std::vector<int> new_cols;
    int cur = 1;
    for (int z = 0; z < this->rows.size() - 1; z++){
        for (int v = this->rows[z]; v < this->rows[z+1]; v++){
            new_cols.push_back(cur);
        }
        cur++;
    }
    int max_border = tmp.size() - 1;
    std::vector<double> new_values = this->values;
    for (int z = 0; z < tmp.size() - 1; z++){
        for (int v = 0; v < max_border; v++){
            if (tmp[v] > tmp[v+1]){
                std::swap(tmp[v], tmp[v+1]);
                std::swap(new_cols[v], new_cols[v+1]);
                std::swap(new_values[v], new_values[v+1]);
            }
        }
        max_border--;
    }
    cur = 0;
    std::vector<int> new_rows;
    new_rows.push_back(0);
    for (int z = 1; z <= colsize; z++){
        while (z == tmp[cur]){
            cur++;
        }
        new_rows.push_back(cur);
    }
    CSR new_M(new_values, new_cols, new_rows);
    return new_M;
};