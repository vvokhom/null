/*#include "gtest/gtest.h"
#include "string.h"

extern "C" {
    #include "file.h"
}

#define SIZE 100

static int arr[SIZE] = {0};

TEST(widget1, ok1) {
    char str[] = "aaabbcrrmmlljjpsslluuuiiiiiiiiikk";
    char ans[] = "bb";

    amount_different(str);
    int lenth = maxinmum_lenth();
    //printf("lenth is %d\n", lenth);
    char symb = find_symbol(str, lenth);
    char* my_ans = (char*)malloc((lenth+1)*sizeof(char));
    my_ans = print_ans(symb, lenth);
    printf("str is: %s", my_ans);
    ASSERT_EQ(strcmp(my_ans, ans), 0);
}

TEST(widget2, ok2) {
    char str[] = "qwerty";
    char ans[] = "q";

    amount_different(str);
    int lenth = maxinmum_lenth();
    //printf("lenth is %d\n", lenth);
    char symb = find_symbol(str, lenth);
    char* my_ans = (char*)malloc((lenth+1)*sizeof(char));
    my_ans = print_ans(symb, lenth);
    printf("str is: %s", my_ans);
    ASSERT_EQ(strcmp(my_ans, ans), 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}*/

#include "gtest/gtest.h"
#include "string.h"

#define NUM_THREADS           4
#define SIZE                100

extern "C" {
    #include "file.h"
}


typedef struct someArgs_tag {
    int id;
    const char *msg;
} someArgs_t;


static int arr[SIZE] = {0};
static pthread_mutex_t mutexes[SIZE];

TEST(widget1, ok1) {
    char sstr[] = "aaabbcrrmmlljjpsslluuuiiiiiiiiikk";
    char my_ans[] = "bb";
    pthread_t threads[NUM_THREADS];
    int status, i, status_addr;
    someArgs_t args[NUM_THREADS];

    for (int i = 0; i < SIZE; i++)
        pthread_mutex_init(&mutexes[i], NULL);
    char** messages = subString(sstr);

    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].id = i;
        args[i].msg = messages[i];
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        status = pthread_create(&threads[i], NULL, helloWorld, (void*) &args[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        status = pthread_join(threads[i], (void**)&status_addr);
    }

    int lenth = maxinmum_lenth();
    char symb = find_symbol(sstr, lenth);
    char* ans = (char*)malloc((lenth+1)*sizeof(char));
    ans = print_ans(symb, lenth);
    ASSERT_EQ(strcmp(my_ans, ans), 0);
}



TEST(widget2, ok2) {
    char sstr[] = "aaabbcrrmmlljjpsslluuuiiiiiiiiikkwilehxnwejxd";
    char my_ans[] = "c";
    pthread_t threads[NUM_THREADS];
    int status, i, status_addr;
    someArgs_t args[NUM_THREADS];

    for (int i = 0; i < SIZE; i++)
        pthread_mutex_init(&mutexes[i], NULL);
    char** messages = subString(sstr);

    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].id = i;
        args[i].msg = messages[i];
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        status = pthread_create(&threads[i], NULL, helloWorld, (void*) &args[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        status = pthread_join(threads[i], (void**)&status_addr);
    }

    int lenth = maxinmum_lenth();
    char symb = find_symbol(sstr, lenth);
    char* ans = (char*)malloc((lenth+1)*sizeof(char));
    ans = print_ans(symb, lenth);
    ASSERT_EQ(strcmp(my_ans, ans), 0);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}