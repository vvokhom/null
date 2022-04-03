//
// Created by vladimir on 01.04.2022.
//

#include "report.h"

#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct BasePart {
    Employee* start;
    size_t size;
} BasePart;

int compPosition(const Employee* elem1, const Employee* elem2) {
    return strcmp(elem1->position, elem2->position);
}
int compExperience(const Employee* elem1, const Employee* elem2) {
    if (elem1->experience > elem2->experience) return  1;
    if (elem1->experience < elem2->experience) return -1;
    return 0;
}
int compEmployee(const void* elem1, const void* elem2) {
    int tmp = compPosition((Employee*)elem1, (Employee*)elem2);
    if (tmp != 0) return tmp;
    tmp = compExperience((Employee*)elem1, (Employee*)elem2);
    return tmp;
}

void* sortPartEmployeeBase(void* args) {
    BasePart* part = (BasePart*)args;

    qsort(part->start, part->size, sizeof(Employee), compEmployee);
    return NULL;
}

void mergeSortedEmployeeBases(Employee* base1, size_t size1, Employee* base2, size_t size2) { //only for adjoining arrays!!! base1 < base2
    Employee* temp = (Employee*)malloc(sizeof(Employee) * (size1 + size2));
    int n = 0;
    int m = 0;
    for (int i = 0; i < (size1 + size2); i++) {
        if (compEmployee(&(base1[n]), &(base2[m])) == 1) {
            memcpy(&(temp[i]), &(base2[m]), sizeof(Employee));
            m++;
        } else {
            memcpy(&(temp[i]), &(base1[n]), sizeof(Employee));
            n++;
        }
    }
    memcpy(base1, temp, size1 + size2);
    free(temp);
}

void sortEmployeeBase(Employee* base, size_t n) {

    int threadsNum = /*sysconf(_SC_NPROCESSORS_ONLN) - 1*/ 1;
    pthread_t threadID[threadsNum];
    int partSize = n / (threadsNum + 1);
    BasePart* part[threadsNum];
    for (int i = 0; i < threadsNum; i++) {

        part[i] = (BasePart*)malloc(sizeof(BasePart));
        part[i]->start = base + partSize * i;
        part[i]->size = partSize;
        pthread_create(&(threadID[i]), NULL, sortPartEmployeeBase, (void*)part[i]);
    }

    qsort(base + partSize * threadsNum, n - partSize * threadsNum, sizeof(Employee), compEmployee);

    for (int i = 0; i < threadsNum; i++) {
        if (pthread_join(threadID[i], NULL) != 0) exit(1);
        free(part[i]);
    }

    printf("ghgh");

    mergeSortedEmployeeBases(base, 2, base + 2, 2);
    /*for (int i = 0; i < threadsNum; i++) {
        if()
        mergeSortedEmployeeBases(base)
    }*/

}