

#include "form.h"



int main() {
    int n = inputInt(stdin);
    struct FormStack* formStack = createFormStack(stdin, n);
    showFormStack(formStack);
    freeFormStack(formStack);
    return 0;
}

