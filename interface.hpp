#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <iostream>
#include <string>

using namespace std;

#include "utilidades.hpp"
#include "Trabalhador.h"

// Função para imprimir o painel de editar
void painelEditar(int &id, string &titleS, string &timeStampS)
{

	cout << "Digite o id do employee que deseja alterar: ";
	cin >> id;

	cin.ignore();

	cout << "Digite o novo title: ";
	getline(cin, titleS);

	cout << "Digite o novo timeStamp (yy-mm-dd hh:mm:ss): ";
	getline(cin, timeStampS);
}

// Função para imprimir o painel de ImprimirTrecho
void painelImprimirTrecho(int numRegistros, int &comeco, int &fim)
{
	cout << "Digite valores dentro do intervalo [0, " << numRegistros - 1 << "]." << endl;
	cout << "Digite o comeco do trecho: ";
	cin >> comeco;
	cout << "Digite o fim do trecho: ";
	cin >> fim;
}

// Painel para InserirNaPosicao
void painelInserirNaPosicao(int &posicao)
{
	cout << "Digite a posicao onde deseja inserir: ";
	cin >> posicao;
}

// Função para pegar os dados de um employee
Trabalhador lerDadosDoEmployee(string nomeDoArquivo)
{
	int id, e;
	float lat, lng, zip;
	string desc, title, timeStamp, twp, addr;

	id = idMaisAlto(nomeDoArquivo) + 1;
	cout << "Digite o lat do employee (40.299): ";
	cin >> lat;
	cout << "Digite o lng do employee (-75.5835): ";
	cin >> lng;
	cin.ignore();
	cout << "Digite o desc do employee (REINDEER CT & DEAD END): ";
	getline(cin, desc);
	cout << "Digite o zip do employee (19525.0): ";
	cin >> zip;
	cin.ignore();
	cout << "Digite o title do employee (EMS: BACK PAINS/INJURY): ";
	getline(cin, title);
	cout << "Digite o timeStamp do employee (yy-mm-dd hh:mm:ss): ";
	getline(cin, timeStamp);
	cout << "Digite o twp do employee (LOWER POTTSGROVE): ";
	getline(cin, twp);
	cout << "Digite o addr do employee (CHERRYWOOD CT & DEAD END): ";
	getline(cin, addr);

	Trabalhador employee(id, lat, lng, desc.c_str(), zip,
						 title.c_str(), timeStamp.c_str(), twp.c_str(), addr.c_str(), 1);
	return employee;
}

// Função para imprimir o painel de TrocarRegistros
void painelTrocarRegistros(int &posicao1, int &posicao2)
{
	cout << "Digite a posicao do primeiro registro: ";
	cin >> posicao1;
	cout << "Digite a posicao do segundo registro: ";
	cin >> posicao2;
}

#endif