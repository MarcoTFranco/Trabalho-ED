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

    Employee(int dado0, char dado1[100], char dado2[100], char dado3[100], char dado4[100],
             char dado5[100], char dado6[100], char dado7[100], char dado8[100], char dado9[100]);

    ~Employee();

    void imprimirInformacoes();
};

#endif