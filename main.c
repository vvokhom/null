

#include "report/report.h"

int main() {
    Employee* base;
    int n = inputInt(stdin);
    base = createEmployeeBase(stdin, n);
    showEmployeeBase(base, n);
    sortEmployeeBase(base, n);
    showEmployeeBase(base, n);
    //size_t reportsNum;
    //Report* reports = makeReports(base, n, &reportsNum);
    //showReports(reports, reportsNum);
    //free(reports);
    free(base);
    return 0;


}

