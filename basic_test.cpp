#include <gtest/gtest.h>


extern "C" {
#include "form.h"
}

TEST(logic_test, form_comparison) {
    struct Form form1 = {1, "a", "a"};
    struct Form form2 = {2, "a", "a"};

    EXPECT_TRUE(isNext(&form1, &form2));
}
TEST(logic_test, sorting) {
    const size_t formStackSize = sizeof(struct FormStack);
    const size_t formSize = sizeof(struct Form);
    struct Form formsUnsorted[3];
    formsUnsorted[0] = {1, "b", "a"};
    formsUnsorted[1] = {2, "a", "a"};
    formsUnsorted[2] = {1, "a", "a"};
    struct FormStack formStackUnsorted = {3, formsUnsorted};

    struct Form formsSorted[3];
    formsSorted[0] = formsUnsorted[2] ;
    formsSorted[1] = formsUnsorted[1];
    formsSorted[2] = formsUnsorted[0];
    struct FormStack formStackSorted = {3, formsSorted};

    sortFormStack(&formStackUnsorted);
    EXPECT_TRUE(memcmp(&(formStackUnsorted.stack[0]), &(formStackSorted.stack[0]), formSize) == 0);
    EXPECT_TRUE(memcmp(&(formStackUnsorted.stack[1]), &(formStackSorted.stack[1]), formSize) == 0);
    EXPECT_TRUE(memcmp(&(formStackUnsorted.stack[2]), &(formStackSorted.stack[2]), formSize) == 0);

}

TEST(logic_test, splitting) {
    const size_t formStackSize = sizeof(struct FormStack);
    const size_t formSize = sizeof(struct Form);
    struct Form formsUnsorted[3];
    formsUnsorted[0] = {1, "b", "a"};
    formsUnsorted[1] = {2, "a", "a"};
    formsUnsorted[2] = {1, "a", "a"};
    struct FormStack formStackUnsorted = {3, formsUnsorted};

    struct Form stack0[2];
    stack0[0] = formsUnsorted[2] ;
    stack0[1] = formsUnsorted[1];

    struct Form stack1[1];
    stack1[0] = formsUnsorted[0] ;

    struct FormStack formStackSorted0 = {2, stack0};
    struct FormStack formStackSorted1 = {1, stack1};

    int stackNum;

    struct FormStack** resFormStacks = splitFormStack(&formStackUnsorted, &stackNum);
    //мне не нравится:
    EXPECT_TRUE(memcmp(&(resFormStacks[0]->stack[0]), &(formStackSorted0.stack[0]), formSize) == 0);
    EXPECT_TRUE(memcmp(&(resFormStacks[0]->stack[1]), &(formStackSorted0.stack[1]), formSize) == 0);
    EXPECT_TRUE(memcmp(&(resFormStacks[1]->stack[0]), &(formStackSorted1.stack[0]), formSize) == 0);
}
/* TODO:
TEST(input_test, numerical) {
    FILE* file = fopen("/home/vladimir/CLionProjects/HW/C1/null/test_files/number", "r");
    int num = inputInt(file);
    EXPECT_EQ(num, 586);
    fclose(file);

}
TEST(input_test, text) {
    FILE* file = fopen("/home/vladimir/CLionProjects/HW/C1/null/test_files/text", "r");
    char* str = inputString(file);
    EXPECT_EQ(str, "Lorem Ipsum Dolores");
    fclose(file);
}
*/
