#include <CSR/CSR.hpp>

std::vector<double> simple_iter(CSR& A, std::vector<double>& b, const double& accuracy, const double& T, unsigned int iter_max);

std::vector<double> Yakoby_iter(CSR& A, std::vector<double>& b, const double& accuracy, const double& T, unsigned int iter_max);

std::vector<double> GaussSeidel_iter(CSR& A, std::vector<double>& b, const double& accuracy, const double& T, unsigned int iter_max);