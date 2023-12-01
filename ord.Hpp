#ifndef ORD_HPP
#define ORD_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <thread>

using namespace std;

struct Trabalhador
{
    int id;
    float lat, lng, zip;
    char desc[200], title[100], timeStamp[20], twp[100], addr[100];
    int e;
};

void intercala(const vector<Trabalhador>& arr1, const vector<Trabalhador>& arr2, vector<Trabalhador>& result)
{
    // Merge the two sorted arrays into the result array
    merge(arr1.begin(), arr1.end(), arr2.begin(), arr2.end(), result.begin(), [](const Trabalhador& a, const Trabalhador& b) {
        return a.id < b.id;
    });
}

void mergeSort(vector<Trabalhador>& arr)
{
    if (arr.size() <= 1)
        return;

    vector<Trabalhador> left(arr.begin(), arr.begin() + arr.size() / 2);
    vector<Trabalhador> right(arr.begin() + arr.size() / 2, arr.end());

    mergeSort(left);
    mergeSort(right);

    intercala(left, right, arr);
}

void ordena_externo(const char* arq)
{
    ifstream inputFile(arq, ios::binary);
    if (!inputFile)
    {
        cerr << "Failed to open input file: " << arq << endl;
        return;
    }

    std::vector<Trabalhador> workers;
    Trabalhador worker;
    while (inputFile.read(reinterpret_cast<char*>(&worker), sizeof(Trabalhador)))
    {
        workers.push_back(worker);
    }
    inputFile.close();

    if (workers.empty())
    {
        cerr << "Input file is empty." << endl;
        return;
    }

    // Check if the input file is already sorted
    bool isSorted = is_sorted(workers.begin(), workers.end(), [](const Trabalhador& a, const Trabalhador& b) {
        return a.id < b.id;
    });

    if (isSorted)
    {
        cout << "Input file is already sorted." << endl;
        return;
    }

    mergeSort(workers);

    ofstream outputFile(arq, ios::binary);
    if (!outputFile)
    {
        cerr << "Failed to open output file: " << arq << endl;
        return;
    }

    for (const auto& worker : workers)
    {
        outputFile.write(reinterpret_cast<const char*>(&worker), sizeof(Trabalhador));
    }
    outputFile.close();
}

#endif