#include <Iter/Iter.hpp>

double get_max_lambda(CSR& A, const double& accuracy, unsigned int iter_max);

std::vector<double> ChebAccel_simple_iter(CSR& A, std::vector<double>& b, const double& accuracy, const double& T, unsigned int iter_max);

std::vector<int> get_perestanovki(int r);
