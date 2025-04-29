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

TEST(GradientDescent, CG){
    std::vector<double> v{
        4, 1, 2,    3, 1,
        1, 5,    2, 1,  
        2,    6, 1,    2,
           2, 1, 7, 1,   
        3, 1,    1, 8, 1,
        1,    2,    1, 9
    };
    std::vector<int> i{
        1, 1, 1,    1, 1,
        2, 2,    2, 2,   
        3,    3, 3,    3,
           4, 4, 4, 4,   
        5, 5,    5, 5, 5,
        6,    6,    6, 6
    };
    std::vector<int> j{
        1, 2, 3,    5, 6,
        1, 2,    4, 5,     
        1,    3, 4,    6,
           2, 3, 4, 5,   
        1, 2,    4, 5, 6,
        1,    3,    5, 6
    };
    std::vector<double> awns{1, 2, 3, 4, 5, 6};
    // std::vector<int> i{1, 1, 1, 2, 2, 2, 3, 3, 3};
    // std::vector<int> j{1, 2, 3, 1, 2, 3, 1, 2, 3};
    // std::vector<double> v{3, 2, 2, 1, 3, 1, 2, 1, 3};
    // std::vector<double> awns{1, 2, 3};
    DOK tmp(i, j, v);
    CSR A(tmp);
    std::vector<double> b = A*awns;
    std::vector<double> x0 (6, 0.0);
    std::vector<double> x = CG(A, b, x0, 1e-7, 100);
    // for (int i = 0; i<6; i++){
    //     for (int j = 0; j < 6; j++){
    //         std::cout << A(i+1, j+1) << " ";
    //     }
    //     std::cout << std::endl;
    // }
    for (int i = 0; i < 3; i++){
        ASSERT_NEAR(awns[i], x[i], 1e-7);
    }
}

TEST(GradientDescent, BiCG){
    std::vector<double> v{
        4, 1, 2,    3, 1,
        1, 5,    2, 1,  
        2,    6, 1,    2,
           2, 1, 7, 1,   
        3, 1,    1, 8, 1,
        1,    2,    1, 9
    };
    std::vector<int> i{
        1, 1, 1,    1, 1,
        2, 2,    2, 2,   
        3,    3, 3,    3,
           4, 4, 4, 4,   
        5, 5,    5, 5, 5,
        6,    6,    6, 6
    };
    std::vector<int> j{
        1, 2, 3,    5, 6,
        1, 2,    4, 5,     
        1,    3, 4,    6,
           2, 3, 4, 5,   
        1, 2,    4, 5, 6,
        1,    3,    5, 6
    };
    std::vector<double> awns{1, 2, 3, 4, 5, 6};
    DOK tmp(i, j, v);
    CSR A(tmp);
    std::vector<double> b = A*awns;
    std::vector<double> x0 (6, 0.0);
    std::vector<double> x = BiCG(A, b, x0, 1e-7, 100);
    for (int i = 0; i < 3; i++){
        ASSERT_NEAR(awns[i], x[i], 1e-7);
    }
}

TEST(GradientDescent, CGS){
    std::vector<double> v{
        4, 1, 2,    3, 1,
        1, 5,    2, 1,  
        2,    6, 1,    2,
           2, 1, 7, 1,   
        3, 1,    1, 8, 1,
        1,    2,    1, 9
    };
    std::vector<int> i{
        1, 1, 1,    1, 1,
        2, 2,    2, 2,   
        3,    3, 3,    3,
           4, 4, 4, 4,   
        5, 5,    5, 5, 5,
        6,    6,    6, 6
    };
    std::vector<int> j{
        1, 2, 3,    5, 6,
        1, 2,    4, 5,     
        1,    3, 4,    6,
           2, 3, 4, 5,   
        1, 2,    4, 5, 6,
        1,    3,    5, 6
    };
    std::vector<double> awns{1, 2, 3, 4, 5, 6};
    DOK tmp(i, j, v);
    CSR A(tmp);
    std::vector<double> b = A*awns;
    std::vector<double> x0 (6, 0.0);
    std::vector<double> x = CGS(A, b, x0, 1e-7, 100);
    for (int i = 0; i < 3; i++){
        ASSERT_NEAR(awns[i], x[i], 1e-7);
    }
}