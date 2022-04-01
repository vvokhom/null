//
// Created by vladimir on 01.04.2022.
//
#include "report.h"

void showReport(Report report){
    printf("[\nДолжность: %s\nСтаж: %i\nЗарплата: %i Р/Мес\n]\n",
           report.position, report.experience, report.avgSalary);
}

void showReports(Report* report, size_t n) {
    printf("Отчет:\n");
    for (int i = 0; i < n; i++) {
        showReport(report[i]);
    }
}

