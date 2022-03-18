

#include "form.h"



int main() {
    int n = inputInt(stdin);
    struct FormStack* formStack = createFormStack(stdin, n);
    int stacksNum;
    struct FormStack** stacks = splitFormStack(formStack, &stacksNum);
    showStacks(stacks, stacksNum);
    free(formStack);
    freeStacks(stacks, stacksNum);


    return 0;

}

