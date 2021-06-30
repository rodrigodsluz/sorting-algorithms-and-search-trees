#include <stdio.h>
#include <stdlib.h>

void leVetor(int *v, int n);
void mergeSort(int *v, int p, int r, int *c, int *t);
void intercala(int *v, int p, int q, int r, int *c, int *t);

int main()
{

  int n = 0, c = 0, t = 0;
  int *v = NULL;

  scanf("%d", &n);

  v = (int *)malloc(n * (sizeof(int)));

  if (v == NULL)
    exit(1);

  leVetor(v, n);

  mergeSort(v, 0, n, &c, &t);

  printf("%d %d", c, t);

  free(v);

  return 0;
}

void leVetor(int *v, int n)
{
  for (int i = 0; i < n; i++)
    scanf("%d", &v[i]);
}

void mergeSort(int *v, int p, int r, int *c, int *t)
{
  if (p < r - 1)
  {
    int q = (p + r) / 2; //metade

    mergeSort(v, p, q, c, t);
    mergeSort(v, q, r, c, t);
    intercala(v, p, q, r, c, t);
  }
}

void intercala(int *v, int p, int q, int r, int *c, int *t)
{
  int i, j, k; //contadores
  int *w;      //vetor auxiliar

  w = (int *)malloc((r - p) * sizeof(int));
  i = p;
  j = q;
  k = 0;

  while (i < q && j < r)
  {
    if (v[i] <= v[j])
    {
      w[k++] = v[i++];
    }
    else
    {
      w[k++] = v[j++];
    }
    (*c)++;
    (*t)++;
  }

  while (i < q)
  {
    (*t)++;
    w[k++] = v[i++];
  }
  while (j < r)
  {
    (*t)++;
    w[k++] = v[j++];
  }

  for (i = p; i < r; i++)
  {
    (*t)++;
    v[i] = w[i - p];
  }

  free(w);
}