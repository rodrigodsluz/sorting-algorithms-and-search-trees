#include <stdio.h>
#include <stdlib.h>

void leVetor(int *v, int n);
void quickSort(int *v, int p, int r, int count, int *c, int *t);
int hoareParticao(int *v, int p, int r, int *c, int *t);
int lomutoParticao(int *v, int p, int r, int *c, int *t);
int sedgewickParticao(int *v, int p, int r, int *c, int *t);

int main()
{
  int qtdComparacoes = 0, qtdTrocas = 0;
  int compLomuto, trocasLomuto, compHoare, trocasHoare, compSedgewick, trocasSedgewick;
  int n, *v = NULL;

  scanf("%d", &n);

  int tempArray[n];

  v = (int *)malloc(n * (sizeof(int)));

  if (v == NULL)
    exit(1);

  leVetor(v, n);

  for (int count = 1; count <= 3; count++)
  {
    qtdComparacoes = 0;
    qtdTrocas = 0;

    switch (count)
    {
    case 1:
      for (int i = 0; i < n; i++)
      {
        tempArray[i] = v[i];
      }
      break;

    case 2:
      for (int i = 0; i < n; i++)
      {
        v[i] = tempArray[i];
      }
      break;

    case 3:
      for (int i = 0; i < n; i++)
      {
        v[i] = tempArray[i];
      }
      break;
    }

    quickSort(v, 0, n - 1, count, &qtdComparacoes, &qtdTrocas);

    switch (count)
    {
    case 1:
      trocasHoare = qtdTrocas;
      compHoare = qtdComparacoes;
      break;
    case 2:
      trocasLomuto = qtdTrocas;
      compLomuto = qtdComparacoes;
      break;
    case 3:
      trocasSedgewick = qtdTrocas;
      compSedgewick = qtdComparacoes;
      break;
    }
  }
  for (int count = 1; count <= 3; count++)
  {
    switch (count)
    {
    case 1:
      printf("%d %d\n", compHoare, trocasHoare);
      break;
    case 2:
      printf("%d %d\n", compLomuto, trocasLomuto);
      break;
    case 3:
      printf("%d %d\n", compSedgewick, trocasSedgewick);
      break;
    }
  }
}

void leVetor(int *v, int n)
{
  for (int i = 0; i < n; i++)
    scanf("%d", &v[i]);
}

void quickSort(int *v, int p, int r, int count, int *c, int *t)
{
  int pivot;

  if (p < r)
  {
    switch (count)
    {
    case 1:

      pivot = hoareParticao(v, p, r, c, t);

      quickSort(v, p, pivot, count, c, t);
      quickSort(v, pivot + 1, r, count, c, t);

      break;
    case 2:

      pivot = lomutoParticao(v, p, r, c, t);

      quickSort(v, p, pivot - 1, count, c, t);
      quickSort(v, pivot + 1, r, count, c, t);

      break;
    case 3:

      pivot = sedgewickParticao(v, p, r, c, t);

      quickSort(v, p, pivot - 1, count, c, t);
      quickSort(v, pivot + 1, r, count, c, t);

      break;
    }
  }
}

int hoareParticao(int *v, int p, int r, int *c, int *t)
{
  int pivot = v[p];
  int i = p - 1, j = r + 1, aux;

  while (1)
  {
    do
    {
      i++;
      (*c)++;
    } while (v[i] < pivot);
    do
    {
      j--;
      (*c)++;
    } while (v[j] > pivot);

    if (i >= j)
      return j;

    aux = v[i];
    v[i] = v[j];
    v[j] = aux;
    (*t)++;
  }
}

int lomutoParticao(int *v, int p, int r, int *c, int *t)
{
  int pivot = v[r], i = p - 1, aux;

  for (int j = p; j < r; j++)
  {
    (*c)++;
    if (v[j] <= pivot)
    {
      i++;

      aux = v[j];
      v[j] = v[i];
      v[i] = aux;

      (*t)++;
    }
  }

  aux = v[i + 1];
  v[i + 1] = v[r];
  v[r] = aux;

  (*t)++;

  return i + 1;
}

int sedgewickParticao(int *v, int p, int r, int *c, int *t)
{
  int i = p, j = r + 1, piv = v[p], aux;

  while (1)
  {
    (*c)++;
    while (v[++i] < piv)
    {
      if (i == r)
        break;

      (*c)++;
    }
    (*c)++;

    while (piv < v[--j])
    {
      if (j == p)
        break;

      (*c)++;
    }

    if (i >= j)
      break;

    aux = v[i];
    v[i] = v[j];
    v[j] = aux;

    (*t)++;
  }
  aux = v[p];
  v[p] = v[j];
  v[j] = aux;

  (*t)++;
  return j;
}
