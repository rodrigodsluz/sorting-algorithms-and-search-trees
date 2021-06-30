//Bibliotecas padrão da linguagem C
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Protótipos das funções*/
//Insertion Sort
void insertionSort(long int *v, long int n, long int *c, long int *t);
int menor(long int a, long int b, long int *c);

//Selection Sort
void selectionSort(long int *v, long int n, long int *c, long int *t);

//Bubble Sort
void bubbleSort(long int *v, long int n, long int *c, long int *t);

//Comb Sort
void combSort(long int *v, long int n, long int *c, long int *t);

//Merge Sort
void mergeSort(long int *v, long int p, long int r, long int *c, long int *t);
void intercala(long int *v, long int p, long int q, long int r, long int *c, long int *t);

//Quick Sort
void quickSort(long int *v, long int p, long int r, long int *c, long int *t);
int hoareParticao(long int *v, long int p, long int r, long int *c, long int *t);

//Heap Sort
void heapify(long int *v, long int n, long int i, long int *c, long int *t);
void heapSort(long int *v, long int n, long int *c, long int *t);

//Merge Sort Externo e struct do arquivo
#define N 100 //Define o tamanho máximo do buffer para ler arquivos

struct arquivo
{
  FILE *f;
  int pos, MAX;
  int *buffer;
};

int compara(const void *a, const void *b);
void salvaArquivo(char *nome, int *V, int tam, int mudaLinhaFinal);
void criArquivoTeste(char *nome, long int n, int arrayType, long int *v);
int criaArquivosOrdenados(char *nome);
void preencheBuffer(struct arquivo *arq, int T);
int procuraMenor(struct arquivo *arq, int K, int T, int *menor);
void merge(char *nome, int K, int T);
void mergeSortExterno(char *nome);
void verificaArquivoOrdenado(char *nome);

//Função para printar resultados
void printResult(double executionTime, long int qtdComparacoes, long int qtdTrocas);

//Função para ler cada vetor com elementos ordenados de forma diferente
void leVetor(long int *v, long int n, int arrayType);

//Função para escrever o arquivo
void writeFile(long int n, long int *v, int algorithm);

int main()
{
  //Declaração do vetor, da variável que será o tamanho dele
  //e as variáveis para contar as trocas e comparações
  long int *v = NULL, n, qtdComparacoes, qtdTrocas, c, t;

  //Declaração das variáveis para auxiliar em contagens
  int algorithm = 0, arraySize, arrayType;

  //Função que cria uma semente para numeros aleatorios
  srand(time(NULL));

  //Declaração de variaveis para guardar o tempo de execucao
  clock_t startTime, finalTime;

  //Declaração de variaveis para contar o tempo total de execução para cada tipo de vetor
  double executionTime = 0;

  //Menu para pegar o número do vetor desejado
  do
  {
    printf("\n|--------------------------------------------------------|\n");
    printf("|             Escolha um tamanho de vetor                |\n");
    printf("|--------------------------------------------------------|\n");
    printf("|Opcao [1] - 140 mil elementos                           |\n");
    printf("|Opcao [2] - 120 mil elementos                           |\n");
    printf("|Opcao [3] - 100 mil elementos                           |\n");
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
      n = 140;
      break;

    case 2:
      n = 120;
      break;

    case 3:
      n = 100;
      break;

    case 4:
      n = 80;
      break;

    case 5:
      n = 50;
      break;

    default:
      printf("\n\nEssa opcao nao existe, tente novamente!!!\n\n");

      break;
    }

    while ((arraySize >= 1 && arraySize <= 5) && algorithm == 0)
    {
      printf("\nO tamanho do vetor escolhido foi: %ld elementos\n\n", n);

      //Zerando variáveis
      qtdComparacoes = 0, qtdTrocas = 0, c = 0, t = 0;
      startTime = 0, finalTime = 0;

      //Criando o vetor dinamicamente
      v = (long int *)malloc(n * (sizeof(long int)));

      if (v == NULL)
        exit(1);

      writeFile(n, v, algorithm);

      //Menu para escolher qual o tipo do vetor
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

      //Lê cada tipo de vetor escolhido pelo usuário
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

          for (int i = 0; i < n; i++)
          {
            printf("%ld\t", v[i]);
          }
          printf("\n\n");

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

          for (int i = 0; i < n; i++)
          {
            printf("%ld\t", v[i]);
          }
          printf("\n\n");

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

          for (int i = 0; i < n; i++)
          {
            printf("%ld\t", v[i]);
          }
          printf("\n\n");

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

          for (int i = 0; i < n; i++)
          {
            printf("%ld\t", v[i]);
          }
          printf("\n\n");

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

          for (int i = 0; i < n; i++)
          {
            printf("%ld\t", v[i]);
          }
          printf("\n\n");

          executionTime = (double)(finalTime - startTime) / CLOCKS_PER_SEC;
          qtdTrocas = t;
          qtdComparacoes = c;

          printResult(executionTime, qtdComparacoes, qtdTrocas);

          break;

        case 6:
          // for (int i = 0; i < n; i++)
          // {
          //   printf("%ld\t", v[i]);
          // }

          startTime = clock(); //inicia contagem do tempo
          quickSort(v, 0, n - 1, &c, &t);
          finalTime = clock(); // finaliza contagem do tempo

          printf("\n\nVc escolheu ordenar os elementos do vetor com o Quick Sort\n\n");

          writeFile(n, v, algorithm);

          // for (int i = 0; i < n; i++)
          // {
          //   printf("%ld\t", v[i]);
          // }
          printf("\n\n");

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

          for (int i = 0; i < n; i++)
          {
            printf("%ld\t", v[i]);
          }
          printf("\n\n");

          executionTime = (double)(finalTime - startTime) / CLOCKS_PER_SEC;
          qtdTrocas = t;
          qtdComparacoes = c;

          printResult(executionTime, qtdComparacoes, qtdTrocas);

          break;

        case 8:
          criArquivoTeste("dados.txt", n, arrayType, v);
          startTime = clock(); //inicia contagem do tempo
          mergeSortExterno("dados.txt");
          finalTime = clock(); // finaliza contagem do tempo
          verificaArquivoOrdenado("dados.txt");

          printf("\n\n");

          executionTime = (double)(finalTime - startTime) / CLOCKS_PER_SEC;
          qtdTrocas = t;
          qtdComparacoes = c;

          printResult(executionTime, qtdComparacoes, qtdTrocas);

          break;

        default:
          printf("\n\nEssa opcao nao existe, tente novamente!!!\n\n");

          break;
        }
      }
    }
    algorithm = 0;
  } while (arraySize != 0);
  free(v);
  return 0;
}

/*Funções*/
void insertionSort(long int *v, long int n, long int *c, long int *t)
{
  int i, j, aux;
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

int menor(long int a, long int b, long int *c)
{
  (*c)++;
  return (a < b);
}

void selectionSort(long int *v, long int n, long int *c, long int *t)
{
  int i, j, min, aux;
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

void bubbleSort(long int *v, long int n, long int *c, long int *t)
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

void combSort(long int *v, long int n, long int *c, long int *t)
{
  int step = n, i, k, j, again = 1;
  int aux;

  while ((step = (int)(step / 1.3)) > 1)
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

void mergeSort(long int *v, long int p, long int r, long int *c, long int *t)
{
  if (p < r - 1)
  {
    int q = (p + r) / 2; //metade

    mergeSort(v, p, q, c, t);
    mergeSort(v, q, r, c, t);
    intercala(v, p, q, r, c, t);
  }
}

void intercala(long int *v, long int p, long int q, long int r, long int *c, long int *t)
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

void quickSort(long int *v, long int p, long int r, long int *c, long int *t)
{
  long int pivot;

  if (p < r)
  {
    pivot = hoareParticao(v, p, r, c, t);

    quickSort(v, p, pivot, c, t);
    quickSort(v, pivot + 1, r, c, t);
  }
}

int hoareParticao(long int *v, long int p, long int r, long int *c, long int *t)
{
  long int pivot = v[p];
  long int i = p - 1, j = r + 1, aux;

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

void heapify(long int *v, long int n, long int i, long int *c, long int *t)
{
  long int maior = i, esq = 2 * i + 1, dir = 2 * i + 2, aux;

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

void heapSort(long int *v, long int n, long int *c, long int *t)
{
  long int i, aux;

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

int compara(const void *a, const void *b)
{
  if (*(int *)a == *(int *)b)
    return 0; //iguais
  else if (*(int *)a < *(int *)b)
    return -1; //vem antes
  else
    return 1; //vem depois
}

void salvaArquivo(char *nome, int *V, int tam, int mudaLinhaFinal)
{
  int i;
  FILE *f = fopen(nome, "a");
  for (i = 0; i < tam - 1; i++)
    fprintf(f, "%d\n", V[i]);
  if (mudaLinhaFinal == 0)
    fprintf(f, "%d", V[tam - 1]);
  else
    fprintf(f, "%d\n", V[tam - 1]);
  fclose(f);
}

void criArquivoTeste(char *nome, long int n, int arrayType, long int *v)
{
  long int i;
  FILE *f = fopen(nome, "w");
  srand(time(NULL));

  switch (arrayType)
  {
  case 1:
    for (i = 1; i < n; i++)
      fprintf(f, "%d\n", rand() % 10);

    fprintf(f, "%d", rand() % 10);

    break;

  case 2:
    for (i = 1; i < n; i++)
      fprintf(f, "%ld\n", i);

    fprintf(f, "%ld", i);

    break;

  case 3:
    for (i = n - 1; i >= 1; i--)
      fprintf(f, "%ld\n", i);

    fprintf(f, "%ld", i);

    break;

  case 4:
    for (int i = 1; i < n; i++)
      fprintf(f, "%ld\n", v[i]);

    fprintf(f, "%ld", v[i]);

    break;
  }

  fclose(f);
}

int criaArquivosOrdenados(char *nome)
{
  int V[N];
  char novo[20];
  int cont = 0, total = 0;
  FILE *f = fopen(nome, "r");
  while (!feof(f))
  {
    fscanf(f, "%d", &V[total]);
    total++;
    if (total == N)
    {
      cont++;
      sprintf(novo, "Temp%d.txt", cont);
      qsort(V, total, sizeof(int), compara);
      salvaArquivo(novo, V, total, 0);
      total = 0;
    }
  }

  if (total > 0)
  {
    cont++;
    sprintf(novo, "Temp%d.txt", cont);
    qsort(V, total, sizeof(int), compara);
    salvaArquivo(novo, V, total, 0);
  }
  fclose(f);
  return cont;
}

void preencheBuffer(struct arquivo *arq, int T)
{
  int i;
  if (arq->f == NULL)
    return;

  arq->pos = 0;
  arq->MAX = 0;
  for (i = 0; i < T; i++)
  {
    if (!feof(arq->f))
    {
      fscanf(arq->f, "%d", &arq->buffer[arq->MAX]);
      arq->MAX++;
    }
    else
    {
      fclose(arq->f);
      arq->f = NULL;
      break;
    }
  }
}

int procuraMenor(struct arquivo *arq, int K, int T, int *menor)
{
  int i, idx = -1;
  for (i = 0; i < K; i++)
  {
    if (arq[i].pos < arq[i].MAX)
    {
      if (idx == -1)
        idx = i;
      else
      {
        if (arq[i].buffer[arq[i].pos] < arq[idx].buffer[arq[idx].pos])
          idx = i;
      }
    }
  }
  if (idx != -1)
  {
    *menor = arq[idx].buffer[arq[idx].pos];
    arq[idx].pos++;
    if (arq[idx].pos == arq[idx].MAX)
      preencheBuffer(&arq[idx], T);
    return 1;
  }
  else
    return 0;
}

void merge(char *nome, int K, int T)
{
  char novo[20];
  int i;
  int *buffer = (int *)malloc(T * sizeof(int));

  struct arquivo *arq;
  arq = (struct arquivo *)malloc(K * sizeof(struct arquivo));
  for (i = 0; i < K; i++)
  {
    sprintf(novo, "Temp%d.txt", i + 1);
    arq[i].f = fopen(novo, "r");
    arq[i].MAX = 0;
    arq[i].pos = 0;
    arq[i].buffer = (int *)malloc(T * sizeof(int));
    preencheBuffer(&arq[i], T);
  }

  //enquanto houver arquivos para processar
  int menor, qtdBuffer = 0;
  while (procuraMenor(arq, K, T, &menor) == 1)
  {
    buffer[qtdBuffer] = menor;
    qtdBuffer++;
    if (qtdBuffer == T)
    {
      salvaArquivo(nome, buffer, T, 1);
      qtdBuffer = 0;
    }
  }

  if (qtdBuffer != 0)
    salvaArquivo(nome, buffer, qtdBuffer, 1);

  for (i = 0; i < K; i++)
    free(arq[i].buffer);
  free(arq);
  free(buffer);
}

void mergeSortExterno(char *nome)
{
  char novo[20];
  int K = criaArquivosOrdenados(nome);
  int i, T = N / (K + 1);

  printf("\nVc escolheu ordenar os elementos do vetor com o Merge Sort Externo\n");

  printf("\nNro de arquivos:%d\n", K);
  printf("K:%d\n", T);

  remove(nome);
  merge(nome, K, T);

  for (i = 0; i < K; i++)
  {
    sprintf(novo, "Temp%d.txt", i + 1);
    remove(novo);
  }
  printf("Fim!\n");
}

void verificaArquivoOrdenado(char *nome)
{
  int v1, v2, erro = 0;
  FILE *f = fopen(nome, "r");
  fscanf(f, "%d", &v1);
  while (!feof(f))
  {
    fscanf(f, "%d", &v2);
    if (v2 < v1)
    {
      erro = 1;
      break;
    }
  }
  fclose(f);
  if (erro)
    printf("Valores fora de ordem!\n");
  else
    printf("Arquivo corretamente ordenado!\n");
}

void printResult(double executionTime, long int qtdComparacoes, long int qtdTrocas)
{
  printf("Tempo de execucao: %f segundos\n\n", executionTime);
  printf("Quantidade de comparacoes: %ld\n\n", qtdComparacoes);
  printf("Quantidade de trocas: %ld\n\n", qtdTrocas);

  printf("\n\nMuito obrigado, escolha outra opcao!!!\n\n");
}

void leVetor(long int *v, long int n, int arrayType)
{
  int i = 0;
  FILE *f;

  f = fopen("file.txt", "r");

  fscanf(f, "%ld", &v[i]);

  while (!feof(f))
  {
    i++;
    fscanf(f, "%ld", &v[i]);
  }

  fclose(f);
}

void writeFile(long int n, long int *v, int algorithm)
{
  FILE *fp, *fr;
  int i;
  /* open the file for writing*/
  fp = fopen("file.txt", "w");
  fr = fopen("result.txt", "w");

  /* write 10 lines of text into the file stream*/
  for (i = n - 1; i >= 0; i--)
  {
    fprintf(fp, "%d\n", i);
  }

  // if (algorithm != 0)
  // {
  //   for (i = 0; i < n; i++)
  //   {
  //     fprintf(fr, "%d\n", v[i]);
  //   }
  // }

  /* close the file*/
  fclose(fp);
  fclose(fr);

  // long int count = 0;
  // switch (arrayType)
  // {
  // case 1:
  //   //Preenche o vetor com valores aleatórios
  //   for (int i = 0; i < n; i++)
  //   {
  //     v[i] = rand() % 10; //Atribui um inteiro aleatorio entre 0 e 9
  //   }
  //   printf("\nVoce escolheu o seguinte vetor com elementos distintos e distribuidos de forma aleatoria\n\n");

  //   //Mostra o vetor com os elementos aleatórios
  //   for (int i = 0; i < n; i++)
  //   {
  //     printf("%ld\t", v[i]);
  //   }

  //   printf("\n\n");

  //   break;

  // case 2:
  //   //Preenche o vetor com elementos ordenados
  //   for (int i = 0; i < n; i++)
  //   {
  //     v[i] = i;
  //   }
  //   printf("\n\n----- Vetores com elementos distintos ja ordenados. -----\n\n");

  //   //Mostra o vetor com os elementos ordenados
  //   for (int i = 0; i < n; i++)
  //   {
  //     printf("%ld\t", v[i]);
  //   }

  //   printf("\n\n");

  //   break;

  // case 3:
  //   //Preenche o vetor com elementos ordenados de forma reversa
  //   count = 0;
  //   for (int i = n - 1; i >= 0; i--)
  //   {
  //     v[count] = i;
  //     count++;
  //   }
  //   printf("\n\n----- Vetores com elementos distintos ordenados de forma reversa. -----\n\n");

  //   //Mostra o vetor com os elementos ordenados de forma reversa
  //   // for (int i = 0; i < n; i++)
  //   // {
  //   //   printf("%ld\t", v[i]);
  //   // }

  //   printf("\n\n");

  //   break;

  // case 4:
  //   //Preenche o vetor com elementos aleatórios e repetidos
  //   count = 0;
  //   for (int i = 0; i < n; i++)
  //   {
  //     v[i] = i % 5;
  //   }
  //   for (int i = 0; i < n; i++)
  //   {
  //     v[i] = v[rand() % (n - 1)];
  //   }
  //   printf("\n\n----- Vetores onde os elementos estão distribuidos de forma aleatoria, -----\n");
  //   printf("----- porem, cada elemento aparece ao menos em quantidade igual ou superior a 5 por cento do tamanho do vetor. -----\n\n");

  //   //Mostra o vetor com os elementos aleatórios e repetidos
  //   for (int i = 0; i < n; i++)
  //   {
  //     printf("%ld\t", v[i]);
  //   }

  //   printf("\n\n");

  //   break;
  // default:
  // {
  //   printf("\n\nEssa opcao nao existe, tente novamente!!!\n\n");
  //   break;
  // }
  // }
}
