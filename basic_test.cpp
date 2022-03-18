
#include <gtest/gtest.h>


extern "C" {
#include "form.h"
}
//TODO:увеличить покрытие
TEST(basic_test, Returns1) {
    EXPECT_EQ(ret1(), 1);
}