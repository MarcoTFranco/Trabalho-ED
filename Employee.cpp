#include <iostream>
#include <string>
#include <cstring>
#include <assert.h>

#include "Employee.h"

using namespace std;

Employee::Employee(int dado0, float dado1, float dado2, const char *dado3, float dado4,
                   const char *dado5, const char *dado6, const char *dado7, const char *dado8, int dado9)
{
    id = dado0;
    lat = dado1;
    lng = dado2;
    assert(strlen(dado3) < sizeof(desc));
    strcpy(desc, dado3);
    zip = dado4;
    assert(strlen(dado5) < sizeof(title));
    strcpy(title, dado5);
    assert(strlen(dado6) < sizeof(timeStamp));
    strcpy(timeStamp, dado6);
    assert(strlen(dado7) < sizeof(twp));
    strcpy(twp, dado7);
    assert(strlen(dado8) < sizeof(addr));
    strcpy(addr, dado8);
    e = dado9;
};

// Construtor padrao
Employee::Employee(){};

// Destrutor
Employee::~Employee(){};

// Metodos para pegar id;
int Employee::getId()
{
    return id;
}

bool Employee::operator<(const Employee &other) const
{
    return id < other.id;
}

// Metodo para mudar title;
void Employee::setTitle(const char *dado)
{
    assert(strlen(dado) < sizeof(title));
    strcpy(title, dado);
}

// Metodo para mudar timeStamp;
void Employee::setTimeStamp(const char *dado)
{
    assert(strlen(dado) < sizeof(timeStamp));
    strcpy(timeStamp, dado);
}

// Metodo para imprimir informacoes
void Employee::imprimirInformacoes()
{
    cout << "id: " << id << endl;
    cout << "lat: " << lat << endl;
    cout << "lng: " << lng << endl;
    cout << "desc: " << desc << endl;
    cout << "zip: " << zip << endl;
    cout << "title: " << title << endl;
    cout << "timeStamp: " << timeStamp << endl;
    cout << "twp: " << twp << endl;
    cout << "addr: " << addr << endl;
    cout << "e: " << e << endl;
};