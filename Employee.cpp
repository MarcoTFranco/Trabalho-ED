#include <iostream>
#include <string>
#include <cstring>
#include <assert.h>

#include "Employee.h"

using namespace std;

Employee::Employee(int dado0, char dado1[100], char dado2[100], char dado3[100], char dado4[100],
                   char dado5[100], char dado6[100], char dado7[100], char dado8[100], char dado9[100])
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

Employee::Employee(){};

Employee::~Employee(){};

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