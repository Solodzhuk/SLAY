#include <CSR/CSR.hpp>

std::vector<double> SteepestGradientDescent(CSR& A, std::vector<double>& b, double accuracy, int iter_max);