#include <stdio.h>
#include <stdlib.h>

void leVetor(int *v, int n);
void smartBubbleSort(int *v, int n, int *c, int *t);
void troca(int *v, int i, int j, int *t);

int main()
{

  int n = 0, *v = NULL, c = 0, t = 0;

  scanf("%d", &n);

  v = (int *)malloc(n * (sizeof(int)));

  if (v == NULL)
    exit(1);

  leVetor(v, n);

  smartBubbleSort(v, n, &c, &t);

  for (int i = 0; i < n; i++)
    printf("%d ", v[i]);

  printf("\n%d %d", c, t);

  free(v);

  return 0;
}

void leVetor(int *v, int n)
{
  for (int i = 0; i < n; i++)
    scanf("%d", &v[i]);
}

void smartBubbleSort(int *v, int n, int *c, int *t)
{
  int i = 0, j = 0, isSorted = 1;
  for (i = 0; i < n - 1 && isSorted; i++)
  {
    for (j = n - 1, isSorted = 0; j > i; j--)
    {
      (*c)++;
      if (v[j] > v[j - 1])
      {
        troca(v, j, j - 1, t);
        isSorted = 1;
      }
    }
  }
}

void troca(int *v, int i, int j, int *t)
{
  int aux = 0;
  aux = v[i];
  v[i] = v[j];
  v[j] = aux;
  (*t)++;
}
