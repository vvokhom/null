#include <stdio.h>

#include "tehnopasr1.h"

int main(){
    int n;
    int ans[3];
    scanf("%d", &n);
    if(n < 3){
        printf("Less than 3 points\n");
        return 0;
    }
    int x[n], y[n];
    for(int i = 0; i < n; ++i){
        scanf("%d %d", &x[i], &y[i]);
    }

    algo(n, x, y, ans);

    print_ans(ans);

    return 0;
}