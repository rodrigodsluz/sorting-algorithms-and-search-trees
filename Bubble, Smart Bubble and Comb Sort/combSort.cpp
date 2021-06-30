#include <vector>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int main()
{
  int n, item, i;
  FILE *f;
  vector<int> array_arquivo;
  int *v = NULL;

  char values[20];

  scanf("%s", values);

  f = fopen(values, "r");

  fscanf(f, "%d", &item);

  while (!feof(f))
  {
    array_arquivo.push_back(item);

    fscanf(f, "%d", &item);
  }

  n = array_arquivo.size();

  v = (int *)malloc(n * sizeof(int));

  for (int i = 0; i < n; i++)
  {
    v[i] = array_arquivo[i];
  }

  int step = n, k, j, again = 1, t = 0, c = 0;
  int aux, temp;

  while ((step = int(step / 1.3)) > 1)
    for (j = 0; j < n - step; j++)
    {
      k = j + step;
      c++;
      if (v[j] > v[k])
      {
        aux = v[j];
        v[j] = v[k];
        v[k] = aux;
        printf("%d %d\n", j, k);
        t++;
      }
    }

  for (i = 0; i < n - 1 && again; i++)
    for (j = n - 1, again = 0; j > i; j--)
    {
      c++;
      if (v[j] < v[j - 1])
      {
        temp = v[j];
        v[j] = v[j - 1];
        v[j - 1] = temp;
        t++;
        again = 1;
        printf("%d %d\n", j - 1, j);
      }
    }

  printf("%d %d", c, t);

  fclose(f);

  return 0;
}
