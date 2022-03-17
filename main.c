

#include "form.h"



int main() {
    int n = inputInt(stdin);
    int* m;
    struct FormStack* formStack = createFormStack(stdin, n);
    struct FormStack** stacks = splitFormStack(formStack, &m);
    printf("out-of-funk:%i", stacks);
    /*for (int i = 0;i < n; i++) {
        showFormStack(stacks[i]);
    }*/
    //printf("%s", stacks[0]->stack[0].admin);
    freeFormStack(formStack);
    return 0;
}

