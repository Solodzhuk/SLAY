#include <CSR/CSR.hpp>
#include <Matrix/Matrix.hpp>
std::vector<double> simple_iter(CSR& A, std::vector<double>& b, const double& accuracy, const double& T, unsigned int iter_max);

std::vector<double> Yakoby_iter(CSR& A, std::vector<double>& b, const double& accuracy, unsigned int iter_max);

std::vector<double> GaussSeidel_iter(CSR& A, std::vector<double>& b, const double& accuracy, unsigned int iter_max);

std::vector<double> Symm_GaussSeidel_iter(CSR& A, std::vector<double>& b, const double& accuracy, unsigned int iter_max);


double get_max_lambda(CSR& A, const double& accuracy, unsigned int iter_max);

std::vector<double> SOR(CSR& A, std::vector<double>& b, const double& accuracy, unsigned int iter_max);