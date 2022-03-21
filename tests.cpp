#include "gtest/gtest.h"

extern "C" {
    #include "tehnopasr1.h"
}

TEST(widget, ok) {
    int n = 4;
    int x[] = {1, 2, 1, 4};
    int y[] = {1, 2, 4, 1};
    int ans[3];
    algo(n, x, y, ans);
    ASSERT_EQ(ans[0]+1, 1);
    ASSERT_EQ(ans[1]+1, 3);
    ASSERT_EQ(ans[2]+1, 4);
}

TEST(widget1, ok1) {
    int n = 10;
    int x[] = {1, 4, 1, 4, 2, 2, 8, 0, -1, 100};
    int y[] = {1, 89, 4, 1, 2, 2, -2, 3, 17, 9};
    int ans[3];
    algo(n, x, y, ans);
    ASSERT_EQ(ans[0]+1, 1);
    ASSERT_EQ(ans[1]+1, 2);
    ASSERT_EQ(ans[2]+1, 10);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}