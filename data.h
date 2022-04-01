//
// Created by vladimir on 11.03.2022.
//

#ifndef C2_DATA_H
#define C2_DATA_H

#include <assert.h>

#include "input.h"

#define FIELD_LEN 8
#define POSITION_LEN 8

typedef struct Employee { // 40 байт, без лакун
    char* fName;// Неоптимально по скорости; но я полагаю что обращения по имени/фамилии будут редки
    char* sName;
    char field[FIELD_LEN];
    char position[POSITION_LEN];
    u_short age;
    u_short experience;
    int salary;
} Employee;

Employee* inputEmployee(FILE* file, Employee* form);
Employee* inputEmployeeBase(FILE* file, Employee* base, size_t n);
Employee* createEmployeeBase(FILE* file, size_t n);
void showEmployee(const Employee* employee);
void showEmployeeBase(const Employee* employeeBase, size_t n);


#endif //C2_DATA_H
