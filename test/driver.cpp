#include "gtest/gtest.h"


GTEST_API_ int main(int c, char** v) {
    testing::InitGoogleTest(&c, v);
    return RUN_ALL_TESTS();
}
