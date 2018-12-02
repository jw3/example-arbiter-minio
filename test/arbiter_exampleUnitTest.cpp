#include "gtest/gtest.h"

#include "arbiter_example.hpp"

namespace
{
    using namespace pdal;

    TEST(DefaultTests, instantiation) {
        arbiter_example plugin();
        //EXPECT_EQ(plugin.getName(), "filters.arbiter_example");
    }
}
