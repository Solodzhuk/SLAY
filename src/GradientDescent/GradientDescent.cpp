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