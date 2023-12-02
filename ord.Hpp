#ifndef ORD_HPP
#define ORD_HPP

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

struct pacote
{
    int indice;
    float lat, lng, zip;
    char desc[200], title[100], timeStamp[20], twp[100], addr[100];
    int e;
};

bool compararPacotes(const pacote &a, const pacote &b)
{
    return a.indice < b.indice;
}

void merge(pacote *vetor, int inicio, int meio, int fim)
{
    int i, j, k;
    int tam = fim - inicio + 1;
    pacote *aux = new pacote[tam];
    i = inicio;
    j = meio + 1;
    k = 0;
    while (i <= meio && j <= fim)
    {
        if (vetor[i].indice >= vetor[j].indice)
        {
            aux[k] = vetor[i];
            i++;
        }
        else
        {
            aux[k] = vetor[j];
            j++;
        }
        k++;
    }
    while (i <= meio)
    {
        aux[k] = vetor[i];
        i++;
        k++;
    }
    while (j <= fim)
    {
        aux[k] = vetor[j];
        j++;
        k++;
    }
    for (i = 0; i < tam; i++)
    {
        vetor[inicio + i] = aux[i];
    }
    delete[] aux;
}

void mergeSort(pacote *vetor, int inicio, int fim)
{

    if (inicio < fim)
    {
        int meio = (inicio + fim) / 2;
        mergeSort(vetor, inicio, meio);
        mergeSort(vetor, meio + 1, fim);
        merge(vetor, inicio, meio, fim);
    }
}

int lerArquivo(string fileName)
{
    /*
        Realiza a contagem de elementos nos arquivos
    */

    ifstream arquivo(fileName, ios::binary);
    pacote umPacote;
    int count = 0;
    while (arquivo.read((char *)&umPacote, sizeof(umPacote)))
    {
        count++;
    }

    arquivo.close();
    return count;
};

void criarArquivoSeparado(ifstream &arquivo)
{
    // Leitura do arquivo original
    pacote *vetor;
    int tamanho = lerArquivo("teste.bin");
    vetor = new pacote[tamanho];
    arquivo.seekg(0, ios::beg);
    arquivo.read((char *)vetor, sizeof(pacote) * tamanho);

    // Divisão do arquivo em dois arquivos de origem
    ofstream f1("f1.bin", ios::binary);
    ofstream f2("f2.bin", ios::binary);
    ofstream s1("s1.bin", ios::binary);
    ofstream s2("s2.bin", ios::binary);
    int tamanhoF1 = tamanho / 2;

    // Ordenação dos arquivos de origem
    mergeSort(vetor, 0, tamanho - 1);

    for (int i = 0; i < tamanho; i++)
    {
        if (i < tamanhoF1)
            f1.write((char *)&vetor[i], sizeof(pacote));
        else
            f2.write((char *)&vetor[i], sizeof(pacote));
    }
    f1.close();
    f2.close();

    delete[] vetor;
}

void intercalaArquivos(string entrada1Name, string entrada2Name, string saida1Name, string saida2Name, int tamanhoInicialBloco)
{
    ifstream entrada1(entrada1Name, ios::binary);
    ifstream entrada2(entrada2Name, ios::binary);
    ofstream saida1(saida1Name, ios::binary);
    ofstream saida2(saida2Name, ios::binary);

    pacote *vetor1 = new pacote[tamanhoInicialBloco];
    pacote *vetor2 = new pacote[tamanhoInicialBloco];

    pacote aux;

    int numeroDeBlocosMaximo = lerArquivo(entrada1Name) / tamanhoInicialBloco;
    cout << "Número de blocos máximo: " << numeroDeBlocosMaximo << endl;

    int contadorGeral = 0, posicaoArquivo = 0;
    bool inverte = false;

    while (!entrada2.eof() && !entrada1.eof())
    {

        entrada1.read((char *)vetor1, tamanhoInicialBloco * sizeof(pacote));
        int tamBlocoReal = entrada1.gcount() / sizeof(pacote);

        entrada2.read((char *)vetor2, tamanhoInicialBloco * sizeof(pacote));
        int tamBlocoReal2 = entrada2.gcount() / sizeof(pacote);

        mergeSort(vetor1, 0, tamBlocoReal - 1);
        mergeSort(vetor2, 0, tamBlocoReal - 1);

        if (!inverte and contadorGeral < numeroDeBlocosMaximo)
        {
            // salva o vetor no arquivo de saida
            saida1.write((char *)vetor1, sizeof(pacote) * tamBlocoReal);
            saida2.write((char *)vetor1, sizeof(pacote) * tamBlocoReal2);

            cout << "Intercalação inserido na saida 1: " << endl;
            cout << "Numero de pacotes: " << lerArquivo(saida1Name);
            cout << "Numero de pacotes: " << lerArquivo(saida2Name);
        }
        else if (inverte and contadorGeral < numeroDeBlocosMaximo)
        {
            saida1.write((char *)vetor2, sizeof(pacote) * tamBlocoReal);
            saida2.write((char *)vetor2, sizeof(pacote) * tamBlocoReal2);

            cout << "Intercalação inserido na saida 2: " << endl;
            cout << "Numero de pacotes: " << lerArquivo(saida1Name);
            cout << "Numero de pacotes: " << lerArquivo(saida2Name);
        }
        else if (contadorGeral == numeroDeBlocosMaximo)
        {
            saida1.write((char *)vetor1, sizeof(pacote) * tamBlocoReal);
            saida1.write((char *)vetor2, sizeof(pacote) * tamBlocoReal);

            cout << "Final do arquivo 2" << endl;
            cout << "Numero de pacotes: " << lerArquivo(saida1Name);
            cout << "Numero de pacotes: " << lerArquivo(saida2Name);
        }

        posicaoArquivo = entrada1.tellg(); // Obter a posição atual no arquivo
        inverte = !inverte;
        contadorGeral++;
    }

    entrada1.seekg(posicaoArquivo); // Voltar para a posição anterior no arquivo
    saida1.seekp(0, ios::end);      // Ir para o final do arquivo

    // Se o arquivo 2 terminou, copia o arquivo 1 para a saida 1
    while (!entrada1.eof() and contadorGeral < numeroDeBlocosMaximo)
    {
        cout << "entrou aqui" << endl;
        entrada1.read((char *)vetor1, tamanhoInicialBloco * sizeof(pacote));
        int tamBlocoReal = entrada1.gcount() / sizeof(pacote);

        saida1.write((char *)vetor1, sizeof(pacote) * tamBlocoReal);
        contadorGeral++;
    }

    entrada1.close();
    entrada2.close();
    saida1.close();
    saida2.close();

    delete[] vetor1; // Don't forget to free the allocated memory
    delete[] vetor2; // Don't forget to free the allocated memory

    // Remove os arquivos de entrada
    remove(entrada1Name.c_str());
    remove(entrada2Name.c_str());

    // Recria os arquivos de entrada
    ofstream f1(entrada1Name, ios::binary);
    ofstream f2(entrada2Name, ios::binary);
}

void mergeExterno(string input)
{
    string entrada1 = "f1.bin";
    string entrada2 = "f2.bin";
    string saida1 = "s1.bin";
    string saida2 = "s2.bin";

    int tamanhoInicial = 1000;
    bool inverte = false;
    int tamanhoMaximo = lerArquivo(input);
    cout << "Tamanho máximo: " << tamanhoMaximo << endl;

    // Chama a intercalação
    while (lerArquivo(saida1) == tamanhoMaximo and lerArquivo(saida1) == 0)
    {

        cout << "Tamanho da saida: " << lerArquivo(saida1) << endl;

        if (!inverte)
        {
            intercalaArquivos(entrada1, entrada2, saida1, saida2, tamanhoInicial);
        }
        else
        {
            intercalaArquivos(saida1, saida2, entrada1, entrada2, tamanhoInicial);
        }

        tamanhoInicial = tamanhoInicial * 2;

        inverte = !inverte;
    }

    // Remove os arquivos de entrada
    remove(entrada1.c_str());
    remove(entrada2.c_str());
    remove (saida2.c_str());
}

void principal(string input)
{
    ifstream arquivo_bin_read(input, ios::binary);
    criarArquivoSeparado(arquivo_bin_read);
    arquivo_bin_read.close();

    mergeExterno(input);

    ifstream f1("f1.bin", ios::binary);
    ifstream f2("f2.bin", ios::binary);
    ifstream s1("s1.bin", ios::binary);
    ifstream s2("s2.bin", ios::binary);

    if (f1.peek() != ifstream::traits_type::eof())
    {
        ifstream f1("f1.bin", ios::binary);
        f1.seekg(0, ios::end);
        int fileSize = f1.tellg();
        int numData = fileSize / sizeof(pacote);
        cout << "MAIN O arquivo f1.bin tem " << numData << " dados." << endl;
        f1.close();
    }
    else if (f2.peek() != ifstream::traits_type::eof())
    {
        ifstream f2("f2.bin", ios::binary);
        f2.seekg(0, ios::end);
        int fileSize = f2.tellg();
        int numData = fileSize / sizeof(pacote);
        cout << "MAIN O arquivo f2.bin tem " << numData << " dados." << endl;
        f2.close();
    }
    else if (s1.peek() != ifstream::traits_type::eof())
    {
        ifstream s1("s1.bin", ios::binary);
        s1.seekg(0, ios::end);
        int fileSize = s1.tellg();
        int numData = fileSize / sizeof(pacote);
        cout << "MAIN O arquivo s1.bin tem " << numData << " dados." << endl;
        s1.close();
    }
    else if (s2.peek() != ifstream::traits_type::eof())
    {
        ifstream s2("s2.bin", ios::binary);
        s2.seekg(0, ios::end);
        int fileSize = s2.tellg();
        int numData = fileSize / sizeof(pacote);
        cout << "MAIN O arquivo s2.bin tem " << numData << " dados." << endl;
        s2.close();
    }
    else
    {
        cout << "Nenhum arquivo tem dados." << endl;
    }

    f1.close();
    f2.close();
    s1.close();
    s2.close();
}

#endif