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

char* createString(FILE* file) {
    struct buffer {
        char* string;
        size_t size;
        size_t capacity;
    } buf = {NULL, 0, 0};
    char c = '\0';
    while (c = inputChar(file), c != EOF && c != '\n') {
        if (buf.size + 1 >= buf.capacity) {
            size_t new_capacity = !buf.capacity ? 1 : buf.capacity * 2;
            char *tmp = (char *)malloc((new_capacity + 1) * sizeof(char));
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

void inputString(FILE* file, char* string, int length) {
    int i = 0;
    char c = '\0';
    for (i = 0; i < length; i++) {
        if(c = inputChar(file), c != EOF && c != '\n') {
            string[i] = c;
        } else {
            string[i] = '\0';
            break;
        }

    }


}

int inputInt(FILE* file) {
    char c = '\0';
    int result = 0;
    while (c = inputChar(file), c != EOF && c != '\n') {
        if (!(c >= '0' && c <= '9')) {
            char *buf = createString(file);
            if (buf) {
                free(buf);
            }
            return 0;
        }
        if (result > INT_MAX / 10 ) {
            printf("Too large number!");
            result = 0;
        }
        result = result * 10 + c - '0';
    }
    return result;
}
u_short inputShortInt(FILE* file) {
    int num = inputInt(file);
    if (num > USHRT_MAX) {
        printf("Too large number!");
        num = USHRT_MAX;
    }
    return (u_short)num;
}



