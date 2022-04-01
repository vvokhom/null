#include "func.c"

int main(){
    time_t t0 = time(0);
    char *sstr = (char*)malloc(10*sizeof(char));
    sstr = "aaabbcrrmmlljjpsslluuuiiiiiiiiikk";
    amount_different(sstr);
    int lenth = maxinmum_lenth();
    char symb = find_symbol(sstr, lenth);
    printf("Str is: %s\n", sstr);
    char* ans = (char*)malloc((lenth+1)*sizeof(char));
    ans = print_ans(symb, lenth);
    printf("ans is: %s", ans);
    
    time_t t1 = time(0);
    double time_in_seconds = difftime(t1, t0);
    printf("\nTime is: %lf", time_in_seconds);

    return 0;
}