#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(long long int *v, long long int n, long long int *c, long long int *t);
long long int menor(long long int a, long long int b, long long int *c);

void selectionSort(long long int *v, long long int n, long long int *c, long long int *t);

void bubbleSort(long long int *v, long long int n, long long int *c, long long int *t);

void combSort(long long int *v, long long int n, long long int *c, long long int *t);

void mergeSort(long long int *v, long long int p, long long int r, long long int *c, long long int *t);
void intercala(long long int *v, long long int p, long long int q, long long int r, long long int *c, long long int *t);

void quickSort(long long int *v, long long int p, long long int r, long long int *c, long long int *t);
long long int particao(long long int *v, long long int p, long long int r, long long int *c, long long int *t);

void heapSort(long long int *v, long long int n, long long int *c, long long int *t);
void heapify(long long int *v, long long int n, long long int i, long long int *c, long long int *t);

void mergeSortExterno(long long int v[], long long int l, long long int r, long long int *c, long long int *t);
void merge(long long int v[], long long int l, long long int m, long long int r, long long int *c, long long int *t);
FILE *openFile(char const *fileName, char *mode);
void mergeFiles(char const *output_file, long long int n, long long int k);
void createInitialRuns(char const *input_file, long long int run_size, long long int num_ways, long long int *c, long long int *t);
void externalSort(char const *input_file, char const *output_file, long long int num_ways, long long int run_size, long long int *c, long long int *t);

void printResult(double executionTime, long long int qtdComparacoes, long long int qtdTrocas);

void leVetor(long long int *v, long long int n, int arrayType);

int main()
{
  long long int *v = NULL, n, qtdComparacoes, qtdTrocas, c, t;
  int algorithm = 0, arraySize, arrayType;
  srand(time(NULL));
  clock_t startTime, finalTime;
  double executionTime = 0;

  do
  {
    printf("\n|--------------------------------------------------------|\n");
    printf("|             Escolha um tamanho de vetor                |\n");
    printf("|--------------------------------------------------------|\n");
    printf("|Opcao [1] - 270 mil elementos                           |\n");
    printf("|Opcao [2] - 180 mil elementos                           |\n");
    printf("|Opcao [3] - 120 mil elementos                           |\n");
    printf("|Opcao [4] - 80 mil elementos                            |\n");
    printf("|Opcao [5] - 50 mil elementos                            |\n");
    printf("|                                                        |\n");
    printf("|Opcao [0] - Sair                                        |\n");
    printf("|--------------------------------------------------------|\n\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &arraySize);
    switch (arraySize)
    {
    case 0:
      printf("\nObrigado, volte sempre!\n");
      break;

    case 1:
      n = 270000;
      break;

    case 2:
      n = 180000;
      break;

    case 3:
      n = 120000;
      break;

    case 4:
      n = 80000;
      break;

    case 5:
      n = 50000;
      break;

    default:
      printf("\n\nEssa opcao nao existe, tente novamente!!!\n\n");
      break;
    }

    while ((arraySize >= 1 && arraySize <= 5) && algorithm == 0)
    {
      printf("\nO tamanho do vetor escolhido foi: %lld elementos\n", n);

      qtdComparacoes = 0, qtdTrocas = 0, c = 0, t = 0;
      startTime = 0, finalTime = 0;

      v = (long long int *)malloc(n * (sizeof(long long int)));

      if (v == NULL)
        exit(1);

      printf("\n|------------------------------------------------------------------------------------------------------------|\n");
      printf("|Escolha a forma com que os elementos estarao dentro do vetor                                                |\n");
      printf("|------------------------------------------------------------------------------------------------------------|\n");
      printf("|Opcao [1] - Elementos distintos e distribuidos aleatoriamente                                               |\n");
      printf("|Opcao [2] - Elementos distintos ja ordenados                                                                |\n");
      printf("|Opcao [3] - Elementos distintos ordenados de forma reversa                                                  |\n");
      printf("|Opcao [4] - Elementos distribuidos aleatoriamente, e cada elemento em qtd >= 5 por cento do tamanho do vetor|\n");
      printf("|------------------------------------------------------------------------------------------------------------|\n\n");
      printf("Digite a opcao desejada: ");
      scanf("%d", &arrayType);

      leVetor(v, n, arrayType);

      while ((arrayType >= 1 && arrayType <= 4) && algorithm == 0)
      {
        printf("\n|-------------------------------------------------------------------|\n");
        printf("|Escolha algum algoritmo de ordenacao abaixo para ordenar esse vetor|\n");
        printf("|-------------------------------------------------------------------|\n");
        printf("|Opcao [1] - Insertion Sort                                         |\n");
        printf("|Opcao [2] - Selection Sort                                         |\n");
        printf("|Opcao [3] - Bubble Sort                                            |\n");
        printf("|Opcao [4] - Comb Sort                                              |\n");
        printf("|Opcao [5] - Merge Sort                                             |\n");
        printf("|Opcao [6] - Quick Sort                                             |\n");
        printf("|Opcao [7] - Heap Sort                                              |\n");
        printf("|Opcao [8] - Merge Sort Externo                                     |\n");
        printf("|-------------------------------------------------------------------|\n\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &algorithm);

        switch (algorithm)
        {
        case 1:
          startTime = clock(); //inicia contagem do tempo
          insertionSort(v, n, &c, &t);
          finalTime = clock(); // finaliza contagem do tempo

          printf("\n\nVc escolheu ordenar os elementos do vetor com o Insertion Sort\n\n");

          executionTime = (double)(finalTime - startTime) / CLOCKS_PER_SEC;
          qtdTrocas = t;
          qtdComparacoes = c;

          printResult(executionTime, qtdComparacoes, qtdTrocas);
          break;

        case 2:
          startTime = clock(); //inicia contagem do tempo
          selectionSort(v, n, &c, &t);
          finalTime = clock(); // finaliza contagem do tempo

          printf("\n\nVc escolheu ordenar os elementos do vetor com o Selection Sort\n\n");

          executionTime = (double)(finalTime - startTime) / CLOCKS_PER_SEC;
          qtdTrocas = t;
          qtdComparacoes = c;

          printResult(executionTime, qtdComparacoes, qtdTrocas);
          break;

        case 3:
          startTime = clock(); //inicia contagem do tempo
          bubbleSort(v, n, &c, &t);
          finalTime = clock(); // finaliza contagem do tempo

          printf("\n\nVc escolheu ordenar os elementos do vetor com o Bubble Sort\n\n");

          executionTime = (double)(finalTime - startTime) / CLOCKS_PER_SEC;
          qtdTrocas = t;
          qtdComparacoes = c;

          printResult(executionTime, qtdComparacoes, qtdTrocas);
          break;

        case 4:
          startTime = clock(); //inicia contagem do tempo
          combSort(v, n, &c, &t);
          finalTime = clock(); // finaliza contagem do tempo

          printf("\n\nVc escolheu ordenar os elementos do vetor com o Comb Sort\n\n");

          executionTime = (double)(finalTime - startTime) / CLOCKS_PER_SEC;
          qtdTrocas = t;
          qtdComparacoes = c;

          printResult(executionTime, qtdComparacoes, qtdTrocas);
          break;

        case 5:
          startTime = clock(); //inicia contagem do tempo
          mergeSort(v, 0, n, &c, &t);
          finalTime = clock(); // finaliza contagem do tempo

          printf("\n\nVc escolheu ordenar os elementos do vetor com o Merge Sort\n\n");

          executionTime = (double)(finalTime - startTime) / CLOCKS_PER_SEC;
          qtdTrocas = t;
          qtdComparacoes = c;

          printResult(executionTime, qtdComparacoes, qtdTrocas);
          break;

        case 6:
          startTime = clock(); //inicia contagem do tempo
          quickSort(v, 0, n - 1, &c, &t);
          finalTime = clock(); // finaliza contagem do tempo

          printf("\n\nVc escolheu ordenar os elementos do vetor com o Quick Sort\n\n");

          executionTime = (double)(finalTime - startTime) / CLOCKS_PER_SEC;
          qtdTrocas = t;
          qtdComparacoes = c;

          printResult(executionTime, qtdComparacoes, qtdTrocas);
          break;

        case 7:
          startTime = clock(); //inicia contagem do tempo
          heapSort(v, n, &c, &t);
          finalTime = clock(); // finaliza contagem do tempo

          printf("\n\nVc escolheu ordenar os elementos do vetor com o Heap Sort\n\n");

          executionTime = (double)(finalTime - startTime) / CLOCKS_PER_SEC;
          qtdTrocas = t;
          qtdComparacoes = c;

          printResult(executionTime, qtdComparacoes, qtdTrocas);
          break;

        case 8:
        {
          long long int num_ways = 10, run_size = n / 10;
          char const *input_file = "input.txt", *output_file = "output.txt";
          FILE *in = openFile(input_file, "w");

          for (long long int i = 0; i < num_ways * run_size; i++)
            fprintf(in, "%lld ", v[i]);

          fclose(in);

          startTime = clock(); //inicia contagem do tempo
          externalSort(input_file, output_file, num_ways, run_size, &c, &t);
          finalTime = clock(); // finaliza contagem do tempo

          printf("\n\nVc escolheu ordenar os elementos do vetor com o Merge Sort Externo\n\n");

          executionTime = (double)(finalTime - startTime) / CLOCKS_PER_SEC;
          qtdTrocas = t;
          qtdComparacoes = c;

          printResult(executionTime, qtdComparacoes, qtdTrocas);
          break;
        }
        }
      }
    }
    algorithm = 0;
    free(v);
  } while (arraySize != 0);
  return 0;
}

void insertionSort(long long int *v, long long int n, long long int *c, long long int *t)
{
  long long int i, j, aux;
  for (i = 1; i < n; i++)
  {
    for (j = i; j > 0 && menor(v[j], v[j - 1], c); j--)
    {
      aux = v[j];
      v[j] = v[j - 1];
      v[j - 1] = aux;
      (*t)++;
    }
  }
}

long long int menor(long long int a, long long int b, long long int *c)
{
  (*c)++;
  return (a < b);
}

void selectionSort(long long int *v, long long int n, long long int *c, long long int *t)
{
  long long int i, j, min, aux;
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
    aux = v[i];
    v[i] = v[min];
    v[min] = aux;
    (*t)++;
  }
}

void bubbleSort(long long int *v, long long int n, long long int *c, long long int *t)
{
  long long int i, j, aux;
  for (i = 0; i < n - 1; i++)
    for (j = n - 1; j > i; j--)
    {
      (*c)++;
      if (v[j] < v[j - 1])
      {
        aux = v[j];
        v[j] = v[j - 1];
        v[j - 1] = aux;
        (*t)++;
      }
    }
}

void combSort(long long int *v, long long int n, long long int *c, long long int *t)
{
  long long int step = n, i, k, j, again = 1, aux;
  while ((step = (long long int)(step / 1.3)) > 1)
    for (j = n - 1; j >= step; j--)
    {
      k = j - step;
      (*c)++;
      if (v[j] < v[k])
      {
        aux = v[j];
        v[j] = v[k];
        v[k] = aux;
        (*t)++;
      }
    }

  for (i = 0; i < n - 1 && again; i++)
    for (j = n - 1, again = 0; j > i; j--)
    {
      (*c)++;
      if (v[j] < v[j - 1])
      {
        aux = v[j];
        v[j] = v[j - 1];
        v[j - 1] = aux;
        (*t)++;
        again = 1;
      }
    }
}

void mergeSort(long long int *v, long long int p, long long int r, long long int *c, long long int *t)
{
  if (p < r - 1)
  {
    long long int q = (p + r) / 2; //metade
    mergeSort(v, p, q, c, t);
    mergeSort(v, q, r, c, t);
    intercala(v, p, q, r, c, t);
  }
}

void intercala(long long int *v, long long int p, long long int q, long long int r, long long int *c, long long int *t)
{
  long long int i, j, k; //contadores
  long long int *w;      //vetor auxiliar

  w = (long long int *)malloc((r - p) * sizeof(long long int));

  if (w == NULL)
    exit(1);

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

void quickSort(long long int *v, long long int p, long long int r, long long int *c, long long int *t)
{
  long long int pivot;

  if (p < r)
  {
    pivot = particao(v, p, r, c, t);
    quickSort(v, p, pivot, c, t);
    quickSort(v, pivot + 1, r, c, t);
  }
}

long long int particao(long long int *v, long long int p, long long int r, long long int *c, long long int *t)
{
  long long int pivot = v[p];
  long long int i = p - 1, j = r + 1, aux;

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

void heapify(long long int *v, long long int n, long long int i, long long int *c, long long int *t)
{
  long long int maior = i, esq = 2 * i + 1, dir = 2 * i + 2, aux;

  (*c)++;
  if (esq < n && v[esq] > v[maior])
    maior = esq;

  (*c)++;
  if (dir < n && v[dir] > v[maior])
    maior = dir;

  if (maior != i)
  {
    aux = v[i];
    v[i] = v[maior];
    v[maior] = aux;
    (*t)++;

    heapify(v, n, maior, c, t);
  }
}

void heapSort(long long int *v, long long int n, long long int *c, long long int *t)
{
  long long int i, aux;

  for (i = n / 2 - 1; i >= 0; i--)
    heapify(v, n, i, c, t);

  for (i = n - 1; i >= 0; i--)
  {
    aux = v[0];
    v[0] = v[i];
    v[i] = aux;
    (*t)++;

    heapify(v, i, 0, c, t);
  }
}

void merge(long long int v[], long long int l, long long int m, long long int r, long long int *c, long long int *t)
{
  long long int i, j, k, n1 = m - l + 1, n2 = r - m;

  long long int *L = (long long int *)malloc((n1) * sizeof(long long int));

  if (L == NULL)
    exit(1);

  long long int *R = (long long int *)malloc((n2) * sizeof(long long int));

  if (R == NULL)
    exit(1);

  for (i = 0; i < n1; i++)
  {
    (*t)++;
    L[i] = v[l + i];
  }
  for (j = 0; j < n2; j++)
  {
    (*t)++;
    R[j] = v[m + 1 + j];
  }

  i = 0;
  j = 0;
  k = l;

  while (i < n1 && j < n2)
  {
    (*c)++;
    (*t)++;
    if (L[i] <= R[j])
      v[k++] = L[i++];
    else
      v[k++] = R[j++];
  }

  while (i < n1)
  {
    (*t)++;
    v[k++] = L[i++];
  }
  while (j < n2)
  {
    (*t)++;
    v[k++] = R[j++];
  }
  free(L);
  free(R);
}

void mergeSortExterno(long long int v[], long long int l, long long int r, long long int *c, long long int *t)
{
  if (l < r)
  {
    long long int m = l + (r - l) / 2;
    mergeSortExterno(v, l, m, c, t);
    mergeSortExterno(v, m + 1, r, c, t);
    merge(v, l, m, r, c, t);
  }
}

FILE *openFile(char const *fileName, char *mode)
{
  FILE *fp = fopen(fileName, mode);
  if (fp == NULL)
  {
    perror("Erro ao abrir o arquivo.\n");
    exit(EXIT_FAILURE);
  }
  return fp;
}

//Merge Sort Externo
struct MinHeapNode
{
  long long int element, i;
};

class MinHeap
{
  MinHeapNode *harr;
  long long int heap_size;

public:
  MinHeap(MinHeapNode a[], long long int size);

  void MinHeapify(long long int);

  long long int left(long long int i) { return (2 * i + 1); }

  long long int right(long long int i) { return (2 * i + 2); }

  MinHeapNode getMin() { return harr[0]; }

  void replaceMin(MinHeapNode x)
  {
    harr[0] = x;
    MinHeapify(0);
  }
};

MinHeap::MinHeap(MinHeapNode a[], long long int size)
{
  heap_size = size;
  harr = a;
  long long int i = (heap_size - 1) / 2;
  while (i >= 0)
  {
    MinHeapify(i);
    i--;
  }
}

void MinHeap::MinHeapify(long long int i)
{
  long long int l = left(i), r = right(i), smallest = i;
  MinHeapNode temp;
  if (l < heap_size && harr[l].element < harr[i].element)
    smallest = l;
  if (r < heap_size && harr[r].element < harr[smallest].element)
    smallest = r;
  if (smallest != i)
  {
    temp = harr[i];
    harr[i] = harr[smallest];
    harr[smallest] = temp;
    MinHeapify(smallest);
  }
}

void mergeFiles(char const *output_file, long long int n, long long int k)
{
  FILE *in[k];
  for (long long int i = 0; i < k; i++)
  {
    char fileName[2];

    snprintf(fileName, sizeof(fileName),
             "%lld", i);

    in[i] = openFile(fileName, "r");
  }
  FILE *out = openFile(output_file, "w");

  MinHeapNode *harr = new MinHeapNode[k];
  long long int i;
  for (i = 0; i < k; i++)
  {

    if (fscanf(in[i], "%lld ", &harr[i].element) != 1)
      break;

    harr[i].i = i;
  }

  MinHeap hp(harr, i);

  long long int count = 0;

  while (count != i)
  {
    MinHeapNode root = hp.getMin();
    fprintf(out, "%lld ", root.element);

    if (fscanf(in[root.i], "%lld ",
               &root.element) != 1)
    {
      root.element = INT_MAX;
      count++;
    }
    hp.replaceMin(root);
  }

  for (long long int i = 0; i < k; i++)
    fclose(in[i]);

  fclose(out);
}

void createInitialRuns(char const *input_file, long long int run_size, long long int num_ways, long long int *c, long long int *t)
{
  FILE *in = openFile(input_file, "r");
  FILE *out[num_ways];
  char fileName[2];
  for (long long int i = 0; i < num_ways; i++)
  {
    snprintf(fileName, sizeof(fileName),
             "%lld", i);

    out[i] = openFile(fileName, "w");
  }

  long long int *v = (long long int *)malloc(
      run_size * sizeof(long long int));
  bool more_input = true;
  long long int next_output_file = 0, i;

  while (more_input)
  {

    for (i = 0; i < run_size; i++)
    {
      if (fscanf(in, "%lld ", &v[i]) != 1)
      {
        more_input = false;
        break;
      }
    }

    mergeSortExterno(v, 0, i - 1, c, t);

    for (long long int j = 0; j < i; j++)
      fprintf(out[next_output_file],
              "%lld ", v[j]);

    next_output_file++;
  }

  for (long long int i = 0; i < num_ways; i++)
    fclose(out[i]);

  fclose(in);
}

void externalSort(char const *input_file, char const *output_file, long long int num_ways, long long int run_size, long long int *c, long long int *t)
{
  createInitialRuns(input_file, run_size, num_ways, c, t);
  mergeFiles(output_file, run_size, num_ways);
}

void printResult(double executionTime, long long int qtdComparacoes, long long int qtdTrocas)
{
  printf("\nTempo de execucao: %f segundos\n\n", executionTime);
  printf("Quantidade de comparacoes: %lld\n\n", qtdComparacoes);
  printf("Quantidade de trocas: %lld\n\n", qtdTrocas);
  printf("\n\nMuito obrigado, escolha outra opcao!!!\n\n");
}

void leVetor(long long int *v, long long int n, int arrayType)
{
  long long int count = 0, i, a, b, aux;
  switch (arrayType)
  {
  case 1:
    //Preenche o vetor com valores aleatórios
    for (i = 0; i < n; i++)
      v[i] = i;

    for (i = 0; i < n; i++)
    {
      a = rand() % n;
      b = rand() % n;
      aux = v[a];
      v[a] = v[b];
      v[b] = aux;
    }

    printf("\nVoce escolheu o vetor com elementos distintos e distribuidos de forma aleatoria\n");
    break;

  case 2:
    //Preenche o vetor com elementos ordenados
    for (i = 0; i < n; i++)
      v[i] = i;

    printf("\nVoce escolheu o vetor com elementos distintos ja ordenados.\n");
    break;

  case 3:
    //Preenche o vetor com elementos ordenados de forma reversa
    count = 0;
    for (i = n - 1; i >= 0; i--)
    {
      v[count] = i;
      count++;
    }
    printf("\nVoce escolheu o vetor com elementos distintos ordenados de forma reversa.\n");
    break;

  case 4:
    //Preenche o vetor com elementos aleatórios e repetidos
    count = 0;
    for (i = 0; i < n; i++)
      v[i] = i % 5;

    for (i = 0; i < n; i++)
    {
      a = rand() % n;
      b = rand() % n;
      aux = v[a];
      v[a] = v[b];
      v[b] = aux;
    }
    printf("\nVc escolheu o vetor de valores distribuidos aleatoriamente, e cada valor em qtd >= 5 por cento do tamanho\n");
    break;
  default:
    printf("\n\nEssa opcao nao existe, tente novamente!!!\n\n");
    break;
  }
}
