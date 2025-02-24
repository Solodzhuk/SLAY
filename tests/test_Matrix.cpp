#include <gtest/gtest.h>

#include <Matrix/Matrix.hpp>

TEST(Matrix, testShape){
    Matrix m(3, 4);
    ASSERT_EQ(m.shape().first, 3);
    ASSERT_EQ(m.shape().second, 4);
}

TEST(Matrix, testBrackets){
    Matrix m(3, 4);
    m(2, 3, 1);
    ASSERT_EQ(m(2, 3), 1);
    ASSERT_EQ(m(1, 1), 0);
}

TEST(Matrix, testMulVect){
    Matrix m(3, 4);
    m(1, 1, 1);
    m(2, 2, 2);
    m(3, 3, 3);
    m(3, 4, 1);
    std::vector<double> b{1, 1, 1, 1};
    std::vector<double> res = m*b;
    ASSERT_NEAR(res[0], 1, 1e-7);
    ASSERT_NEAR(res[1], 2, 1e-7);
    ASSERT_NEAR(res[2], 4, 1e-7);
}

TEST(Martix, testMulMat){
    Matrix one(2, 3);
    Matrix two(3, 2);
    one(1, 1, 1);
    one(1, 2, 2);
    one(1, 3, 3);
    one(2, 1, 4);
    one(2, 2, 5);
    one(2, 3, 6);

    two(1, 1, 1);
    two(1, 2, 2);
    two(2, 1, 3);
    two(2, 2, 4);
    two(3, 1, 5);
    two(3, 2, 6);
    
    Matrix res = one*two;

    ASSERT_EQ(res.shape().first, 2);
    ASSERT_EQ(res.shape().second, 2);
    ASSERT_NEAR(res(1, 1), 22, 1e-7);
    ASSERT_NEAR(res(1, 2), 28, 1e-7);
    ASSERT_NEAR(res(2, 1), 49, 1e-7);
    ASSERT_NEAR(res(2, 2), 64, 1e-7);
}

TEST(Matrix, testTranspose){
    Matrix m(3, 4);
    m(1, 1, 1);
    m(1, 2, 2);
    m(3, 2, 3);
    m(3, 4, 1);
    Matrix n = m.transpose();
    ASSERT_NEAR(n(1, 1), 1, 1e-7);
    ASSERT_NEAR(n(2, 1), 2, 1e-7);
    ASSERT_NEAR(n(2, 3), 3, 1e-7);
    ASSERT_NEAR(n(4, 3), 1, 1e-7);
}

TEST(Matrix, testMakeEye){
    Matrix m = make_eye(4);
    for (int i = 1; i < 5; i++){
        for (int j = 1; j < 5; j++){
            if (i == j){
                ASSERT_NEAR(m(i, j), 1, 1e-7);
            }else{
                ASSERT_NEAR(m(i, j), 0, 1e-7);
            }
        }
    }
}

TEST(Matrix, testGetCol){
    Matrix m(3, 4);
    m(1, 1, 1);
    m(1, 2, 2);
    m(3, 2, 3);
    m(3, 4, 1);
    std::vector<double> vec = m.get_col(2); 
    ASSERT_EQ(vec.size(), 3);
    ASSERT_NEAR(vec[0], 2, 1e-7);
    ASSERT_NEAR(vec[1], 0, 1e-7);
    ASSERT_NEAR(vec[2], 3, 1e-7);
    std::vector<double> vec1 = m.get_col(2, 1, 3);
    ASSERT_EQ(vec1.size(), 2);
    ASSERT_NEAR(vec1[0], 2, 1e-7);
    ASSERT_NEAR(vec1[1], 0, 1e-7);

}