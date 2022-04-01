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
    char* fName;
    char* sName;
    char field[FIELD_LEN];
    char position[POSITION_LEN];
    u_short age;
    u_short experience; // в месяцах
    int salary;
} Employee;

Employee* inputEmployee(FILE* file, Employee* form);
Employee* inputEmployeeBase(FILE* file, Employee* base, int n);
Employee* createEmployeeBase(FILE* file, int n);
void showEmployee(const Employee* employee);
void showEmployeeBase(const Employee* employeeBase, int n);


#endif //C1_FORM_H
