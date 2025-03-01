#include <gtest/gtest.h>

#include <Iter/Iter.hpp>

TEST(Iter, testSimple){
    std::vector<int> i{1, 1, 1, 2, 2, 2, 3, 3, 3};
    std::vector<int> j{1, 2, 3, 1, 2, 3, 1, 2, 3};
    std::vector<double> v{3, 2, 2, 1, 3, 1, 2, 1, 3};
    std::vector<double> awns{1, 2, 3};
    DOK tmp(i, j, v);
    CSR A(tmp);
    std::vector<double> b = A*awns;
    std::vector<double> x = simple_iter(A, b, 1e-7, 0.005, 10000);
    for (int i = 0; i < 3; i++){
        ASSERT_NEAR(awns[i], x[i], 1e-7);
    }
}

TEST(Iter, testYakoby){
    std::vector<int> i{1, 1, 1, 2, 2, 2, 3, 3, 3};    // 9 2 2 
    std::vector<int> j{1, 2, 3, 1, 2, 3, 1, 2, 3};    // 1 9 1
    std::vector<double> v{9, 2, 2, 1, 9, 1, 2, 1, 9}; // 2 1 9
    std::vector<double> awns{1, 2, 3};
    DOK tmp(i, j, v);
    CSR A(tmp);
    std::vector<double> b = A*awns;
    std::vector<double> x = Yakoby_iter(A, b, 1e-7, 0.005, 1000);
    for (int i = 0; i < 3; i++){
        ASSERT_NEAR(awns[i], x[i], 1e-7);
    }
}

TEST(Iter, testGaussSeidel){
    std::vector<int> i{1, 1, 1, 2, 2, 2, 3, 3, 3};    // 9 2 2 
    std::vector<int> j{1, 2, 3, 1, 2, 3, 1, 2, 3};    // 1 9 1
    std::vector<double> v{9, 2, 2, 1, 9, 1, 2, 1, 9}; // 2 1 9
    std::vector<double> awns{1, 2, 3};
    DOK tmp(i, j, v);
    CSR A(tmp);
    std::vector<double> b = A*awns;
    std::vector<double> x = GaussSeidel_iter(A, b, 1e-7, 0.005, 1000);
    for (int i = 0; i < 3; i++){
        ASSERT_NEAR(awns[i], x[i], 1e-7);
    }
}