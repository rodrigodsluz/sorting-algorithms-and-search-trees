#include <stdio.h>
#include <stdlib.h>

void leVetor(int *v, int n);
void bubbleSort(int *v, int n, long long int *c, long long int *t);

int main()
{

  int n, *v;
  long long int c = 0, t = 0;

  scanf("%d", &n);

  v = (int *)malloc(n * (sizeof(int)));

  if (v == NULL)
    exit(1);

  leVetor(v, n);

  bubbleSort(v, n, &c, &t);

  printf("%lli %lli", c, t);

  free(v);

  return 0;
}

void leVetor(int *v, int n)
{
  for (int i = 0; i < n; i++)
    scanf("%d", &v[i]);
}

void bubbleSort(int *v, int n, long long int *c, long long int *t)
{
  int i, j;
  for (i = 0; i < n - 1; i++)
    for (j = n - 1; j > i; j--)
    {
      (*c)++;
      if (v[j] < v[j - 1])
      {
        int aux;
        aux = v[j];
        v[j] = v[j - 1];
        v[j - 1] = aux;
        (*t)++;
      }
    }
}
