#include "Iter.hpp"


std::vector<double> simple_iter(CSR& A, std::vector<double>& b, const double& accuracy, const double& T, unsigned int iter_max){
    std::vector<double> x(b.size(), 0.0);
    unsigned int iter = 0;
    while ((abs_val(A*x - b) > accuracy) && (iter < iter_max)){
        x = x - (A*x - b)*T;
        iter++;
    }
    if (iter == iter_max){
        std::cout << "Exceeded max iteration number\n";
    }
    return x;
}


std::vector<double> Yakoby_iter(CSR& A, std::vector<double>& b, const double& accuracy, const double& T, unsigned int iter_max){
    std::vector<double> x(b.size(), 0.0);
    std::vector<double> temp(b.size(), 0.0);
    std::vector<double> D{0, 0, 0};
    unsigned int iter = 0;
    while ((abs_val(A*x - b) > accuracy) && (iter < iter_max)){
        for (int i = 0; i < A.rows.size()-1; i++){
            double sum = 0;
            for(int j = A.rows[i]; j < A.rows[i+1]; j++){
                if (i+1 != A.cols[j]){
                    sum += A.values[j]*x[A.cols[j]-1];
                }else{
                    D[i] = (A.values[j]);
                }
            }
            temp[i] = sum; // temp = (L+U)*x
        }
        temp = b - temp;
        for (int z = 0; z < 3; z++)
        for (int n = 0; n < b.size(); n++){
            x[n] = temp[n]/D[n];
        }
        iter++;
    }
    if (iter == iter_max){
        std::cout << "Exceeded max iteration number\n";
    }
    return x;
}

std::vector<double> GaussSeidel_iter(CSR& A, std::vector<double>& b, const double& accuracy, const double& T, unsigned int iter_max){
    
    std::vector<double> x(b.size(), 0.0);
    std::vector<double> D{0, 0, 0};
    unsigned int iter = 0;

    double sum1;
    double sum2;
    while ((abs_val(A*x - b) > accuracy) && (iter < iter_max)){
        for (int i = 1; i < b.size()+1; i++){
            sum1 = 0;
            sum2 = 0;
            for (int j = i+1; j < b.size()+1; j++)
                sum1 += A(i, j)*x[j-1];
            
            for (int j = 1; j < i; j++)
                sum2 += A(i, j)*x[j-1];
            
            x[i-1] = (b[i-1] - sum1 - sum2)/A(i, i);
        }
    }
    if (iter == iter_max){
        std::cout << "Exceeded max iteration number\n";
    }
    return x;
}