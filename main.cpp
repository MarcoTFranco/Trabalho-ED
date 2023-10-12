#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstring>
#include <assert.h>

#include "Employee.h"

using namespace std;

string removerExtensaoDaPalavra(string palavra, string extensao)
{
	// Encontrando a posição do ponto antes da extensão
	size_t pos = palavra.find(extensao);

	// Removendo a extensão .csv se encontrada
	if (pos != string::npos)
	{
		palavra = palavra.substr(0, pos);
	}

	return palavra;
}

void lerArquivoCSV(string nomeDoArquivo)
{
	ifstream arquivo(nomeDoArquivo);

	if (!arquivo.is_open())
	{
		cerr << "Erro ao abrir o arquivo." << endl;
		arquivo.close();
	}

	nomeDoArquivo = removerExtensaoDaPalavra(nomeDoArquivo, ".csv");

	ofstream gravaBinario(nomeDoArquivo + ".bin", ios::binary);
	string auxLinha;
	string auxColuna;
	string campos[10];
	Employee employee;
	int id;
	char lat[100], lng[100], desc[200], zip[100], title[100],
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

void inserir(string nomeDoArquivo)
{
	ofstream arquivo(nomeDoArquivo, ios::binary | ios::app);
	if (!arquivo)
	{
		cerr << "Erro ao abrir o arquivo." << endl;
	}

	int id;
	string lat, lng, desc, zip, title, timeStamp, twp, addr, e;

	cout << "Digite o identificador do employee: ";
	cin >> id;
	cin.ignore();
	cout << "Digite o lat do employee: ";
	getline(cin, lat);
	cout << "Digite o lng do employee: ";
	getline(cin, lng);
	cout << "Digite o desc do employee: ";
	getline(cin, desc);
	cout << "Digite o zip do employee: ";
	getline(cin, zip);
	cout << "Digite o title do employee: ";
	getline(cin, title);
	cout << "Digite o timeStamp do employee: ";
	getline(cin, timeStamp);
	cout << "Digite o twp do employee: ";
	getline(cin, twp);
	cout << "Digite o addr do employee: ";
	getline(cin, addr);
	cout << "Digite o e do employee: ";
	getline(cin, e);

	Employee employee(id, lat.c_str(), lng.c_str(), desc.c_str(), zip.c_str(), title.c_str(), timeStamp.c_str(), twp.c_str(), addr.c_str(), e.c_str());

	bool existe = false;
	ifstream leitura(nomeDoArquivo, ios::binary);
	Employee aux;
	while (leitura.read((char *)&aux, sizeof(Employee)))
	{
		if (aux.getId() == id)
		{
			existe = true;
		}
	}
	leitura.close();

	if (existe)
	{
		cout << "O id ja existe!" << endl;
	}
	else
	{
		arquivo.write(reinterpret_cast<char *>(&employee), sizeof(Employee));
	}

	arquivo.close();
}

void trocarRegistros(string nomeDoArquivo)
{
	int posicao1, posicao2;

	cout << "Digite a posicao do primeiro registro: ";
	cin >> posicao1;
	cout << "Digite a posicao do segundo registro: ";
	cin >> posicao2;

	fstream arquivo(nomeDoArquivo, ios::binary | ios::in | ios::out);

	if (!arquivo)
	{
		cerr << "Erro ao abrir o arquivo." << endl;
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

void imprimirTrecho(string nomeDoArquivo)
{
	int comeco, fim;

	cout << "Digite o numero da linha inicial: ";
	cin >> comeco;
	cout << "Digite o numero da linha final: ";
	cin >> fim;

	ifstream arquivo(nomeDoArquivo, ios::binary);
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

void editar(string nomeDoArquivo)
{
	fstream arquivo(nomeDoArquivo, ios::binary | ios::in | ios::out);
	if (!arquivo)
	{
		cerr << "Erro ao abrir o arquivo." << endl;
	}

	int id;
	cout << "Digite o id do employee que deseja alterar: ";
	cin >> id;

	Employee employee;

	char title[100], timeStamp[100];
	string titleS, timeStampS;

	while (arquivo.read(reinterpret_cast<char *>(&employee), sizeof(Employee)))
	{
		if (employee.getId() == id)
		{

			cin.ignore();
			cout << "Digite o novo title: ";
			getline(cin, titleS);

			cout << "Digite o novo timeStamp (yy-mm-dd hh:mm:ss): ";
			getline(cin, timeStampS);

			assert(titleS.length() < sizeof(title));
			strcpy(title, titleS.c_str());
			assert(timeStampS.length() < sizeof(timeStamp));
			strcpy(timeStamp, timeStampS.c_str());

			employee.setTitle(title);
			employee.setTimeStamp(timeStamp);

			int pos = arquivo.tellg();
			arquivo.seekp(pos - sizeof(Employee));
			arquivo.write(reinterpret_cast<char *>(&employee), sizeof(Employee));
			cout << "Dados atualizados com sucesso." << endl;
			employee.imprimirInformacoes();
		}
	}

	arquivo.close();
}

void imprimeTudo(string nomeDoArquivo)
{
	ifstream leitura(nomeDoArquivo, ios::binary);

	if (!leitura.is_open())
	{
		cerr << "Erro ao abrir o arquivo." << endl;
		leitura.close();
	}

	Employee data;
	leitura.seekg(0, ios::beg);
	while (leitura.read(reinterpret_cast<char *>(&data), sizeof(Employee)))
	{
		data.imprimirInformacoes();
	}
	leitura.close();
}

void menu_principal(string nomeDoArquivo)
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
			 << "  4 - Editar dados" << endl
			 << "  5 - Imprimir tudo" << endl
			 << "  6 - Sair" << endl
			 << "Digite sua escolha: ";
		cin >> escolha;
		switch (escolha)
		{
		case 1:
			cout << endl;
			inserir(nomeDoArquivo);
			break;
		case 2:
			cout << endl;
			imprimirTrecho(nomeDoArquivo);
			break;
		case 3:
			cout << endl;
			trocarRegistros(nomeDoArquivo);
			break;
		case 4:
			cout << endl;
			editar(nomeDoArquivo);
			break;
		case 5:
			cout << endl;
			imprimeTudo(nomeDoArquivo);
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

	string nomeDoArquivo;

	cout << "Digite o nome do arquivo: ";
	cin >> nomeDoArquivo;
	cout << endl;

	ifstream leitura(nomeDoArquivo);

	if (!leitura.is_open())
	{
		cout << "Erro ao abrir o arquivo." << endl;
		leitura.close();
	}
	else
	{
		lerArquivoCSV(nomeDoArquivo);

		string novoNome = removerExtensaoDaPalavra(nomeDoArquivo, ".csv") + ".bin";

		menu_principal(novoNome);
	}

	return 0;
}