/**
    Rodrigo Duarte Silva Luz
    Yasmin Karolyne Aniceto Carvalho
    Matheus de Souza
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
  int key;
  struct Node *left, *right;
  bool color; //"true" é red e "false" é black
} Node;

/**
    A funcao put faz a insercao de uma nova chave em seu local correto e 
    utiliza quando necessário outras funções para ajustar os nos e as cores da arvore 
     fazendo com que ela siga os padroes da Left-Leaning Red-Black de Sedgewick. 
    @param x raiz da sub-arvore.
    @param key A chave a ser inserida.
*/
Node *put(Node *x, int key);

/**
    A funcao rotateLeft executa uma rotacao a esquerda
    na sub-arvore recebida como parametro.
    @param h O ponteiro da sub-arvore a ser rotacionada.
    @return o ponteiro para o no rotacionado.
*/
Node *rotateLeft(Node *h);

/**
    A funcao rotateRight executa uma rotacao a direita
    na sub-arvore recebida como parametro.
    @param h O ponteiro da sub-arvore a ser rotacionada.
    @return o ponteiro para o no rotacionado.
*/
Node *rotateRight(Node *h);

/**
    A funcao flipColors faz com que os dois filhos se tornem pretos e o pai vermelho
    @param x No para fazer a troca de cores
*/
void flipColors(Node *x);

/**
    A funcao isRed verifica se o node e vermelho ou não
    @param x no para verificar a cor
*/
int isRed(Node *x);

/**
    A funcao searchKeyOrColor pode ser utilizada tanto para pesquisar 
    pela chave ou pela cor do no
    @param root A raiz da arvore.
    @param key A chave a ser pesquisada ou a chave do nó para pesquisar a cor
    @param isColor Variável utilizada para verificar se o usuário apenas quer pesquisar
    uma chave ou pesquisar a cor do nó, se o valor for 1 será 
    pesquisado a cor do nó, se for 0 a chave será pesquisada
    @return 1 se a chave for pesquisada e existir ou 0 senão existir, e se for pesquisada a cor
    do nó a cor dele será retornada (true ou false)
*/
int searchKeyOrColor(Node *root, int key, int isColor);

/**
    A funcao percursoPreOrdem mostra os valores da arvore em pre-ordem
    @param root A raiz da arvore
*/
void percursoPreOrdem(Node *root);

/**
    A funcao percursoEmOrdem mostra os valores da arvore em ordem
    @param root A raiz da arvore
*/
void percursoEmOrdem(Node *root);

/**
    A funcao percursoPosOrdem mostra os valores da arvore em pos-ordem
    @param root A raiz da arvore
*/
void percursoPosOrdem(Node *root);

/**
    A funcao freeNode libera cada no da arvore
    @param no O ponteiro para o no
*/
void freeNode(Node *no);

/**
    A funcao freeTree chama a funcao freeNode e depois libera a raiz da arvore
    @param root A raiz da arvore
*/
void freeTree(Node *root);

/**
    Funcao principal.
    Ponto de inicio do programa.
    @return zero.
*/
int main()
{
  Node *root = NULL; // A raiz da arvore.
  int menu, key, result;

  do
  {
    scanf("%d", &menu);

    switch (menu)
    {
    case 1:
      scanf("%d", &key);

      root = put(root, key);

      root->color = false;

      break;

    case 2:
      scanf("%d", &key);

      result = searchKeyOrColor(root, key, 0);

      if (result)
        printf("%d\n", key);
      else
        printf("x\n");

      break;

    case 3:
      percursoPreOrdem(root);
      printf("\n");

      break;
    case 4:
      percursoEmOrdem(root);
      printf("\n");

      break;

    case 5:
      percursoPosOrdem(root);
      printf("\n");

      break;

    case 6:
      scanf("%d", &key);

      result = searchKeyOrColor(root, key, 1);

      if (result == true)
        printf("R\n");
      else
        printf("B\n");

      break;

    case 7:
      //freeTree(root);
      break;

    default:
      printf("\n\nEssa opcao nao existe, tente novamente!!!\n\n");
      break;
    }

  } while (menu != 7);
  return 0;
}

Node *put(Node *x, int key)
{
  if (x == NULL)
  {
    Node *x = (Node *)malloc(sizeof(Node));

    if (x == NULL)
      exit(1);

    x->left = x->right = NULL;
    x->key = key;
    x->color = true;

    return x;
  }

  if (key < x->key)
    x->left = put(x->left, key);
  else if (key > x->key)
    x->right = put(x->right, key);
  else
    return x;

  if (isRed(x->right) && !isRed(x->left))
  {
    x = rotateLeft(x);
    bool temp = x->color;
    x->color = x->left->color;
    x->left->color = temp;
  }

  if (isRed(x->left) && isRed(x->left->left))
  {
    x = rotateRight(x);
    bool temp = x->color;
    x->color = x->right->color;
    x->right->color = temp;
  }

  if (isRed(x->left) && isRed(x->right))
    flipColors(x);

  return x;
}

Node *rotateLeft(Node *h)
{
  Node *child = h->right;
  Node *childLeft = child->left;
  child->left = h;
  h->right = childLeft;

  return child;
}

Node *rotateRight(Node *h)
{
  Node *child = h->left;
  Node *childRight = child->right;
  child->right = h;
  h->left = childRight;

  return child;
}

int isRed(Node *x)
{
  if (x == NULL)
    return 0;

  return (x->color == true);
}

void flipColors(Node *x)
{
  x->color = !x->color;
  x->left->color = false;
  x->right->color = false;
}

int searchKeyOrColor(Node *root, int key, int isColor)
{
  if (root == NULL)
    return 0;

  Node *current = root;

  while (current != NULL)
  {
    if (key == current->key)
    {
      if (isColor)
        return current->color;

      return 1;
    }

    if (key < current->key)
      current = current->left;
    else
      current = current->right;
  }

  return 0;
}

void percursoPreOrdem(Node *root)
{
  if (root == NULL)
    return;

  if (root != NULL)
  {
    printf("%d ", (root)->key);
    percursoPreOrdem(((root)->left));
    percursoPreOrdem(((root)->right));
  }
}

void percursoEmOrdem(Node *root)
{
  if (root == NULL)
    return;

  if (root != NULL)
  {
    percursoEmOrdem(((root)->left));
    printf("%d ", (root)->key);
    percursoEmOrdem(((root)->right));
  }
}

void percursoPosOrdem(Node *root)
{
  if (root == NULL)
    return;

  if (root != NULL)
  {
    percursoPosOrdem(((root)->left));
    percursoPosOrdem(((root)->right));
    printf("%d ", (root)->key);
  }
}

void freeNode(Node *no)
{
  if (no == NULL)
    return;
  freeNode(no->left);
  freeNode(no->right);
  free(no);
  no = NULL;
}

void freeTree(Node *root)
{
  if (root == NULL)
    return;
  freeNode(root);
  free(root);
}