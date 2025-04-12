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


std::vector<double> Yakoby_iter(CSR& A, std::vector<double>& b, const double& accuracy, unsigned int iter_max){
    std::vector<double> x(b.size(), 0.0);
    std::vector<double> temp(b.size(), 0.0);

    
    std::vector<double> D(b.size(), 0.0);
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
        for (int n = 0; n < b.size(); n++){
            x[n] = temp[n]/D[n];
        }
        // for (int z = 0; z < x.size(); z++){
        //     std::cout << x[z] << " ";
        // }
        // std::cout << abs_val(A*x - b) << std::endl;
        iter++;
    }
    if (iter == iter_max){
        std::cout << "Exceeded max iteration number\n";
    }
    // std::cout << "------" << iter << "------" << std::endl;
    return x;
}

std::vector<double> GaussSeidel_iter(CSR& A, std::vector<double>& b, const double& accuracy, unsigned int iter_max){
    
    std::vector<double> x(b.size(), 0.0);
    // std::vector<double> D{0, 0, 0};
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


std::vector<double> Symm_GaussSeidel_iter(CSR& A, std::vector<double>& b, const double& accuracy, unsigned int iter_max){
    int n = b.size();
    std::vector<double> x (n, 0.0);
    std::vector<double> U (n, 0.0);
    std::vector<double> L (n, 0.0);
    double sum;

    for (int z = 0; z < iter_max; z++){
        for(int i = 0; i < n; i++){
            sum = 0;
            for (int j = i+1; j < n; j++){
                sum += x[j]*A(i+1, j+1);   
            }
            U[i] = b[i] - sum;
        }
        x[0] = U[0]/A(1, 1);
        for (int i = 1; i < n; i++){
            sum = U[i];
            for(int j = 0; j < i; j++){
                sum -= x[j]*A(i+1, j+1);
            }
            x[i] = sum/A(i, i);
        }
        //---------------------------------- 第二个
        for(int i = 0; i < n; i++){
            sum = 0;
            for (int j = 0; j < i; j++){
                sum += x[j]*A(i+1, j+1);   
            }
            L[i] = b[i] - sum;
        }
        x[n-1] = L[n-1]/A(n, n);
        for (int i = n-2; i >= 0; i--){
            sum = L[i];
            for (int j = i+1; j < n; j++){
                sum -= x[j]*A(i+1, j+1);
            }
            x[i] = sum/A(i+1, i+1);
        }
        if (abs_val(A*x - b) < accuracy){
            return x;
        }
    }
    std::cout << "Exceeded max iteration number\n";
    return x;
}


double get_max_lambda(CSR& A, const double& accuracy, unsigned int iter_max){
    std::vector<double> r(A.rows.size()-1, 1.0/(A.rows.size()-1));
    double lambda = 0;
    double prev_lambda = 1000;
    unsigned int iter = 0;
    while((abs(lambda - prev_lambda) > accuracy) && (iter < iter_max)){
        prev_lambda = lambda;
        r = A*r;
        r = r*(1/abs_val(r));
        lambda = DOT(r, A*r)/(DOT(r, r));
        iter++;
    }
    return lambda;
}

std::vector<double> SOR(CSR& A, std::vector<double>& b, const double& accuracy, unsigned int iter_max){
    int n = b.size();
    std::vector<double> x (n, 0.0);

    double sum1;
    double sum2;

    std::vector<int> i_vec;
    std::vector<int> j_vec;
    std::vector<double> val_vec;
    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            i_vec.push_back(i);
            j_vec.push_back(j);
            if(i != j){
                val_vec.push_back(A(i+1, j+1)/A(i+1, i+1));
            }else{
                val_vec.push_back(1 - A(i+1, j+1)/A(i+1, i+1));
            }
        }
    }
    DOK tmp(i_vec, j_vec, val_vec);
    CSR Dm1A(tmp);
    double m = get_max_lambda(Dm1A, accuracy, iter_max);
    double omega = 1 + pow((m/(1 + sqrt(1 - m*m))), 2);

    for (int z = 0; z < iter_max; z++){
        for(int i = 0; i < n; i++){
            sum1 = 0;
            sum2 = 0;

            for (int j = i+1; j < n; j++){
                sum1 += x[j]*A(i+1, j+1);
            }
            for (int j = 0; j < i; j++){
                sum2 += x[j]*A(i+1, j+1);
            }
            x[i] = (1-omega)*x[i] + omega*(b[i] - sum1 - sum2)/A(i+1, i+1);
        }

        if(abs_val(A*x - b) < accuracy){
            return x;
        }
    }
    std::cout << "Exceeded max iteration number\n";
    return x;
}