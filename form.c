//
// Created by vladimir on 11.03.2022.
//
#include "form.h"

struct buffer {
    struct FormStack** stacks;
    size_t size;
    size_t capacity;
};

void extendBuffer(struct buffer* buf) {
    if (buf->size + 1 >= buf->capacity) {
        size_t new_capacity = !buf->capacity ? 1 : buf->capacity * 2;
        struct FormStack** tmp = (struct FormStack**)malloc((new_capacity + 1) * sizeof(struct FormStack*));
        if (!tmp) {
            if (buf->stacks) {
                free(buf->stacks);
            }
            exit(137);
        }
        if (buf->stacks) {
            tmp = memcpy(tmp, buf->stacks, buf->capacity * sizeof(struct FormStack*));
            free(buf->stacks);
        }
        buf->stacks = tmp;
        buf->capacity = new_capacity;
    }

    buf->size++;
}


void addToBuffer(struct FormStack** stack, struct buffer* buf) {
    extendBuffer(buf);

    memcpy(&(buf->stacks[buf->size - 1]), stack, sizeof(struct FormStack*));

}


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
    struct FormStack* formStack = (struct FormStack*)malloc(sizeof(struct FormStack));
    formStack->size = n;
    formStack->stack = (struct Form*)malloc(sizeof(struct Form) * n);
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
int compForm (const void* elem1, const void* elem2) { //сравниваем по ответственному > адресу > номеру
    //elem1 = (struct Form*)elem1;
    //elem2 = (struct Form*)elem2;
    int tmp = compAdmin((struct Form*)elem1, (struct Form*)elem2);
    if (tmp != 0) return tmp;
    tmp = compAddress((struct Form*)elem1, (struct Form*)elem2);
    if (tmp != 0) return tmp;
    return compID((struct Form*)elem1, (struct Form*)elem2);
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
    struct buffer buf =  {NULL, 0, 0};
    for (int i =1;  i < n; i++) {


        if (!isNext(&(formStack->stack[i - 1]), &(formStack->stack[i]))) {
            struct FormStack* new = (struct FormStack*)malloc(sizeof(struct FormStack));
            new->size = i - start;
            new->stack = &(formStack->stack[start]);

            addToBuffer(&new, &buf);

            (*stacksNum)++;
            start = i;
        }
    }
    struct FormStack* new = (struct FormStack*)malloc(sizeof(struct FormStack));
    new->size = n - start;
    new->stack = &(formStack->stack[start]);
    addToBuffer(&new, &buf);

    (*stacksNum)++;

    return buf.stacks;
}

void showStacks(struct FormStack** stacks, int num) {
    for (int i = 0;i < num; i++) {
        printf("Стопка:%i\n", i);
        showFormStack(stacks[i]);
    }
}
void freeStacks(struct FormStack** stacks, int num) {
    /*for (int i = 0;i < num; i++) { //Недопустимое освобождение?
        freeFormStack(stacks[i]);
    }*/
    free(stacks);
}

int ret1 () {
    return 1;
}