//
// Created by vladimir on 01.04.2022.
//
#include "report.h"

#include <stdlib.h>

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

void sortEmployeeBase(Employee* base, size_t n) {
    qsort(base, n, sizeof(Employee), compEmployee);
}

Report* makeReports(Employee* base, size_t n, size_t* reportsNum) {
    sortEmployeeBase(base, n);
    *reportsNum = 0;
    int employeeCount = 0;
    int totalSalary = 0;
    Report* reports = (Report*)malloc(sizeof(Report) * n); //TODO: динамическое выделение памяти;
    for (int i = 1;  i < n; i++) {
        totalSalary += base[i - 1].salary;
        employeeCount++;
        if (compEmployee(&(base[i - 1]), &(base[i])) != 0) {
            reports[*reportsNum].experience = base[i-1].experience;
            strcpy(reports[*reportsNum].position, base[i - 1].position);
            reports[*reportsNum].avgSalary = totalSalary / employeeCount;
            totalSalary = 0;
            employeeCount = 0;
            (*reportsNum)++;
        }
    }
    totalSalary += base[n - 1].salary;
    employeeCount++;
    reports[*reportsNum].experience = base[n - 1].experience;
    strcpy(reports[*reportsNum].position, base[n - 1].position);
    reports[*reportsNum].avgSalary = totalSalary / employeeCount;

    (*reportsNum)++;
    reports = (Report*)realloc(reports, sizeof(Report) * *reportsNum);

    return reports;
}

