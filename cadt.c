#include <stdio.h>

#define MAX_LEN 100

typedef struct
{
    char data[MAX_LEN];
} String;

typedef struct
{
    int id;
    String name;
} Employee;

typedef struct
{
    int employee_id;
    int tasksDone;
} Report;

/*
    TODO: return the name of employee with highest tasksDone
*/
String getTopEmployeeName(Employee *employees, int empCount, Report *reports,
                          int reportCount)
{
    String result;
    result.data[0] = '\0'; // default empty string

    int max_task = 0;
    int id;
    for (int i = 0; i < reportCount; i++)
    {
        if (reports[i].tasksDone > max_task)
        {
            max_task = reports[i].tasksDone;
            id = reports[i].employee_id;
        }
    }

    for (int i = 0; i < empCount; i++)
    {
        if (id == employees[i].id)
        {
            return employees[i].name;
        }
    }
    return result;
}

int main()
{
    Employee employees[] = {{1, {"Alice"}}, {2, {"Bob"}}, {3, {"Charlie"}}, {4, {"Diana"}}, {5, {"Eve"}}, {6, {"Frank"}}};
    int empCount = 6;

    Report reports[] = {{1, 12}, {2, 25}, {3, 18}, {4, 25}, // same maximum as Bob
                        {5, 7},
                        {6, 20}};
    int reportCount = 6;

    String result =
        getTopEmployeeName(employees, empCount, reports, reportCount);

    printf("%s\n", result.data);

    return 0;
}