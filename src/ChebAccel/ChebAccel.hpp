#include <Iter/Iter.hpp>

// double get_max_lambda(CSR& A, const double& accuracy, unsigned int iter_max);

std::vector<double> ChebAccel_simple_iter(CSR& A, std::vector<double>& b, std::vector<double>& x0, const double& accuracy, unsigned int iter_max);

std::vector<int> get_perestanovki(int r);

std::vector<double> ChebAccel(CSR& A, std::vector<double>& b, std::vector<double>& x0, const double& accuracy, unsigned int iter_max, std::function<std::vector<double>(CSR&, std::vector<double>&, std::vector<double>&)> meth_iter);