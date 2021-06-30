#include <iostream>
#include <algorithm>
#include <stdlib.h>

using namespace std;

int main()
{
    long long int trocas, itens;
    while (true)
    {
        cin >> itens >> trocas;
        if (itens == 0 && trocas == 0)
            break;
        long long int trocas_vetor[trocas];
        long long int vetor[itens];
        for (long long int i = 0; i < itens; i++)
        {
            vetor[i] = i + 1;
        }
        for (long long int i = 0; i < trocas; i++)
        {
            cin >> trocas_vetor[i];
        }
        for (long long int i = trocas; i >= 1; i--)
        {
            for (long long int j = 0; j < trocas_vetor[i - 1]; j++)
            {
                swap(vetor[i - 1 + j], vetor[i + j]);
            }
        }
        for (long long int i = 0; i < itens; i++)
        {
            cout << vetor[i] << " ";
        }
        cout << "\n";
    }
}