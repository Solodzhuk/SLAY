#include <CSR/CSR.hpp>
#include <span>

struct CMM {
    int n_rows, n_cols;
    std::vector<double> mat;
    CMM();
    CMM(int r, int c);
    std::pair<int, int> shape();
    double operator()(int i, int j);
    void operator()(int i, int j, double val);
    std::vector<double> operator*(const std::vector<double>& one);
    CMM operator*(CMM& one); 

    CMM transpose();
    std::span<double> get_col(int j); // вот че ему не нравится то
    std::span<double> get_col(int j, int i_start, int i_end);
};