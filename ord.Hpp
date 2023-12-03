#ifndef ORD_HPP
#define ORD_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

#define N 100

struct Trabalhador
{
    int id;
    float lat, lng, zip;
    char desc[200], title[100],
        timeStamp[20], twp[100], addr[100];
    int e;

    bool operator<(const Trabalhador &t) const
    {
        return id < t.id;
    }
};

struct Arquivo
{
    std::ifstream *f;
    int pos, MAX;
    Trabalhador *buffer;
};

void salvaArquivo(const char *nome, Trabalhador *V, int tam)
{
    std::ofstream f(nome, std::ios::binary | std::ios::app);
    f.write(reinterpret_cast<const char *>(V), tam * sizeof(Trabalhador));
    f.close();
}

int comparaTrabalhadores(const void *a, const void *b)
{
    return (*(Trabalhador *)a < *(Trabalhador *)b) ? -1 : 1;
}

int criaArquivosOrdenados(const char *nome)
{
    Trabalhador V[N];
    char novo[20];
    int cont = 0, total = 0;
    std::ifstream f(nome, std::ios::binary);
    while (!f.eof())
    {
        f.read(reinterpret_cast<char *>(V), N * sizeof(Trabalhador));
        total = f.gcount() / sizeof(Trabalhador);

        if (total > 0)
        {
            cont++;
            sprintf(novo, "Temp%d.bin", cont);
            std::qsort(V, total, sizeof(Trabalhador), comparaTrabalhadores);
            salvaArquivo(novo, V, total);
        }
    }
    f.close();
    return cont;
}

void preencheBuffer(Arquivo *arq, int T)
{
    int i;

    if (arq->f == nullptr)
        return;

    arq->pos = 0;
    arq->MAX = 0;

    for (i = 0; i < T; i++)
    {
        if (!arq->f->eof())
        {
            arq->f->read(reinterpret_cast<char *>(&arq->buffer[arq->MAX]), sizeof(Trabalhador));
            arq->MAX++;
        }
        else
        {
            arq->f->close();
            arq->f = nullptr;
            break;
        }
    }
}

int procuraMenor(Arquivo *arq, int K, int T, Trabalhador *menor)
{
    int i, idx = -1;
    for (int i = 0; i < K; i++)
    {
        if (arq[i].pos < arq[i].MAX)
        {
            if (idx == -1)
                idx = i;
            else
            {
                if (arq[i].buffer[arq[i].pos] < arq[idx].buffer[arq[idx].pos])
                    idx = i;
            }
        }
    }
    if (idx != -1)
    {
        *menor = arq[idx].buffer[arq[idx].pos];
        arq[idx].pos++;
        if (arq[idx].pos == arq[idx].MAX)
            preencheBuffer(&arq[idx], T);
        return 1;
    }
    else
    {
        return 0;
    }
}

void merge(const char *nome, int K, int T)
{
    char novo[20];
    int i;
    Trabalhador *buffer = new Trabalhador[T];

    Arquivo *arq;
    arq = new Arquivo[K];

    for (i = 0; i < K; i++)
    {
        sprintf(novo, "Temp%d.bin", i + 1);
        arq[i].f = new std::ifstream(novo, std::ios::binary);
        arq[i].MAX = 0;
        arq[i].pos = 0;
        arq[i].buffer = new Trabalhador[T];
        preencheBuffer(&arq[i], T);
    }

    Trabalhador menor;
    int qtdBuffer = 0;
    while (procuraMenor(arq, K, T, &menor) == 1)
    {
        buffer[qtdBuffer] = menor;
        qtdBuffer++;
        if (qtdBuffer == T)
        {
            salvaArquivo(nome, buffer, T);
            qtdBuffer = 0;
        }
    }

    if (qtdBuffer != 0)
        salvaArquivo(nome, buffer, qtdBuffer);

    for (i = 0; i < K; i++)
    {
        delete[] arq[i].buffer;
    }

    delete[] arq;
    delete[] buffer;
}

void mergeSortExterno(const char *nome)
{
    char novo[20];
    int K = criaArquivosOrdenados(nome);
    int i, T = N / (K + 1);
    std::cout << "Nro de arquivos:" << K << std::endl;
    std::cout << "K:" << T << std::endl;

    remove(nome);
    merge(nome, K, T);

    for (i = 0; i < K; i++)
    {
        sprintf(novo, "Temp%d.bin", i + 1);
        remove(novo);
    }
    std::cout << "Fim!" << std::endl;
}

void principal(string input)
{
    mergeSortExterno(input.c_str());
}

#endif