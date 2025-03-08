#include <gtest/gtest.h>

#include <ChebAccel/ChebAccel.hpp>

TEST(ChebAccel, testChebAccel_iter){
    std::vector<int> i{1, 1, 1, 2, 2, 2, 3, 3, 3};
    std::vector<int> j{1, 2, 3, 1, 2, 3, 1, 2, 3};
    std::vector<double> v{3, 2, 2, 1, 3, 1, 2, 1, 3};
    std::vector<double> awns{1, 2, 3};
    DOK tmp(i, j, v);
    CSR A(tmp);
    std::vector<double> b = A*awns;
    std::vector<double> x = ChebAccel_simple_iter(A, b, 1e-7, 0.005, 10000);
    for (int i = 0; i < 3; i++){
        ASSERT_NEAR(awns[i], x[i], 1e-7);
    }
}

TEST(ChebAccel, testGet_perestanovki){
    std::vector<int> t = get_perestanovki(3);
    std::vector<int> awns{0, 7, 3, 4, 1, 6, 2, 5};
    for (int i = 0; i < 8; i++){
        ASSERT_EQ(t[i], awns[i]);
    }
}

TEST(ChebAccel, testGet_max_lambda){
    std::vector<int> i{1, 1, 1, 2, 2, 2, 3, 3, 3};
    std::vector<int> j{1, 2, 3, 1, 2, 3, 1, 2, 3};
    std::vector<double> v{3, 2, 2, 1, 3, 1, 2, 1, 3};
    DOK tmp(i, j, v);
    CSR A(tmp);
    double lambda = get_max_lambda(A, 0.02, 1000);
    double awns = 6.0;
    ASSERT_NEAR(lambda, awns, 0.02);
}