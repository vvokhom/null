//
// Created by vladimir on 01.04.2022.
//

#ifndef C2_REPORT_H
#define C2_REPORT_H

#include "../data.h" //плохая зависимость?

typedef struct Report {
    char position[POSITION_LEN];
    int experience;
    int avgSalary;
} Report;

void sortEmployeeBase(Employee* base, size_t n);
Report* makeReports(Employee* base, size_t n, size_t* reportsNum);
void showReport(Report report);
void showReports(Report* report, size_t n);

#endif //C2_REPORT_H
