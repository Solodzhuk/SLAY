#include <gtest/gtest.h>

#include <QR/QR.hpp>


TEST(QR, testHouseholder){
    Matrix one(2, 2);
    one(1, 1, 1);
    one(1, 2, 2);
    one(2, 1, 4);
    one(2, 2, 5);

    std::pair<Matrix, Matrix> qr = Householder_transf(one);
    for(int i = 1; i < 3; i++){
        for (int j = 1; j < 3; j++){
            ASSERT_NEAR(one(i, j), (qr.first*qr.second)(i, j), 1e-7);
        }
    }
}

TEST(QR, testQRSolve){
    Matrix one(2, 2);
    one(1, 1, 1);
    one(1, 2, 4);
    one(2, 1, 2);
    one(2, 2, 5);
    std::vector<double> b{2, 1};
    std::pair<Matrix, Matrix> qr = Householder_transf(one);
    std::vector<double> x = QR_solve(qr.first, qr.second, b);
    std::vector<double> awns{-2, 1};
    for (int i = 0; i < x.size(); i++){
        ASSERT_NEAR(x[i], awns[i], 1e-7);
    }
}

