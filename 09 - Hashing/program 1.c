#include <stdio.h>
#include <stdlib.h>

struct aluno
{
  int matricula;
};

typedef struct hash
{
  int qtd, n;
  struct aluno **array;
} Hash;

Hash *createHash(int n);
void freeHash(Hash *hash);
int chaveDivisao(int key, int n);
int sondagemLinear(int pos, int i, int n);
int insertKey(Hash *hash, struct aluno aluno);
int searchKey(Hash *hash, int matricula, struct aluno *aluno);
int removeKey(Hash *hash, struct aluno aluno, int n);
int printHash(Hash *hash);

int main()
{
  int menu, n, key, result;

  scanf("%d", &n);

  Hash *table = createHash(n);

  struct aluno aluno;

  do
  {
    scanf("%d", &menu);

    switch (menu)
    {
    case 1:
      scanf("%d", &aluno.matricula);

      insertKey(table, aluno);

      break;

    case 2:
      scanf("%d", &key);

      result = searchKey(table, key, &aluno);

      printf("%d\n", result);

      break;

    case 3:
      scanf("%d", &aluno.matricula);

      result = removeKey(table, aluno, n);

      break;

    case 4:
      printHash(table);

      printf("\n");
      break;
    }
  } while (menu != 9);

  freeHash(table);

  return 0;
}

Hash *createHash(int n)
{
  Hash *hash = (Hash *)malloc(sizeof(Hash));

  if (hash != NULL)
  {
    hash->n = n;

    hash->array = (struct aluno **)malloc(n * sizeof(struct aluno *));

    if (hash->array == NULL)
    {
      free(hash);
      return NULL;
    }

    hash->qtd = 0;

    for (int i = 0; i < hash->n; i++)
      hash->array[i] = NULL;
  }

  return hash;
}

void freeHash(Hash *hash)
{
  if (hash != NULL)
  {
    for (int i = 0; i < hash->n; i++)
      if (hash->array[i] != NULL)
        free(hash->array[i]);

    free(hash->array);

    free(hash);
  }
}

int chaveDivisao(int key, int n)
{
  return (key & 0x7FFFFFFF) % n;
}

int sondagemLinear(int pos, int i, int n)
{
  return ((pos + i) & 0x7FFFFFFF) % n;
}

int insertKey(Hash *hash, struct aluno aluno)
{
  if (hash == NULL || hash->qtd == hash->n)
    return 0;

  int pos, newPos, key = aluno.matricula;

  pos = chaveDivisao(key, hash->n);

  for (int i = 0; i < hash->n; i++)
  {
    newPos = sondagemLinear(pos, i, hash->n);

    if (hash->array[newPos] == NULL)
    {
      struct aluno *new;

      new = (struct aluno *)malloc(sizeof(struct aluno));

      if (new == NULL)
        return 0;

      *new = aluno;

      hash->array[newPos] = new;

      hash->qtd++;

      return 1;
    }
  }
  return 0;
}

int searchKey(Hash *hash, int matricula, struct aluno *aluno)
{
  if (hash == NULL)
    return 0;

  int pos, newPos;

  pos = chaveDivisao(matricula, hash->n);

  for (int i = 0; i < hash->n; i++)
  {
    newPos = sondagemLinear(pos, i, hash->n);

    if (hash->array[newPos] == NULL)
      return -1;

    if (hash->array[newPos]->matricula == matricula)
    {
      *aluno = *(hash->array[newPos]);

      return newPos;
    }
  }

  return -1;
}

int removeKey(Hash *hash, struct aluno aluno, int n)
{
  if (hash == NULL)
    return 0;

  int key = aluno.matricula;

  struct aluno *new;

  new = (struct aluno *)malloc(sizeof(struct aluno));

  if (new == NULL)
    return 0;

  aluno.matricula = -1; //dummy

  *new = aluno;

  hash->array[key] = new;

  hash->qtd--;

  return 1;
}

int printHash(Hash *hash)
{
  if (hash == NULL)
    return 0;
  else
    for (int i = 0; i < hash->n; i++)
      if (hash->array[i] != NULL && hash->array[i]->matricula != -1)
        printf("%d ", hash->array[i]->matricula);
  return 1;
}