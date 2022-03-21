#include <stdio.h>
#include <stdlib.h>

#include "tehnopasr1.h"

void algo(int n, int* x, int* y, int* ans){
    double max_square = -1, square = -1;
    for(int i = 0; i < n-2; ++i){
        for(int j = i+1; j < n-1; ++j){
            for(int k = j+1; k < n; ++k){
                square = abs((x[j]-x[i]) * (y[k]-y[i])- (x[k]-x[i])*(y[j]-y[i]));
                if(max_square < (double)square/2) {
                    max_square = (double)square/2;
                    ans[0] = i; ans[1] = j; ans[2] = k;
                }

            }
        }
    }
}

void print_ans(int* ans){
    printf("%d %d %d", ans[0]+1, ans[1]+1, ans[2]+1);
}
