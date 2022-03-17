//
// Created by vladimir on 11.03.2022.
//
#include "input.h"


char inputChar(FILE* file) {
    char c = '\0';
    int result = 0;
    do {
        result = fscanf(file, "%c", &c);
    } while (result != 1);
    return c;
}

char* inputString(FILE* file) {
    struct buffer {
        char* string;
        size_t size;
        size_t capacity;
    } buf = {NULL, 0, 0};
    char c = '\0';
    while (c = inputChar(file), c != EOF && c != '\n') {
        if (buf.size + 1 >= buf.capacity) {
            size_t new_capacity = !buf.capacity ? 1 : buf.capacity * 2;
            char *tmp = (char *)malloc((new_capacity + 1) * sizeof(char)); // Как ее освободить? считается утечкой?
            if (!tmp) {
                if (buf.string) {
                    free(buf.string);
                }
                return NULL;
            }
            if (buf.string) {
                tmp = strcpy(tmp, buf.string);
                free(buf.string);
            }
            buf.string = tmp;
            /*if (tmp) {
                free(tmp);
            }*/
            buf.capacity = new_capacity;
        }

        buf.string[buf.size] = c;
        buf.string[buf.size + 1] = '\0';
        ++buf.size;
    }

    return buf.string;
}

int inputInt(FILE* file) {
    char c = '\0';
    int result = 0;
    while (c = inputChar(file), c != EOF && c != '\n') {
        if (!(c >= '0' && c <= '9')) {
            char *buf = inputString(file);
            if (buf) {
                free(buf);
            }
            return 0;
        }
        result = result * 10 + c - '0';
    }
    return result;
}



