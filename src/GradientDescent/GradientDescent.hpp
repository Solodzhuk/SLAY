#include <CSR/CSR.hpp>

std::vector<double> SteepestGradientDescent(CSR& A, std::vector<double>& b, double accuracy, int iter_max);

std::vector<double> CG(CSR& A, std::vector<double>& b, std::vector<double>& x0, double accuracy, int iter_max);

std::vector<double> BiCG(CSR& A, std::vector<double>& b, std::vector<double>& x0, double accuracy, int iter_max);

std::vector<double> CGS(CSR& A, std::vector<double>& b, std::vector<double>& x0, double accuracy, int iter_max);
