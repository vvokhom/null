#include "gtest/gtest.h"
#include "string.h"

extern "C" {
    #include "file.h"
}

#define SIZE 100

static int arr[SIZE] = {0};

TEST(widget1, ok1) {
    char str[] = "aaabbcrrmmlljjpsslluuuiiiiiiiiikk";
    char ans[] = "bb";

    amount_different(str);
    int lenth = maxinmum_lenth();
    //printf("lenth is %d\n", lenth);
    char symb = find_symbol(str, lenth);
    char* my_ans = (char*)malloc((lenth+1)*sizeof(char));
    my_ans = print_ans(symb, lenth);
    printf("str is: %s", my_ans);
    ASSERT_EQ(strcmp(my_ans, ans), 0);
}

TEST(widget2, ok2) {
    char str[] = "qwerty";
    char ans[] = "q";

    amount_different(str);
    int lenth = maxinmum_lenth();
    //printf("lenth is %d\n", lenth);
    char symb = find_symbol(str, lenth);
    char* my_ans = (char*)malloc((lenth+1)*sizeof(char));
    my_ans = print_ans(symb, lenth);
    printf("str is: %s", my_ans);
    ASSERT_EQ(strcmp(my_ans, ans), 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}