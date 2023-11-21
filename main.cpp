/*
 *
 * Participantes do grupo:
 * Marco Túlio Franco Silva
 * Pedro Henrique Souza Perazza Martins
 *
 */

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstring>
#include <assert.h>

#include "Employee.h"

using namespace std;

// Função para remover extensao de uma palavra
string removerExtensaoDaPalavra(string palavra, string extensao)
{
	size_t pos = palavra.find(extensao);

	if (pos != string::npos)
	{
		palavra = palavra.substr(0, pos);
	}

	return palavra;
}

// Função para verificar se um id existe no arquivo binario
bool existeId(string nomeDoArquivo, int id)
{
	ifstream leitura(nomeDoArquivo, ios::binary);
	Employee aux;
	while (leitura.read((char *)&aux, sizeof(Employee)))
	{
		if (aux.getId() == id)
		{
			return true;
		}
	}
	leitura.close();
	return false;
}

// Função para pegar os dados de um employee , assim separando leitura de dados com regra de negócio
Employee lerDadosDoEmployee()
{
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
	return employee;
}

// Função para ler uma posição, assim separando leitura de dados com regra de negócio
int lerPosicao(string esperando)
{
	int posicao;
	cout << "Digite a posicao onde deseja " << esperando << ": ";
	cin >> posicao;
	return posicao;
}

// Função para ler um arquivo CSV e gravar em um arquivo binario
void lerArquivoCSV(string nomeDoArquivo)
{
	ifstream arquivo(nomeDoArquivo);

	if (!arquivo.is_open())
	{
		throw runtime_error("Erro ao abrir o arquivo.");
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

// Função para inserir um novo registro no arquivo binario
void inserir(string nomeDoArquivo)
{
	ofstream arquivo(nomeDoArquivo, ios::binary | ios::app);
	if (!arquivo)
	{
		throw runtime_error("Erro ao abrir o arquivo.");
	}

	Employee employee(lerDadosDoEmployee());

	bool existe = existeId(nomeDoArquivo, employee.getId());
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

// Função para inserir um novo registro em uma determinada posição, mandando todos os outros para baixo
void inserirNaPosicao(string nomeDoArquivo)
{
	fstream arquivo(nomeDoArquivo, ios::binary | ios::in | ios::out);

	if (!arquivo)
	{
		throw runtime_error("Erro ao abrir o arquivo.");
	}

	// Verificar se a posição é válida
	int posicao, numRegistros;
	do
	{
		posicao = lerPosicao("inserir");

		if (posicao < 0)
		{
			cout << "Posição invalida. Digite valor não negativo." << endl;
		}
		else
		{
			arquivo.seekg(0, ios::end);
			numRegistros = arquivo.tellg() / sizeof(Employee);

			if (posicao >= numRegistros)
			{
				cout << "Posição invalida. Digite valor dentro do intervalo [0, " << numRegistros - 1 << "]." << endl;
			}
			else
			{
				break;
			}
		}
	} while (true);

	Employee novoRegistro(lerDadosDoEmployee());

	// Verificar se o id já existe
	bool existe = existeId(nomeDoArquivo, novoRegistro.getId());
	if (existe)
	{
		cout << "O id ja existe!" << endl;
	}
	else
	{
		// Ler o registro existente na posição especificada
		Employee registroExistente;
		arquivo.seekg(posicao * sizeof(Employee));
		arquivo.read(reinterpret_cast<char *>(&registroExistente), sizeof(Employee));

		// Deslocar os registros restantes para baixo
		for (int i = numRegistros - 1; i >= posicao; i--)
		{
			Employee registroAnterior;
			arquivo.seekg(i * sizeof(Employee));
			arquivo.read(reinterpret_cast<char *>(&registroAnterior), sizeof(Employee));

			arquivo.seekp((i + 1) * sizeof(Employee));
			arquivo.write(reinterpret_cast<char *>(&registroAnterior), sizeof(Employee));
		}

		// Escrever o novo registro na posição especificada
		arquivo.seekp(posicao * sizeof(Employee));
		arquivo.write(reinterpret_cast<char *>(&novoRegistro), sizeof(Employee));
	}

	arquivo.close();
}

// Função para trocar dois registros de posicao
void trocarRegistros(string nomeDoArquivo)
{

	fstream arquivo(nomeDoArquivo, ios::binary | ios::in | ios::out);

	if (!arquivo)
	{
		throw runtime_error("Erro ao abrir o arquivo.");
	}

	int posicao1, posicao2;

	do
	{
		posicao1 = lerPosicao("trocar o registro n. º1");
		posicao2 = lerPosicao("trocar o registro n. º2");

		if (posicao1 < 0 || posicao2 < 0)
		{
			cout << "Posicoes invalidas. Digite valores não negativos." << endl;
		}
		else
		{
			arquivo.seekg(0, ios::end);
			int numRegistros = arquivo.tellg() / sizeof(Employee);

			if (posicao1 >= numRegistros || posicao2 >= numRegistros)
			{
				cout << "Posicoes invalidas. Digite valores dentro do intervalo [0, " << numRegistros - 1 << "]." << endl;
			}
			else
			{
				break;
			}
		}
	} while (true);

	Employee registro1, registro2;

	arquivo.seekg(posicao1 * sizeof(Employee));
	arquivo.read(reinterpret_cast<char *>(&registro1), sizeof(Employee));

	arquivo.seekg(posicao2 * sizeof(Employee));
	arquivo.read(reinterpret_cast<char *>(&registro2), sizeof(Employee));

	arquivo.seekp(posicao1 * sizeof(Employee));
	arquivo.write(reinterpret_cast<char *>(&registro2), sizeof(Employee));

	arquivo.seekp(posicao2 * sizeof(Employee));
	arquivo.write(reinterpret_cast<char *>(&registro1), sizeof(Employee));

	arquivo.close();
}

// Função para imprimir um trecho do arquivo binario
void imprimirTrecho(string nomeDoArquivo)
{

	ifstream arquivo(nomeDoArquivo, ios::binary);

	if (!arquivo)
	{
		throw runtime_error("Erro ao abrir o arquivo.");
		
	}

	Employee employee;

	arquivo.seekg(0, ios::end);
	int numRegistros = arquivo.tellg() / sizeof(Employee);
	cout << "Digite valores dentro do intervalo [0, " << numRegistros - 1 << "]." << endl;

	int comeco, fim;

	comeco = lerPosicao("começar a imprimir o trecho");
	fim = lerPosicao("que seja o fim do trecho");

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

// Função para editar um registro
void editar(string nomeDoArquivo)
{
	fstream arquivo(nomeDoArquivo, ios::binary | ios::in | ios::out);
	if (!arquivo)
	{
		throw runtime_error("Erro ao abrir o arquivo.");
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

// Função para imprimir todos os registros do arquivo binario
void imprimeTudo(string nomeDoArquivo)
{
	ifstream leitura(nomeDoArquivo, ios::binary);

	if (!leitura.is_open())
	{
		throw runtime_error("Erro ao abrir o arquivo.");
	}

	Employee data;
	leitura.seekg(0, ios::beg);
	while (leitura.read(reinterpret_cast<char *>(&data), sizeof(Employee)))
	{
		data.imprimirInformacoes();
	}
	leitura.close();
}

// Função para imprimir o menu principal
void menuPrincipal(string nomeDoArquivo)
{
	int escolha;
	bool loop = true;
	while (loop)
	{
		cout << endl;
		cout << "Escolha uma opcao:" << endl
			 << "  1 - Inserir" << endl
			 << "  2 - Inserir na posição" << endl
			 << "  3 - Visualizar um trecho" << endl
			 << "  4 - Trocar dois registros" << endl
			 << "  5 - Editar dados" << endl
			 << "  6 - Imprimir tudo" << endl
			 << "  7 - Sair" << endl
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
			inserirNaPosicao(nomeDoArquivo);
			break;
		case 3:
			cout << endl;
			imprimirTrecho(nomeDoArquivo);
			break;
		case 4:
			cout << endl;
			trocarRegistros(nomeDoArquivo);
			break;
		case 5:
			cout << endl;
			editar(nomeDoArquivo);
			break;
		case 6:
			cout << endl;
			imprimeTudo(nomeDoArquivo);
			break;
		case 7:
			cout << endl;
			cout << "Saindo..." << endl;
			loop = false;
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
		throw runtime_error("Erro ao abrir o arquivo.");
	}
	else
	{
		lerArquivoCSV(nomeDoArquivo);

		string novoNome = removerExtensaoDaPalavra(nomeDoArquivo, ".csv") + ".bin";

		menuPrincipal(novoNome);
	}

	return 0;
}