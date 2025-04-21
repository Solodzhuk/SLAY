#include "ChebAccel.hpp"


// double get_max_lambda(CSR& A, const double& accuracy, unsigned int iter_max){
//     std::vector<double> r(A.rows.size()-1, 1.0/(A.rows.size()-1));
//     double lambda = 0;
//     double prev_lambda = 1000;
//     unsigned int iter = 0;
//     while((abs(lambda - prev_lambda) > accuracy) && (iter < iter_max)){
//         prev_lambda = lambda;
//         r = A*r;
//         r = r*(1/abs_val(r));
//         lambda = DOT(r, A*r)/(DOT(r, r));
//         iter++;
//     }
//     return lambda;
// }

std::vector<int> get_perestanovki(int r){
    if (r == 1){
        return std::vector<int> {0, 1};
    }
    std::vector<int> vec_jm1 = get_perestanovki(r-1);
    std::vector<int> vec_j(pow(2, r));
    for (int i = 0; i < pow(2, r-1); i++){
        vec_j[2*i] = vec_jm1[i];
        vec_j[2*i+1] = pow(2, r) - 1 - vec_jm1[i];
    }
    return vec_j;
};

std::vector<double> ChebAccel_simple_iter(CSR& A, std::vector<double>& b, std::vector<double>& x0, const double& accuracy, unsigned int iter_max){
    const int N_ROOTS = 64; // магия с лекции сказали брать 64 我不知道这是什么
    std::vector<double> roots(N_ROOTS);
    double cosPiN = cos(M_PI/N_ROOTS);
    double sinPiN = sin(M_PI/N_ROOTS);
    roots[0] = cos(M_PI/(2 * N_ROOTS));
    for(int i=1; i<N_ROOTS; i++){
        roots[i] = roots[i-1] * cosPiN - sqrt(1-roots[i-1]*roots[i-1]) * sinPiN;
    }
    
    double min_lambda = 0;
    double max_lambda = get_max_lambda(A, accuracy, 1000);
    std::vector<int> peres = get_perestanovki(6);
    std::vector<double> x = x0;

    for (int i = 0; i < N_ROOTS; i++){
        roots[i] = (min_lambda + max_lambda)/2 +(max_lambda-min_lambda)/2 *roots[i];
    }

    for (unsigned int iter = 0; iter < iter_max; iter++){
        for(int i = 0; i < N_ROOTS; i++){
            x = x - (A*x - b) * (1/roots[peres[i]]);
        }
        if (abs_val(A*x - b) < accuracy){
            return x;
        }
    }
    return x;
}


std::vector<double> ChebAccel(CSR& A, std::vector<double>& b, std::vector<double>& x0, const double& accuracy, unsigned int iter_max, 
    std::function<std::vector<double>(CSR&, std::vector<double>&, std::vector<double>&)> meth_iter){
    std::vector<double> y0 = x0;
    std::vector<double> y1 = meth_iter(A, b, x0);
    double r = abs_val(meth_iter(A, b, y1) - y1)/abs_val(y1-x0);
    double w = 2 / (2 - r*r);
    for (int z = 0; z < iter_max; z++){
        std::vector<double> y2 = (meth_iter(A, b, y1) - y0) * w + y0;
        y0 = y1;
        y1 = y2;
        w = 1 / (1 - r*r*w/4);
        if (abs_val(A*y1 - b) < accuracy){
            return y1;
        }
    }
    std::cout << "Exceeded max iteration number\n";
    return y1;
}