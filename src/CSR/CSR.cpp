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
};

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