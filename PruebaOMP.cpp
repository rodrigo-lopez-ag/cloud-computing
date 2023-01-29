// PruebaOMP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
#endif

#define N 1000
#define chunk 100
#define show 10

void printArray(float* d);
void fillArray(float* a, float* b, int total);

int main()
{

    std::cout << "Sum arrays in parallel...\n";
    int optional;
    std::cout << "Enter a number greater than 9: ";
    std::cin >> optional;

    float* a;
    float* b;
    float* c;

    if (optional > 9) {
        a = new float[optional];
        b = new float[optional];
        c = new float[optional];

        fillArray(a, b, optional);
    }
    else
    {
        a = new float[N];
        b = new float[N];
        c = new float[N];

        optional = N;

        for (int i = 0; i < N; i++)
        {
            a[i] = i * 10;
            b[i] = (i + 3) * 3.7;
        }
    }

    int i;

    int chunks = chunk;

    std::cout << "Array size: " << optional << std::endl;

    #pragma omp parallel for \
    shared(a,b,c,chunks) private(i) \
    schedule(static, chunks)

    for (i = 0; i < optional; i++)
    {
        if (i == 0)
        {
            int threads = omp_get_num_threads();
            std::cout << "threads: " << threads << std::endl;
        }
        c[i] = a[i] + b[i];
    }
    std::cout << "Array a first 10 elements" << std::endl;
    printArray(a);

    std::cout << "Array b first 10 elements" << std::endl;
    printArray(b);

    std::cout << "Array c first 10 elements" << std::endl;
    printArray(c);
}

void fillArray(float* a, float* b, int total)
{
    for (int i = 0; i < total; i++)
    {
        a[i] = rand() & total;
        b[i] = rand() & total;
    }
}

void printArray(float* d)
{
    for (int i = 0; i < show; i++)
        std::cout << d[i] << " - ";
    std::cout << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
