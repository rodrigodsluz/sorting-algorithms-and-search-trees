#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
  int key;                   // chave
  struct Node *left, *right; // ponteiros para as subarvores
  int n;                     // qtd de nos na subarvore
} Node;

//Funções para inserir
void insert(Node **root, int key);
Node *put(Node **x, int key);
int size(Node *x);

//Função para buscar chave
int searchKey(Node **root, int key);

//Funções para remover chave
Node *removeNode(Node *atual);
int removeKey(Node **root, int key);

//Funções para percorrer a arvore
void percursoPreOrdem(Node **root);
void percursoEmOrdem(Node **root);
void percursoPosOrdem(Node **root);

int main()
{
  Node *root = NULL;
  int menu, key, result;

  do
  {
    printf("\n|--------------------------------------------------------|\n");
    printf("|         Escolha uma operacao para arvore binaria       |\n");
    printf("|--------------------------------------------------------|\n");
    printf("|Opcao [1] - Inserir                                     |\n");
    printf("|Opcao [2] - Buscar chave                                |\n");
    printf("|Opcao [3] - Remover chave                               |\n");
    printf("|Opcao [4] - Percurso pre-ordem                          |\n");
    printf("|Opcao [5] - Percurso em-ordem                           |\n");
    printf("|Opcao [6] - Percurso pos-ordem                          |\n");
    printf("|                                                        |\n");
    printf("|Opcao [0] - Sair                                        |\n");
    printf("|--------------------------------------------------------|\n\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &menu);

    switch (menu)
    {
    case 1:
      printf("\nEntre com um key: ");
      scanf("%d", &key);

      insert(&root, key);

      printf("\nO key %d foi inserido na arvore binaria com sucesso!\n", key);
      break;

    case 2:
      printf("\nEntre com a chave a ser buscada: ");
      scanf("%d", &key);

      result = searchKey(&root, key);

      if (result == 1)
        printf("\nBusca realizada com sucesso! A chave %d foi encontrada\n", key);
      else
        printf("\nA chave %d nao foi encontrada!\n", key);
      break;

    case 3:
      printf("\nEntre com a chave a ser removida: ");
      scanf("%d", &key);

      result = removeKey(&root, key);

      if (result)
        printf("\nA chave %d foi removida com sucesso!\n", key);
      else
        printf("\nFalha em remover a chave %d!\n", key);
      break;

    case 4:
      percursoPreOrdem(&root);
      break;
    case 5:
      percursoEmOrdem(&root);
      break;

    case 6:
      percursoPosOrdem(&root);
      break;

    case 0:
      printf("\nObrigado, volte sempre!\n");
      break;

    default:
      printf("\n\nEssa opcao nao existe, tente novamente!!!\n\n");
      break;
    }

  } while (menu != 0);
  return 0;
}

void insert(Node **root, int key)
{
  (*root) = put(&(*root), key);
}

Node *put(Node **x, int key)
{
  if (!(*x))
  {
    (*x) = (Node *)malloc(sizeof(Node));
    (*x)->key = key;
    (*x)->left = (*x)->right = NULL;
    (*x)->n = 1;
    return (*x);
  }
  if (key < (*x)->key)
    (*x)->left = put(&(*x)->left, key);
  else
    (*x)->right = put(&(*x)->right, key);

  (*x)->n = 1 + size((*x)->left) + size((*x)->right);

  return (*x);
}

int size(Node *x)
{
  if (!x)
    return 0;
  else
    return x->n;
}

int searchKey(Node **root, int key)
{
  if (root == NULL)
    return 0;

  Node *atual = *root;

  while (atual != NULL)
  {
    if (key == atual->key)
      return 1;

    if (key < atual->key)
      atual = atual->left;
    else
      atual = atual->right;
  }
  return 0;
}

Node *removeNode(Node *atual)
{
  Node *no1, *no2;

  if (atual->left == NULL)
  {
    no2 = atual->right;
    free(atual);
    return no2;
  }

  no1 = atual;
  no2 = atual->left;

  while (no2->right != NULL)
  {
    no1 = no2;
    no2 = no2->right;
  }

  if (no1 != atual)
  {
    no1->right = no2->left;
    no2->left = atual->left;
  }

  no2->right = atual->right;

  free(atual);

  return no2;
}

int removeKey(Node **root, int key)
{
  if (root == NULL)
    return 0;

  Node *ant = NULL;
  Node *atual = *root;

  while (atual != NULL)
  {
    if (key == atual->key)
    {
      if (atual == *root)
        *root = removeNode(atual);
      else
      {
        if (ant->right == atual)
          ant->right = removeNode(atual);
        else
          ant->left = removeNode(atual);
      }
      return 1;
    }
    ant = atual;

    if (key > atual->key)
      atual = atual->right;
    else
      atual = atual->left;
  }
  return 0;
}

void percursoPreOrdem(Node **root)
{
  if (root == NULL)
    return;

  if (*root != NULL)
  {
    printf("\n%d\n", (*root)->key);
    percursoPreOrdem(&((*root)->left));
    percursoPreOrdem(&((*root)->right));
  }
}

void percursoEmOrdem(Node **root)
{
  if (root == NULL)
    return;

  if (*root != NULL)
  {
    percursoEmOrdem(&((*root)->left));
    printf("\n%d\n", (*root)->key);
    percursoEmOrdem(&((*root)->right));
  }
}

void percursoPosOrdem(Node **root)
{
  if (root == NULL)
    return;

  if (*root != NULL)
  {
    percursoPosOrdem(&((*root)->left));
    percursoPosOrdem(&((*root)->right));
    printf("\n%d\n", (*root)->key);
  }
}