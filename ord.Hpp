#ifndef ORD_HPP
#define ORD_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Trabalhador 
{
    int id;
    float lat, lng, zip;
    char desc[200], title[100], timeStamp[20], twp[100], addr[100];
    int e;
};

void merge(std::vector<Trabalhador> &result, const std::vector<Trabalhador> &left, const std::vector<Trabalhador> &right) {
    auto leftIt = left.begin();
    auto rightIt = right.begin();

    while (leftIt != left.end() && rightIt != right.end()) {
        if (leftIt->id <= rightIt->id) {
            result.push_back(*leftIt);
            ++leftIt;
        } else {
            result.push_back(*rightIt);
            ++rightIt;
        }
    }

    result.insert(result.end(), leftIt, left.end());
    result.insert(result.end(), rightIt, right.end());
}

void mergeSortExternal(const std::string &inputFile, const std::string &outputFile, int blockSize = 2) {
    std::ifstream input(inputFile, std::ios::binary);
    if (!input.is_open()) {
        std::cerr << "Error opening input file." << std::endl;
        return;
    }

    Trabalhador worker;
    std::vector<Trabalhador> workers;

    // Read and process data in chunks
    while (true) {
        workers.clear(); // Clear the workers vector before reading a new chunk
        workers.reserve(blockSize);

        for (int i = 0; i < blockSize; ++i) {
            if (input.read(reinterpret_cast<char *>(&worker), sizeof(Trabalhador))) {
                workers.push_back(worker);
            } else {
                break; // Reached the end of the file
            }
        }

        if (workers.empty()) {
            break; // No more data to process
        }

        // Perform sorting and merging for the current chunk
        std::sort(workers.begin(), workers.end(), [](const Trabalhador &a, const Trabalhador &b) {
            return a.id < b.id;
        });

        std::ofstream output(outputFile, std::ios::binary | std::ios::app);
        output.write(reinterpret_cast<const char *>(workers.data()), sizeof(Trabalhador) * workers.size());
        output.close();
    }

    input.close();
}

void principal (string input) {
    string inputFile = input;
    string outputFile = "resultado.bin";
    int blockSize = 2;

    mergeSortExternal(inputFile, outputFile, blockSize);

    remove(input.c_str());

    rename("resultado.bin", input.c_str());
}

#endif