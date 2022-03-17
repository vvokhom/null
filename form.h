//
// Created by vladimir on 11.03.2022.
//

#ifndef C1_FORM_H
#define C1_FORM_H

#include <assert.h>

#include "input.h"

struct Form {
    int id;
    char* address;
    char* admin;
};
struct FormStack {
    int size;
    struct Form* stack;
};
struct Form* inputForm(FILE* file, struct Form* form);
struct FormStack* inputFormStack(FILE* file, struct FormStack* formStack);
struct FormStack* createFormStack(FILE* file, int n);
void freeFormStack(struct FormStack* formStack);
void showForm(struct Form form);
void showFormStack(const struct FormStack* formStack);
struct FormStack* sortFormStack(struct FormStack* formStack);
struct FormStack** splitFormStack(struct FormStack* formStack, int* stacksNum);

#endif //C1_FORM_H
