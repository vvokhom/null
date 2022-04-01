//
// Created by vladimir on 11.03.2022.
//
#include "data.h"

Employee* inputEmployee(FILE* file, Employee* employee) {

    /*employee->fName = createString(file);

    employee->sName = createString(file);

    inputString(file, employee->field, FIELD_LEN);*/
    sprintf(employee->field, "Account");
  employee->fName = "Bob";
    employee->sName = "Bebs";
    inputString(file, employee->position, POSITION_LEN);

    //employee->age = inputShortInt(file);
employee->age = 10;
    employee->experience = inputShortInt(file);

    employee->salary = inputInt(file);

    return employee;
}
Employee* inputEmployeeBase(FILE* file, Employee* base, size_t n) {
    for (int i = 0; i < n; i++) {
        inputEmployee(file, &(base[i]));
    }
    return base;
}
struct Employee* createEmployeeBase(FILE* file, size_t n){
    Employee* base = (Employee*)malloc(sizeof(Employee) * n);
    inputEmployeeBase(file, base, n);
    return base;
}
void showEmployee(const Employee* employee) {
    printf("[\nФИ: %s %s\nДолжность: %s, %s\nВозраст: %i лет\nСтаж: %i лет\nЗарплата: %i Р/Мес\n]\n",
           employee->fName, employee->sName, employee->position, employee->field, employee->age, employee->experience, employee->salary);
}
void showEmployeeBase(const Employee* employeeBase, size_t n) {
    for (int i = 0; i < n; i++) {
        showEmployee(&(employeeBase[i]));
    }
}