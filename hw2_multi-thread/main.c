#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

#include "func.c"

#define ERROR_CREATE_THREAD -11
#define ERROR_JOIN_THREAD   -12
#define SUCCESS				  0
#define NUM_THREADS           4
#define SIZE				100


int main() {
	time_t t0 = time(0);
	pthread_t threads[NUM_THREADS];
	int status, i, status_addr;
	someArgs_t args[NUM_THREADS];

	for (int i = 0; i < SIZE; i++)
        pthread_mutex_init(&mutexes[i], NULL);
    

    char* sstr = (char*)malloc(SIZE*sizeof(char));
    sstr = "aaabbcrrmmlljjpsslluuuiiiiiiiiikkzxcvbnm";
    //sstr = "qwertyuio";
	char** messages = subString(sstr);

	for (i = 0; i < NUM_THREADS; i++) {
		args[i].id = i;
		args[i].msg = messages[i];
	}

	for (i = 0; i < NUM_THREADS; i++) {
		status = pthread_create(&threads[i], NULL, helloWorld, (void*) &args[i]);
		if (status != 0) {
			exit(ERROR_CREATE_THREAD);
		}
	}

	for (i = 0; i < NUM_THREADS; i++) {
		status = pthread_join(threads[i], (void**)&status_addr);
		if (status != SUCCESS) {
			exit(ERROR_JOIN_THREAD);
		}
	}

	int lenth = maxinmum_lenth();
    char symb = find_symbol(sstr, lenth);
    char* ans = (char*)malloc((lenth+1)*sizeof(char));
    ans = print_ans(symb, lenth);
    printf("Str is: %s\nAnswer is: %s", sstr, ans);

    time_t t1 = time(0);
    double time_in_seconds = difftime(t1, t0);
    printf("\nTime is: %lf", time_in_seconds);

	return 0;
}