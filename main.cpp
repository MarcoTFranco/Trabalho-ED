#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstring>
#include <assert.h>

#include "Employee.h"

using namespace std;

void lerArquivoCSV()
{
	ifstream arquivo("call911_2_teste.csv");
	ofstream gravaBinario("call911_2_teste.bin", ios::binary);
	string auxLinha;
	string auxColuna;
	string campos[10];
	Employee employee;
	int id;
	char lat[100], lng[100], desc[100], zip[100], title[100],
		timeStamp[100], twp[100], addr[100], e[100];

	getline(arquivo, auxLinha);
	while (getline(arquivo, auxLinha))
	{
		stringstream lendo(auxLinha);
		int i = 0;
		while (getline(lendo, auxColuna, ',') && i < 10)
		{
			campos[i] = auxColuna;
			i++;
		}

		Employee employee;
		stringstream streamId(campos[0]);
		streamId >> id;
		assert(campos[1].length() < sizeof(lat));
		strcpy(lat, campos[1].c_str());
		assert(campos[2].length() < sizeof(lng));
		strcpy(lng, campos[2].c_str());
		assert(campos[3].length() < sizeof(desc));
		strcpy(desc, campos[3].c_str());
		assert(campos[4].length() < sizeof(zip));
		strcpy(zip, campos[4].c_str());
		assert(campos[5].length() < sizeof(title));
		strcpy(title, campos[5].c_str());
		assert(campos[6].length() < sizeof(timeStamp));
		strcpy(timeStamp, campos[6].c_str());
		assert(campos[7].length() < sizeof(twp));
		strcpy(twp, campos[7].c_str());
		assert(campos[8].length() < sizeof(addr));
		strcpy(addr, campos[8].c_str());
		assert(campos[9].length() < sizeof(e));
		strcpy(e, campos[9].c_str());
		employee = Employee(id, lat, lng, desc, zip, title, timeStamp, twp, addr, e);
		gravaBinario.write(reinterpret_cast<char *>(&employee), sizeof(Employee));
	}

	arquivo.close();
	gravaBinario.close();
}

void inserir()
{
	ofstream arquivo("call911_2_teste.bin", ios::binary | ios::app);
	if (!arquivo)
	{
		cout << "Erro ao abrir o arquivo." << endl;
	}

	int id;
	string lat, lng, desc, zip, title, timeStamp, twp, addr, e;

	cout << "Digite o identificador do employee" << endl;
	cin >> id;
	cin.ignore();
	cout << "Digite o lat do employee" << endl;
	getline(cin, lat);
	cout << "Digite o lng do employee" << endl;
	getline(cin, lng);
	cout << "Digite o desc do employee" << endl;
	getline(cin, desc);
	cout << "Digite o zip do employee" << endl;
	getline(cin, zip);
	cout << "Digite o title do employee" << endl;
	getline(cin, title);
	cout << "Digite o timeStamp do employee" << endl;
	getline(cin, timeStamp);
	cout << "Digite o twp do employee" << endl;
	getline(cin, twp);
	cout << "Digite o addr do employee" << endl;
	getline(cin, addr);
	cout << "Digite o e do employee" << endl;
	getline(cin, e);

	Employee employee(id, lat.c_str(), lng.c_str(), desc.c_str(), zip.c_str(), title.c_str(), timeStamp.c_str(), twp.c_str(), addr.c_str(), e.c_str());

	arquivo.write(reinterpret_cast<char *>(&employee), sizeof(Employee));
	arquivo.close();
}

void trocarRegistros()
{
	int posicao1, posicao2;

	cout << "Digite a posição do primeiro registro: ";
	cin >> posicao1;
	cout << "Digite a posição do segundo registro: ";
	cin >> posicao2;

	fstream arquivo("call911_2_teste.bin", ios::binary | ios::in | ios::out);

	if (!arquivo)
	{
		cout << "Erro ao abrir o arquivo." << endl;
		return;
	}

	Employee registro1, registro2;

	// Ler o primeiro registro
	arquivo.seekg(posicao1 * sizeof(Employee));
	arquivo.read(reinterpret_cast<char *>(&registro1), sizeof(Employee));

	// Ler o segundo registro
	arquivo.seekg(posicao2 * sizeof(Employee));
	arquivo.read(reinterpret_cast<char *>(&registro2), sizeof(Employee));

	// Voltar para a posição do primeiro registro e escrever o segundo registro
	arquivo.seekp(posicao1 * sizeof(Employee));
	arquivo.write(reinterpret_cast<char *>(&registro2), sizeof(Employee));

	// Voltar para a posição do segundo registro e escrever o primeiro registro
	arquivo.seekp(posicao2 * sizeof(Employee));
	arquivo.write(reinterpret_cast<char *>(&registro1), sizeof(Employee));

	arquivo.close();
}
void imprimirTrecho()
{
	int comeco, fim;

	cout << "Digite o numero da linha inicial: ";
	cin >> comeco;
	cout << "Digite o numero da linha final: ";
	cin >> fim;

	ifstream arquivo("call911_2_teste.bin", ios::binary);
	Employee employee;

	int linha = 0;
	arquivo.seekg(0, ios::beg);
	while (arquivo.read((char *)&employee, sizeof(Employee)))
	{
		if (linha >= comeco and linha <= fim)
		{
			employee.imprimirInformacoes();
		}
		linha++;
	}

	arquivo.close();
}

void imprimeTudo()
{
	ifstream leitura1("call911_2_teste.bin", ios::binary);
	Employee data;
	leitura1.seekg(0, ios::beg);
	while (leitura1.read(reinterpret_cast<char *>(&data), sizeof(Employee)))
	{
		data.imprimirInformacoes();
	}
	leitura1.close();
}

void menu_principal()
{
	int escolha;
	bool loop = true;
	while (loop)
	{
		cout << endl;
		cout << "Escolha uma opcao:" << endl
			 << "  1 - Inserir" << endl
			 << "  2 - Visualizar um trecho" << endl
			 << "  3 - Trocar dois registros" << endl
			 << "  4 - Alterar" << endl
			 << "  5 - Imprimir tudo" << endl
			 << "  6 - Sair" << endl
			 << "Digite sua escolha: ";
		cin >> escolha;
		switch (escolha)
		{
		case 1:
			cout << endl;
			inserir();
			break;
		case 2:
			cout << endl;
			imprimirTrecho();
			break;
		case 3:
			cout << endl;
			trocarRegistros();
			break;
		case 4:
			cout << endl;
			//Função
			break;
		case 5:
			cout << endl;
			imprimeTudo();
			break;
		case 6:
			cout << endl;
			cout << "Saindo..." << endl;
			loop = false; // Definir ward como false para sair do loop
			break;

		default:
			cout << "OPCAO INVALIDA!!!" << endl;
			break;
		}
	}
}

int main()
{
	ifstream leitura("call911_2_teste.csv");

	if (!leitura.is_open())
	{
		cout << "Erro ao abrir o arquivo." << endl;
		leitura.close();
	}
	else
	{
		lerArquivoCSV();
	}

	menu_principal();

	return 0;
}