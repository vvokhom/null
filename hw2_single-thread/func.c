#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#include "file.h"

#define SIZE 100

static int arr[SIZE] = {0};

void amount_different(char *sstr){
    int current = 1;
    for(unsigned int i = 0; i < strlen(sstr); ++i){
        if(sstr[i] == sstr[i+1])
            current++;
        else{
            arr[current]++;
            current = 1;
        }
    }
}


int maxinmum_lenth(){
    int lenth = 0, maximum = 0;
    for(int i = 0; i < SIZE; ++i){
        if(arr[i] > maximum){
            maximum = arr[i];
            lenth = i;
        }
    }
    return lenth;
}


char find_symbol(char* sstr, int lenth){
    int current = 1;
    char symb = ' ';
    for(unsigned int i = 0; i < strlen(sstr); ++i){
        if(sstr[i] == sstr[i+1])
            current++;
        else{
            if(current == lenth){
                symb = sstr[i];
                return symb;
            }
            current = 1;
        }
    }
    return symb;
}


char* print_ans(char symb, int lenth){
    char* ans = (char*)malloc((lenth+1)*sizeof(char));
    for(int i = 0; i < lenth; ++i)
        ans[i] = symb;
    ans[lenth] = '\0';
    return ans;
}
