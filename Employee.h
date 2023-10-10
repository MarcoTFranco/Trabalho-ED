#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>

using namespace std;

class Employee
{
private:
    int id;
    char lat[100], lng[100], desc[100], zip[100], title[100],
        timeStamp[100], twp[100], addr[100], e[100];

public:
    Employee();

    Employee(int dado0, const char * dado1, const char * dado2, const char * dado3, const char * dado4,
             const char * dado5, const char * dado6, const char * dado7, const char * dado8, const char * dado9);

    ~Employee();

    void imprimirInformacoes();
};

#endif