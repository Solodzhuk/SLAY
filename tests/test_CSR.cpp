#include <gtest/gtest.h>

#include <CSR/CSR.hpp>

TEST(CSR, testSort){
        std::vector<int> i{1, 3, 2};
        std::vector<int> j{3, 1, 2};
        std::vector<double> a{1, 2, 3};
        std::vector<int> real_i{1, 2, 3};
        std::vector<int> real_j{3, 2, 1};
        std::vector<double> val{1, 3, 2};
    sort(i, j, a, 0, 3);
    for (int c = 0; c < 3; c++){
        ASSERT_NEAR(i[c], real_i[c], 1e-7);
        ASSERT_NEAR(j[c], real_j[c], 1e-7);
        ASSERT_NEAR(a[c], val[c], 1e-7);
    }
}

TEST(CSR, testDOK){
    std::vector<int> i{1, 3, 2};
    std::vector<int> j{3, 1, 2};
    std::vector<double> a{1, 2, 3};
    std::vector<double> val{1, 2, 3};
    DOK mat(i, j, a);
    for (int c = 0; c < 3; c++){
        ASSERT_NEAR(val[c], mat.access(i[c], j[c]), 1e-7);
    }
}

TEST(CSR, testCSR){
    std::vector<int> i{1, 3, 2};
    std::vector<int> j{3, 1, 2};
    std::vector<double> a{1, 2, 3};
    DOK mat(i, j, a);
    CSR mat_CSR(mat);
    std::vector<double> val{1, 2, 3};
    for (int c = 0; c < 3; c++){
        ASSERT_NEAR(val[c], mat_CSR(i[c], j[c]), 1e-7);
    }
}

TEST(CSR, testCSR_2){
    std::vector<int> i{1, 1, 3, 3};
    std::vector<int> j{2, 4, 3, 4};
    std::vector<double> a{8, 6, 9, 5};
    DOK mat(i, j, a);
    CSR mat_CSR(mat);
    std::vector<double> val{8, 6, 9, 5};
    for (int i = 0; i < 5; i++){
        std::cout << mat_CSR.rows[i] << std::endl;
    }
    for (int c = 0; c < 3; c++){
        ASSERT_NEAR(val[c], mat_CSR(i[c], j[c]), 1e-7);
    }
}

TEST(CSR, testVectSum){
    std::vector<double> a{1, 2, 3.5};
    std::vector<double> b{2, 0.3, 4};
    std::vector<double> c{3, 2.3, 7.5};
    for (int i = 0; i < 3; i++){
        ASSERT_NEAR(a[i]+b[i], c[i], 1e-7);
    }
}

TEST(CSR, testDOT){
    std::vector<double> a{1, 2, 3.5};
    std::vector<double> b{2, 3, 2};
    double c = 2 + 6 + 7;
    ASSERT_NEAR(DOT(a, b), c, 1e-7);
}

TEST(CSR, testMulVectDouble){
    std::vector<double> a{1, 2, 3.5};
    double b = 1.5;
    std::vector<double> res{1.5, 3, 5.25};
    for (int i = 0; i < 3; i++){
        ASSERT_NEAR(a[i]*b, res[i], 1e-7);
    }
}

TEST(CSR, testMulMatVect){
    std::vector<int> i{1, 3, 2};
    std::vector<int> j{3, 1, 2};
    std::vector<double> a{1, 2, 3};
    DOK mat(i, j, a);
    CSR mat_CSR(mat);
    std::vector<double> b{4, 5, 6};
    std::vector<double> tried = mat_CSR*b;
    std::vector<double> res{6, 15, 8};
    for (int c = 0; c < 3; c++){
        ASSERT_NEAR(res[c], tried[c], 1e-7);
    }
}
