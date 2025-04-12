#include <gtest/gtest.h>

#include <GradientDescent/GradientDescent.hpp>

TEST(GradientDescent, SteepestGradientDescent){
    std::vector<int> i{1, 1, 1, 2, 2, 2, 3, 3, 3};
    std::vector<int> j{1, 2, 3, 1, 2, 3, 1, 2, 3};
    std::vector<double> v{3, 2, 2, 1, 3, 1, 2, 1, 3};
    std::vector<double> awns{1, 2, 3};
    DOK tmp(i, j, v);
    CSR A(tmp);
    std::vector<double> b = A*awns;
    std::vector<double> x = SteepestGradientDescent(A, b, 1e-7, 10000);
    for (int i = 0; i < 3; i++){
        ASSERT_NEAR(awns[i], x[i], 1e-7);
    }
}