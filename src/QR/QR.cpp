#include "QR.hpp"

std::pair<Matrix, Matrix> Householder_transf(Matrix& A){
    int m = A.shape().first;
    int n = A.shape().second;
    Matrix Q = make_eye(m);

    for(int j = 1; j < n+1; j++){
        std::vector<double> x = A.get_col(j, j, m+1);
        std::vector<double> e1;
        e1.resize(m-j+1, 0);
        e1[0] = 1;  
        std::vector v = x + e1 * std::sqrt(DOT(x, x));
        if (std::sqrt(DOT(v, v)) != 0){
            for (int r = 1; r < m+1; r++){
                std::vector<double> e = Q.transpose().get_col(r, j, m+1);
                e = e + v*((-2)*DOT(v, e)/DOT(v, v));
                for (int i = j; i < m+1; i++){
                    Q(r, i, e[i-j]);
                }
            }
        }
    }
    Matrix Q_T = Q.transpose();
    Matrix R = Q_T*A; // скорее всего у этой штуки плохая асимптотика, как до конца разберусь с этой темой по-другому матрицу R получу
    return std::make_pair(Q, R);
}

std::vector<double> QR_solve (Matrix& Q, Matrix& R, const std::vector<double> f){
    std::vector<double> b = Q.transpose()*f;
    for(int j = R.shape().second; j > 1; j--){
        b[j-1] /= R(j, j);
        for (int i = j - 1; i > 0; i--){
            b[i-1] -= R(i, j) * b[j-1];
        }
    }
    b[0] /= R(1, 1);
    return b;
}