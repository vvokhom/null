//
// Created by vladimir on 11.03.2022.
//
#include "form.h"

struct Form* inputForm(FILE* file, struct Form* form) {

    form->id = inputInt(file);

    char* string;
    string = inputString(file);
    assert(string);
    form->address = string;

    string = inputString(file);
    assert(string);
    form->admin = string;

    return form;
}
struct FormStack* inputFormStack(FILE* file, struct FormStack* formStack) {
    int n = formStack->size;
    for (int i = 0; i < n; i++) {
        inputForm(file, &(formStack->stack[i])); //???
    }
    return formStack;
}
struct FormStack* createFormStack(FILE* file, int n){
    struct FormStack* formStack = malloc(sizeof(struct FormStack));
    formStack->size = n;
    formStack->stack = malloc(sizeof(struct Form) * n);
    inputFormStack(file, formStack);
    return formStack;
}
void freeFormStack(struct FormStack* formStack) {
    free(formStack->stack);
    free(formStack);
}
void showForm(const struct Form form) {
    printf("Номер:%i\nАдрес:%s\nОтветственный:%s\n---\n", form.id, form.address, form.admin);
}
void showFormStack(const struct FormStack* formStack) {
    int n = formStack->size;
    for (int i = 0; i < n; i++) {
        showForm(formStack->stack[i]);
    }
}


int compAdmin (const struct Form* elem1, const struct Form* elem2) {
    return strcmp(elem1->admin, elem2->admin);
}
int compAddress (const struct Form* elem1, const struct Form* elem2) {
    return strcmp(elem1->address, elem2->address);
}
int compID (const struct Form* elem1, const struct Form* elem2) {
    if (elem1->id > elem2->id) return  1;
    if (elem1->id < elem2->id) return -1;
    return 0;
}

struct FormStack* sortFormStack(struct FormStack* formStack){
    //qsort(forms, n, sizeof(struct Form), compID);
    return formStack;
}



