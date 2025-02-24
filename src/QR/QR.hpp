#pragma once
#include <vector>
#include <Matrix/Matrix.hpp>
#include <CSR/CSR.hpp>

std::pair<Matrix, Matrix> Householder_transf(Matrix& A);
std::vector<double> QR_solve (Matrix& Q, Matrix& R, const std::vector<double> b);
