#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 300

typedef struct aluno
{
    char nome[100];
    char curso[4];
    int matricula;
} aluno;

void imprimeVetor(aluno *v, int n);
void leVetor(aluno *v, char *nomeArquivo);
int particao(aluno *v, int p, int r);
void quickSort(aluno *v, int p, int r);

int main()
{
    aluno v[max] = {0};
    char nomeArquivo[max];
    int count = 0;

    leVetor(v, nomeArquivo);

    for (int i = 0; i < max; i++)
    {
        if (v[i].matricula == 0)
        {
            count++;
        }
    }

    quickSort(v, 0, (max - count) - 1);

    imprimeVetor(v, (max - count));

    return 0;
}

void leVetor(aluno *v, char *nomeArquivo)
{
    char items[100];
    int index = 0;
    FILE *f;

    //scanf("%s", nomeArquivo);

    f = fopen("file.txt", "r");
    //f = fopen(nomeArquivo, "r");
    
    while (fgets(items, 100, f) != NULL)
    {
        char *tab = strtok(items, "\t");
        if (tab != NULL)
        {
            strcpy(v[index].nome, tab);
        }

        tab = strtok(NULL, "\t");
        if (tab != NULL)
        {
            strcpy(v[index].curso, tab);
        }

        tab = strtok(NULL, "\t");
        if (tab != NULL)
        {
            v[index].matricula = atoi(tab);
        }
        index++;
    }

    fclose(f);
}

void quickSort(aluno *v, int p, int r)
{
    int pivot;
    if (p < r)
    {
        pivot = particao(v, p, r);
        quickSort(v, p, pivot - 1);
        quickSort(v, pivot + 1, r);
    }
}

int particao(aluno *v, int p, int r)
{
    int i = p, j = r;
    aluno pivot = v[p], aux;

    while (1)
    {
        while (strcmp(v[i].nome, pivot.nome) <= 0)
        {
            i++;
            if (i == r)
                break;
        }
        while (strcmp(v[j].nome, pivot.nome) > 0)
        {
            j--;
            if (j == p)
                break;
        }

        if (i >= j)
            break;

        aux = v[i];
        v[i] = v[j];
        v[j] = aux;
    }

    aux = v[p];
    v[p] = v[j];
    v[j] = aux;

    return j;
}

void imprimeVetor(aluno *v, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s %s %d\n", v[i].nome, v[i].curso, v[i].matricula);
    }
}
