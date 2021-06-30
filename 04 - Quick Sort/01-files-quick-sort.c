#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
int fileSize(char *nomeArquivo);

int main()
{
    aluno *v = NULL;
    char nomeArquivo[100];
    int n = 0;

    scanf("%s", nomeArquivo);

    //Pega o número de linhas do arquivo
    n = fileSize(nomeArquivo);

    v = (aluno *)malloc(n * (sizeof(aluno)));

    if (v == NULL)
        exit(1);

    leVetor(v, nomeArquivo);

    quickSort(v, 0, n - 1);

    imprimeVetor(v, n);

    free(v);

    return 0;
}

void leVetor(aluno *v, char *nomeArquivo)
{
    int i = 0;
    FILE *f;

    //f = fopen("file.txt", "r");
    f = fopen(nomeArquivo, "r");

    fscanf(f, "%[^\t] %s %d", v[i].nome, v[i].curso, &(v[i].matricula));

    while (!feof(f))
    {
        i++;
        fscanf(f, " %[^\t]  %s %d", v[i].nome, v[i].curso, &(v[i].matricula));
    }


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
    int i = p, j = r + 1;
    aluno pivot = v[p], aux;

    while (1)
    {
        while (strcmp(v[++i].nome, pivot.nome) < 0)
        {
            if (i == r)
                break;
        }
        while (strcmp(v[--j].nome, pivot.nome) > 0)
        {
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
    for (int i = 1; i < n; i++)
    {
        printf("%s %s %d\n", v[i].nome, v[i].curso, v[i].matricula);
    }
}

int fileSize(char *nomeArquivo)
{
    FILE *fN;
    char lines[100];
    int count = 0;

    //fN = fopen("file.txt", "r");
    fN = fopen(nomeArquivo, "r");

    while (!feof (fN))
    {
        count++;
        fgets(lines, 100, fN);
    }

    return count;
}



