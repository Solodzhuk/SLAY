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
    std::vector<double> x0(b.size(), 0.0);
    std::vector<double> x = simple_iter(A, b, x0, 1e-7, 0.005, 10000);
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
    std::vector<double> x = Yakoby_iter(A, b, 1e-7, 1000);
    for (int i = 0; i < 3; i++){
        ASSERT_NEAR(awns[i], x[i], 1e-7);
    }
}
// TEST(Iter, testYakoby_2){
//     std::vector<int> i{1, 1, 2, 2, 2, 3, 3, 4, 4};
//     std::vector<int> j{1, 2, 1, 2, 3, 2, 3, 2, 4};
//     std::vector<double> a{62, 9, 8, 55, 6, 2, 92, 8, 88};
//     DOK mat(i, j, a);
//     CSR A(mat);
//     std::vector<double> b{4, 8, 7, 6};
//     double acc = abs_val(b)/1000;
//     std::vector<double> awns = Yakoby_iter(A, b, acc, 0.005, 1000);
//     std::cout << acc << std::endl;
//     ASSERT_EQ(1, 1);
// }

TEST(Iter, testGaussSeidel){
    std::vector<int> i{1, 1, 1, 2, 2, 2, 3, 3, 3};    // 9 2 2 
    std::vector<int> j{1, 2, 3, 1, 2, 3, 1, 2, 3};    // 1 9 1
    std::vector<double> v{9, 2, 2, 1, 9, 1, 2, 1, 9}; // 2 1 9
    std::vector<double> awns{1, 2, 3};
    DOK tmp(i, j, v);
    CSR A(tmp);
    std::vector<double> b = A*awns;
    std::vector<double> x = GaussSeidel_iter(A, b, 1e-7, 1000);
    for (int i = 0; i < 3; i++){
        ASSERT_NEAR(awns[i], x[i], 1e-7);
    }
}

TEST(Iter, Symm_GaussSeidel_iter){
    std::vector<int> i{1, 1, 1, 2, 2, 2, 3, 3, 3};    // 9 2 2 
    std::vector<int> j{1, 2, 3, 1, 2, 3, 1, 2, 3};    // 1 9 1
    std::vector<double> v{9, 2, 2, 1, 9, 1, 2, 1, 9}; // 2 1 9
    std::vector<double> awns{1, 2, 3};
    DOK tmp(i, j, v);
    CSR A(tmp);
    std::vector<double> b = A*awns;
    std::vector<double> x = Symm_GaussSeidel_iter(A, b, 1e-7, 1000);
    for (int i = 0; i < 3; i++){
        ASSERT_NEAR(awns[i], x[i], 1e-7);
    }
}

TEST(Iter, SOR){
    std::vector<int> i{1, 1, 1, 2, 2, 2, 3, 3, 3};    // 9 2 2 
    std::vector<int> j{1, 2, 3, 1, 2, 3, 1, 2, 3};    // 1 9 1
    std::vector<double> v{9, 2, 2, 1, 9, 1, 2, 1, 9}; // 2 1 9
    std::vector<double> awns{1, 2, 3};
    DOK tmp(i, j, v);
    CSR A(tmp);
    std::vector<double> b = A*awns;
    std::vector<double> x = SOR(A, b, 1e-7, 1000);
    for (int i = 0; i < 3; i++){
        ASSERT_NEAR(awns[i], x[i], 1e-7);
    }

}

TEST(Iter, testGet_max_lambda){
    std::vector<int> i{1, 1, 1, 2, 2, 2, 3, 3, 3};
    std::vector<int> j{1, 2, 3, 1, 2, 3, 1, 2, 3};
    std::vector<double> v{3, 2, 2, 1, 3, 1, 2, 1, 3};
    DOK tmp(i, j, v);
    CSR A(tmp);
    double lambda = get_max_lambda(A, 0.02, 1000);
    double awns = 6.0;
    ASSERT_NEAR(lambda, awns, 0.02);
}