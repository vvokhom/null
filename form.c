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
int compForm (const struct Form* elem1, const struct Form* elem2) { //сравниваем по ответственному > адресу > номеру
    int tmp = compAdmin(elem1, elem2);
    if (tmp != 0) return tmp;
    tmp = compAddress(elem1, elem2);
    if (tmp != 0) return tmp;
    return compID(elem1, elem2);
}
int isNext(const struct Form* elem1, const struct Form* elem2) {
    return ((elem1->id + 1 == elem2->id) &&
            (compAddress(elem1, elem2) == 0) &&
            (compAdmin(elem1, elem2) == 0));
}
struct FormStack* sortFormStack(struct FormStack* formStack){
    qsort(formStack->stack, formStack->size, sizeof(struct Form), compForm);
    return formStack;
}
struct FormStack** splitFormStack(struct FormStack* formStack, int* stacksNum) {
    *stacksNum = 0;
    int n = formStack->size;
    int start = 0;
    sortFormStack(formStack);
    struct FormStack* stacks[n];

    for (int i =0;  i < n; i++) {

        if (/*isNext(&(formStack->stack[i - 1]), &(formStack->stack[i]))*/ 1 == 1) {
            struct FormStack *tmp = malloc(sizeof(struct FormStack));
            tmp->size = 1;
            tmp->stack = &(formStack->stack[i]);
            stacks[i] = tmp;

        }
    }
    for (int i = 0; i < n; i++) {
        showFormStack(stacks[i]);
    }
    printf("in-func:%i", (int)stacks);
    return stacks;
}

