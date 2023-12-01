#ifndef ORD_HPP
#define ORD_HPP

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Trabalhador
{
    int id;
    float lat, lng, zip;
    char desc[200], title[100], timeStamp[20], twp[100], addr[100];
    int e;
};

void merge(Trabalhador arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Trabalhador> LeftArr(n1);
    vector<Trabalhador> RightArr(n2);

    for (int i = 0; i < n1; i++)
        LeftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        RightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (LeftArr[i].id <= RightArr[j].id)
        {
            arr[k] = LeftArr[i];
            i++;
        }
        else
        {
            arr[k] = RightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = LeftArr[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = RightArr[j];
        j++;
        k++;
    }
}

void mergeSort(Trabalhador arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void mergeFiles(const char *input_file1, const char *input_file2, const char *output_file)
{
    ifstream in1(input_file1, ios::binary);
    ifstream in2(input_file2, ios::binary);
    ofstream out(output_file, ios::binary);

    Trabalhador worker1, worker2;

    if (!(in1.read(reinterpret_cast<char *>(&worker1), sizeof(Trabalhador))))
    {
        while (in2.read(reinterpret_cast<char *>(&worker2), sizeof(Trabalhador)))
        {
            out.write(reinterpret_cast<const char *>(&worker2), sizeof(Trabalhador));
        }
    }
    else if (!(in2.read(reinterpret_cast<char *>(&worker2), sizeof(Trabalhador))))
    {
        out.write(reinterpret_cast<const char *>(&worker1), sizeof(Trabalhador));
        while (in1.read(reinterpret_cast<char *>(&worker1), sizeof(Trabalhador)))
        {
            out.write(reinterpret_cast<const char *>(&worker1), sizeof(Trabalhador));
        }
    }
    else
    {
        do
        {
            if (worker1.id <= worker2.id)
            {
                out.write(reinterpret_cast<const char *>(&worker1), sizeof(Trabalhador));
                if (!(in1.read(reinterpret_cast<char *>(&worker1), sizeof(Trabalhador))))
                    break;
            }
            else
            {
                out.write(reinterpret_cast<const char *>(&worker2), sizeof(Trabalhador));
                if (!(in2.read(reinterpret_cast<char *>(&worker2), sizeof(Trabalhador))))
                    break;
            }
        } while (true);

        while (in1.read(reinterpret_cast<char *>(&worker1), sizeof(Trabalhador)))
        {
            out.write(reinterpret_cast<const char *>(&worker1), sizeof(Trabalhador));
        }

        while (in2.read(reinterpret_cast<char *>(&worker2), sizeof(Trabalhador)))
        {
            out.write(reinterpret_cast<const char *>(&worker2), sizeof(Trabalhador));
        }
    }

    in1.close();
    in2.close();
    out.close();
}

void mergeExternalSort(const char *input_file, const char *output_file, int chunk_size)
{
    ifstream in(input_file, ios::binary);
    Trabalhador *chunk = new Trabalhador[chunk_size];
    int run = 0;

    while (!in.eof())
    {
        in.read(reinterpret_cast<char *>(chunk), chunk_size * sizeof(Trabalhador));
        int num_read = in.gcount() / sizeof(Trabalhador);
        if (num_read > 0)
        {
            mergeSort(chunk, 0, num_read - 1);
            ofstream out(to_string(run) + ".bin", ios::binary);
            out.write(reinterpret_cast<const char *>(chunk), num_read * sizeof(Trabalhador));
            out.close();
            run++;
        }
    }

    in.close();

    int num_runs = run;

    while (num_runs > 1)
    {
        for (int i = 0; i < num_runs; i += 2)
        {
            string input_file1 = (i < num_runs) ? to_string(i) + ".bin" : "";
            string input_file2 = (i + 1 < num_runs) ? to_string(i + 1) + ".bin" : "";
            string output_file = to_string(i / 2) + ".bin";

            mergeFiles(input_file1.c_str(), input_file2.c_str(), output_file.c_str());
        }

        num_runs = (num_runs + 1) / 2;
    }

    // Rename the final output file
    rename("0.bin", output_file);

    // Clean up temporary files
    for (int i = 0; i < num_runs; ++i)
    {
        remove((to_string(i) + ".bin").c_str());
    }

    delete[] chunk;
}

void principal(string nomeArquivo)
{
    const char *input_file = nomeArquivo.c_str();
    const char *output_file = "trabalhadores_sorted.bin";
    int chunk_size = 300000; // Assuming the number of records in the file is known

    mergeExternalSort(input_file, output_file, chunk_size);

    cout << "Merge Sort External completed successfully." << endl;
}

#endif