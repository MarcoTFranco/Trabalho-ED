#include <iostream>
#include <string>
#include <cstring>
#include <assert.h>

#include "Employee.h"

using namespace std;

Employee::Employee(int dado0, const char *dado1, const char *dado2, const char *dado3, const char *dado4,
                   const char *dado5, const char *dado6, const char *dado7, const char *dado8, const char *dado9)
{
    id = dado0;
    assert(strlen(dado1) < sizeof(lat));
    strcpy(lat, dado1);
    assert(strlen(dado2) < sizeof(lng));
    strcpy(lng, dado2);
    assert(strlen(dado3) < sizeof(desc));
    strcpy(desc, dado3);
    assert(strlen(dado4) < sizeof(zip));
    strcpy(zip, dado4);
    assert(strlen(dado5) < sizeof(title));
    strcpy(title, dado5);
    assert(strlen(dado6) < sizeof(timeStamp));
    strcpy(timeStamp, dado6);
    assert(strlen(dado7) < sizeof(twp));
    strcpy(twp, dado7);
    assert(strlen(dado8) < sizeof(addr));
    strcpy(addr, dado8);
    assert(strlen(dado9) < sizeof(e));
    strcpy(e, dado9);
};

//Construtor padrao
Employee::Employee(){};

//Destrutor
Employee::~Employee(){};

//Metodos para pegar id;
int Employee::getId()
{
    return id;
}

//Metodo para mudar title;
void Employee::setTitle(const char *dado)
{
    assert(strlen(dado) < sizeof(title));
    strcpy(title, dado);
}

//Metodo para mudar timeStamp;
void Employee::setTimeStamp(const char *dado)
{
    assert(strlen(dado) < sizeof(timeStamp));
    strcpy(timeStamp, dado);
}

//Metodo para imprimir informacoes
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