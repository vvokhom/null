#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define ERROR_CREATE_THREAD -11
#define ERROR_JOIN_THREAD   -12
#define SUCCESS				  0
#define NUM_THREADS           4
#define SIZE				100

/*typedef struct someArgs_tag {
	int id;
	const char *msg;
} someArgs_t;*/

typedef struct someArgs_tag {
    int id;
    const char *msg;
} someArgs_t;


static int arr[SIZE] = {0};
static pthread_mutex_t mutexes[SIZE];



void* helloWorld(void *args) {
	someArgs_t *arg = (someArgs_t*) args;

    int current = 1;
    for(unsigned int i = 0; i < strlen(arg->msg); ++i){
        if(arg->msg[i] == arg->msg[i+1]){
            current++;
		}
        else{
			pthread_mutex_lock(&mutexes[current]);
            arr[current]++;
			pthread_mutex_unlock(&mutexes[current]);
            current = 1;
        }
    }
	return SUCCESS;
}


char** subString (const char* input)
{
    char** message = malloc(NUM_THREADS*sizeof(char*));
	int input_len = strlen(input);
	int offset = 0;
	int len = input_len / NUM_THREADS;
    int end = 0;

    for(int i = 0; i < NUM_THREADS; i++){
        len = input_len / NUM_THREADS;
		end += len;

        if(i == NUM_THREADS-1){
            char* newstr = (char*)malloc((len+1)*sizeof(char));
            for(int j = offset; j < input_len; j++)
                newstr[j-offset] = input[j]; 
            message[i] = newstr;
            return message;
        }

        while(input[end-1] == input[end]){
            len++; end++;
        }
        char* newstr = (char*)malloc((len+1)*sizeof(char));
        for(int j = offset; j < offset+len; j++){
            newstr[j-offset] = input[j];
        }
        newstr[len] = '\0';
        offset += len;
		message[i] = newstr;
	}
    return message;
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

/*void print_ans(char symb, int lenth){
    for(int i = 0; i < lenth; ++i)
        printf("%c", symb);
}*/

char* print_ans(char symb, int lenth){
    char* ans = (char*)malloc((lenth+1)*sizeof(char));
    for(int i = 0; i < lenth; ++i)
        ans[i] = symb;
    ans[lenth] = '\0';
    return ans;
}

