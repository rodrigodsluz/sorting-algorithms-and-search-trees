#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void leVetor(int *v, int n);
void selectionSort(int *v, int n, int *c, int *t);
void troca(int *v, int i, int min, int *t);

int main()
{

  int n = 0;
  int *v, c = 0, t = 0;

  scanf("%d", &n);

  v = (int *)malloc(n * (sizeof(int)));

  if (v == NULL)
    exit(1);

  leVetor(v, n);

  selectionSort(v, n, &c, &t);

  printf("%d %d", c, t);

  free(v);

      return 0;
}

void leVetor(int *v, int n)
{
  for (int i = 0; i < n; i++)
    scanf("%d", &v[i]);
}

void selectionSort(int *v, int n, int *c, int *t)
{
  int i, j, min;
  for (i = 0; i < n - 1; i++)
  {
    min = i;
    for (j = i + 1; j < n; j++)
    {
      (*c)++;
      if (v[j] < v[min])
      {
        min = j;
      }
    }

    troca(v, i, min, t);
  }
}

void troca(int *v, int i, int min, int *t)
{
  int aux;
  aux = v[i];
  v[i] = v[min];
  v[min] = aux;
  (*t)++;
}
