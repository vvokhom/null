

#include "data.h"



int main() {
    Employee* base;
    int n = inputInt(stdin);
    base = createEmployeeBase(stdin, n);
    showEmployeeBase(base, n);
    return 0;

}

