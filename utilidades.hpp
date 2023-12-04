#ifndef UTILIDADES_HPP
#define UTILIDADES_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Trabalhador.h"

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

// Função para pegar o id mais alto do arquivo binario
int idMaisAlto(string nomeDoArquivo)
{
    ifstream leitura(nomeDoArquivo, ios::binary);
    Trabalhador aux;
    int id = 0;
    while (leitura.read((char *)&aux, sizeof(Trabalhador)))
    {
        if (aux.getId() > id)
        {
            id = aux.getId();
        }
    }
    leitura.close();
    return id;
}

// Função para buscar a posição de um employee por id
int buscarPosicaoPorId(string nomeDoArquivo, int id)
{
    ifstream arquivo(nomeDoArquivo, ios::binary);

    if (!arquivo)
    {
        throw runtime_error("Erro ao abrir o arquivo.");
    }

    Trabalhador employee;
    int posicao = -1;
    int linha = 0;

    arquivo.seekg(0, ios::beg);
    while (arquivo.read((char *)&employee, sizeof(Trabalhador)))
    {
        if (employee.getId() == id)
        {
            posicao = linha;
            return posicao;
        }
        linha++;
    }

    arquivo.close();

    return posicao;
}

#endif