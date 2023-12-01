#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>

using namespace std;

class Employee
{
private:
    int id;
    float lat, lng, zip;
    char desc[200], title[100],
        timeStamp[20], twp[100], addr[100];
    int e;

public:
    Employee();

    Employee(int dado0, float dado1, float dado2, const char *dado3, float dado4,
             const char *dado5, const char *dado6, const char *dado7, const char *dado8, int dado9);

    ~Employee();

    bool operator<(const Employee& other) const;

    int getId();

    void setTitle(const char *dado);

    void setTimeStamp(const char *dado);

    void imprimirInformacoes();
};

#endif