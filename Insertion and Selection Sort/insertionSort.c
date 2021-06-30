#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void leVetor(int *v, int n);
void insertionSort(int *v, int n, int *c, int *t);
int menor(int a, int b, int *c);
void troca(int *v, int i, int j, int *t);

int main()
{

  int n = 0;
  int *v, c = 0, t = 0;

  scanf("%d", &n);

  v = (int *)malloc(n * (sizeof(int)));

  if (v == NULL)
    exit(1);

  leVetor(v, n);

  insertionSort(v, n, &c, &t);

  printf("%d %d", c, t);

  free(v);

      return 0;
}

void leVetor(int *v, int n)
{
  for (int i = 0; i < n; i++)
    scanf("%d", &v[i]);
}

void insertionSort(int *v, int n, int *c, int *t)
{
  int i, j;
  for (i = 1; i < n; i++)
  {
    for (j = i; j > 0 && menor(v[j], v[j - 1], c); j--)
      troca(v, j, j - 1, t);
  }
}

int menor(int a, int b, int *c)
{
  (*c)++;
  return (a < b);
}

void troca(int *v, int i, int j, int *t)
{
  int aux;
  aux = v[i];
  v[i] = v[j];
  v[j] = aux;
  (*t)++;
}
