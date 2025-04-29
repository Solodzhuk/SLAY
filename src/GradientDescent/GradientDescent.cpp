#include "GradientDescent.hpp"

std::vector<double> SteepestGradientDescent(CSR& A, std::vector<double>& b, double accuracy, int iter_max){
    std::vector<double> x (b.size(), 0.0);
    std::vector<double> r;
    for (int i = 0; i < iter_max; i++){
        r = A*x - b;
        x = x - r*(DOT(r, r)/DOT(r, A*r));
        if (abs_val(r) <= accuracy){
            return x;
        }
    }
    std::cout << "Exceeded max iteration number\n";
    return x;
}


std::vector<double> CG(CSR& A, std::vector<double>& b, std::vector<double>& x0, double accuracy, int iter_max){
    std::vector<double> x = x0;
    std::vector<double> r = A*x0 - b;
    std::vector<double> d = r;
    std::vector<double> r_ip1;  
    for (int iter = 0; iter < iter_max; iter++){
        x = x - d * (DOT(r, r) / DOT(d, A*d));
        r_ip1 = A*x - b;
        d = r_ip1 + d * (DOT(r_ip1, r_ip1) / DOT(r, r));
        r = r_ip1;
        if (abs_val(A*x - b) < accuracy){
            return x;
        }
    }
    std::cout << "Exceeded max iteration nimber\n";
    return x;
}

std::vector<double> BiCG(CSR& A, std::vector<double>& b, std::vector<double>& x0, double accuracy, int iter_max){
    std::vector<double> x = x0;
    std::vector<double> r1 = A*x0 - b;
    std::vector<double> d1 = r1;
    CSR At = A.transpose();
    std::vector<double> r2 = At*x0 - b;
    std::vector<double> d2 = r2;
    std::vector<double> r1_ip1;    
    std::vector<double> r2_ip1;
    double alfa, beta;
    for (int iter = 0; iter < iter_max; iter++){
        alfa = DOT(r2, r1) / DOT(d2, A*d1);
        x = x - d1 * alfa;
        r1_ip1 = r1 -  A*d1 * alfa;
        r2_ip1 = r2 - At*d2 * alfa;
        beta = DOT(r2_ip1, r1_ip1) / DOT(r2, r1);
        d1 = r1_ip1 + d1*beta;
        d2 = r2_ip1 + d2*beta;
        r1 = r1_ip1;
        r2 = r2_ip1;

        if(abs_val(r1) < accuracy){
            return x;
        }
    }
    std::cout << "Exceeded max iteration number\n";
    return x; 
}


std::vector<double> CGS(CSR& A, std::vector<double>& b, std::vector<double>& x0, double accuracy, int iter_max){
    std::vector<double> x = x0;
    std::vector<double> r = A*x - b;
    std::vector<double> r0 = r;
    std::vector<double> r_ip1;   
    std::vector<double> d = r;
    std::vector<double> u = r;
    std::vector<double> q;
    double alfa, beta;
    for (int iter = 0; iter < iter_max; iter++){
        alfa = DOT(r0, r) / DOT(r0, A*d);
        q = u - A*d * alfa;
        x = x - (u + q)*alfa;
        r_ip1 = r - A*(u + q) * alfa;
        beta = DOT(r0, r_ip1) / DOT(r0, r);
        u = r_ip1 + q * beta;
        d = u + (q + d * beta) * beta;
        r = r_ip1;

        if(abs_val(r) < accuracy){
            return x;
        } 
    }
    std::cout << "Exceeded max iteration number\n";
    return x; 
}