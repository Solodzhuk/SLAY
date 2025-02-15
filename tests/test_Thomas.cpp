#include <gtest/gtest.h>

#include <ThomasAlg/ThomasAlg.hpp>



TEST(ThomasAlg, fullTest1){

    std::vector<float> to_be = {2.0 / 7, 1.0 / 7, 2.0 / 7};
    std::vector<float> a{1, 1};
    std::vector<float> b{3, 3, 3};
    std::vector<float> c{1, 1};
    std::vector<float> d{1, 1, 1};
    std::vector<float> res = ThomasAlg(a, b, c, d);

    for (int i = 0; i < 3; i++){
        ASSERT_NEAR(to_be[i], (res)[i], 1e-7);
    }
}

TEST(ThomasAlg, fullTest2){

    std::vector<float> to_be = {12.0/43, 7.0/43, 23.0/43};
    std::vector<float> a{1, 2};
    std::vector<float> b{3, 4, 5};
    std::vector<float> c{1, 2};
    std::vector<float> d{1, 2, 3};
    std::vector<float> res = ThomasAlg(a, b, c, d);

    for (int i = 0; i < 3; i++){
        ASSERT_NEAR(to_be[i], (res)[i], 1e-7);
    }
}

TEST(ThomasAlg, fullTest3){

    std::vector<float> to_be = {3.0 / 14, -1.0 / 7, 15.0 / 28};
    std::vector<float> a{5, 1};
    std::vector<float> b{6, 8, 4};
    std::vector<float> c{2, 2};
    std::vector<float> d{1, 1, 2};
    std::vector<float> res = ThomasAlg(a, b, c, d);

    for (int i = 0; i < 3; i++){
        ASSERT_NEAR(to_be[i], (res)[i], 1e-7);
    }
}