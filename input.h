//
// Created by vladimir on 11.03.2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#ifndef C2_INPUT_H
#define C2_INPUT_H

char inputChar(FILE* file);
char* createString(FILE* file);
void inputString(FILE* file, char* string, int length);
int inputInt(FILE* file);
u_short inputShortInt(FILE* file);

#endif //C2_INPUT_H
