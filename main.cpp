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

void menu_principal()
{
	int escolha, busca;
	bool loop = true;
	while (loop)
	{
		cout << endl;
		cout << "Escolha uma opcao:" << endl
			 << "  1 - Inserir" << endl
			 << "  2 - Visualizar um trecho" << endl
			 << "  3 - Alterar" << endl
			 << "  4 - Trocar dois registros" << endl
			 << "  5 - Imprimir tudo" << endl
			 << "  6 - Sair" << endl
			 << "Digite sua escolha: ";
		cin >> escolha;
		switch (escolha)
		{
		case 1:
			cout << endl;
			break;
		case 2:
			cout << endl;
			cout << "Escolha uma opcao:" << endl
				 << "  1 - Buscar todos " << endl
				 << "  2 - ID " << endl
				 << "  3 - Nome " << endl
				 << "  4 - Estilo " << endl
				 << "  5 - Ano de Nascimento " << endl
				 << "  6 - Busca por intervalo " << endl
				 << "Digite sua escolha: ";
			cin >> busca;
			switch (busca)
			{
			case 1:
				cout << endl;
				cout << "Todos encontrados: " << endl;
				cout << endl;
				break;
			case 2:
				cout << endl;
				cout << "Busca por ID: ";
				cout << "Diga-me o ID que quer procurar?";
				cout << endl
					 << "--> ";
				cout << endl;
				break;
			case 3:
				cout << endl;
				cout << "Busca por nome: " << endl;
				cout << "Diga-me o nome que quer procurar?";
				cout << endl
					 << "--> ";
				cout << endl;
				break;
			case 4:
				cout << endl;
				cout << "Busca por estilo musical: " << endl;
				cout << "Diga-me o estilo do compositor que você deseja?";
				cout << endl
					 << "--> ";
				cout << endl;
				break;
			case 5:
				cout << endl;
				cout << "Busca por ano de nascimento: " << endl;
				cout << "Diga-me o ano de nascimento do compositor que você deseja?";
				cout << endl
					 << "--> ";
				cout << endl;
				break;
			case 6:
				cout << endl;
				cout << "Busca por intervalo: " << endl;
				cout << "Diga-me o inicio e o fim do interlavo que você deseja?";
				cout << endl;
				break;
			}
			break;
		case 3:
			cout << endl;
			cout << "Insira o ID do compositor que deseja editar: ";
			break;
		case 4:
			cout << endl;
			cout << "Coloque o ID do compositor que deseja excluir: ";
			break;
		case 5:
			cout << endl;
			cout << "Exportando..." << endl;
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
	ifstream leitura ("call911_2_teste.csv");
 
    if (!leitura.is_open()){
        cout <<"Erro ao abrir o arquivo." <<endl;
        leitura.close();
    } else{
		lerArquivoCSV();
	}

	menu_principal();

	return 0;
}

//GIT é muito complexo pro meu gosto!