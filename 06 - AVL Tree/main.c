/**
    Rodrigo Duarte Silva Luz
    Yasmin Karolyne Aniceto Carvalho
    Matheus de Souza
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
    Esta estrutura representa o no de uma arvore AVL.
*/
typedef struct Node
{
  int key;                   // chave
  struct Node *left, *right; // ponteiros para as subarvores
  int n;                     // qtd de nos na subarvore - size na implementacao de Sedgewick
  int height;                // altura da subarvore
} Node;

/**
    A funcao balance e responsavel por realizar o balaceamento de um no
    apos o processo de insercao e/ou remocao de um key, de modo
    a manter a propriedade da arvore AVL.
    @param x O endereco do ponteiro do no a ser balanceado.
    @return o no da arvore AVL, agora balanceado.
*/
Node *balance(Node **x);

/**
    A funcao balanceFactor calcula o fator de balanceamento de um no.
    @param x O no cujo fator de balanceamento deve ser calculado.
    @return o fator de balanceamento do no.
*/
int balanceFactor(Node *x);

/**
    A funcao height devolve a altura da maior sub-arvore do no
    recebido como parametro.
    @param x o no cuja altura deve ser calculada.
    @return a altura da maior sub-arvore do no.
*/
int height(Node *x);

/**
    A funcao insert e responsavel por inserir uma nova chave
    na arvore AVL.
    @param root A raiz da arvore.
    @param key O key a ser inserido.
*/
void insert(Node **root, int key);

/**
    A funcao put percorre as sub-arvores e realiza a insercao
    de uma nova chave em seu local correto. Esta e uma funcao
    auxiliar, invocada pela funcao insert, e nao deve ser
    explicitamente utilizada pelo usuario/programador.
    @param A raiz da sub-arvore.
    @param key O key a ser inserido.
*/
Node *put(Node **x, int key);

/**
    A funcao rotateLeft executa uma rotacao simples a esquerda
    na sub-arvore recebida como parametro.
    @param h O ponteiro da sub-arvore a ser rotacionada.
    @return o ponteiro para o no rotacionado.
*/
Node *rotateLeft(Node *h);

/**
    A funcao rotateRight executa uma rotacao simples a direita
    na sub-arvore recebida como parametro.
    @param h O ponteiro da sub-arvore a ser rotacionada.
    @return o ponteiro para o no rotacionado.
*/
Node *rotateRight(Node *h);

/**
    A funcao size devolve o numero de nos na sub-arvore recebida
    como parametro.
    @param x O ponteiro para a sub-arvore.
    @return a quantidade de nos na sub-arvore.
*/
int size(Node *x);

/**
    A funcao searchKeyOrBalanceFactor pode ser utilizada tanto para pesquisar 
    pela chave ou pelo fator de balanceamento
    @param root A raiz da arvore.
    @param key A chave a ser pesquisada ou a chave do nó para pesquisar o fator de balanceamento
    @param isBalanceFactor Variável utilizada para verificar se o usuário apenas quer pesquisar
    uma chave ou pesquisar o fator de balanceamento do nó, se o valor for 1 será 
    pesquisado o fator de balanceamento, se for 0 a chave será pesquisada
    @return 1 se a chave for pesquisada e existir ou 0 senão existir, e se for pesquisado o
    fator de balanceamento retornará o valor dele ou -5 (número aleatório escolhido) 
    caso não tenha fator de balanceamento
*/
int searchKeyOrBalanceFactor(Node **root, int key, int isBalanceFactor);

/**
    A funcao removeKey percorre as sub-arvores e faz a remoção da chave escolhida pelo usuário.
    @param x Ponteiro da sub-arvore
    @param key A chave que será removida
    @return O ponteiro para o no
*/
Node *removeKey(Node **x, int key);

/**
    A funcao removeMin remove o menor valor da sub-arvore.
    @param x Ponteiro da sub-arvore
    @return O ponteiro para o no
*/
Node *removeMin(Node **x);

/**
    A funcao min retorna o no com o menor valor da sub-arvore
    @param x Ponteiro da sub-arvore
    @return o no com o menor valor da sub-arvore
*/
Node *min(Node *x);

/**
    A funcao percursoPreOrdem mostra os valores da arvore em pre-ordem
    @param root A raiz da arvore
*/
void percursoPreOrdem(Node **root);

/**
    A funcao percursoEmOrdem mostra os valores da arvore em ordem
    @param root A raiz da arvore
*/
void percursoEmOrdem(Node **root);

/**
    A funcao percursoPosOrdem mostra os valores da arvore em pos-ordem
    @param root A raiz da arvore
*/
void percursoPosOrdem(Node **root);

/**
    A funcao freeNode libera cada no da arvore
    @param no O ponteiro para o no
*/
void freeNode(Node *no);

/**
    A funcao freeAVLTree chama a funcao freeNode e depois libera a raiz da arvore
    @param root A raiz da arvore
*/
void freeAVLTree(Node **root);

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

      insert(&root, key);

      break;

    case 2:
      scanf("%d", &key);

      result = searchKeyOrBalanceFactor(&root, key, 0);

      if (result)
        printf("%d\n", key);
      else
        printf("x\n");

      break;

    case 3:
      scanf("%d", &key);

      root = removeKey(&root, key);

      break;

    case 4:
      percursoPreOrdem(&root);
      printf("\n");

      break;
    case 5:
      percursoEmOrdem(&root);
      printf("\n");

      break;

    case 6:
      percursoPosOrdem(&root);
      printf("\n");

      break;

    case 7:
      scanf("%d", &key);

      result = searchKeyOrBalanceFactor(&root, key, 1);

      if (result != -5)
        printf("%d\n", result);

      break;

    case 8:
      //freeAVLTree(&root);
      break;

    default:
      printf("\n\nEssa opcao nao existe, tente novamente!!!\n\n");
      break;
    }

  } while (menu != 8);
  return 0;
}

Node *balance(Node **x)
{
  if (balanceFactor((*x)) > 1)
  {
    if (balanceFactor((*x)->right) < 0)
      (*x)->right = rotateRight((*x)->right);
    (*x) = rotateLeft((*x));
  }
  else if (balanceFactor((*x)) < -1)
  {
    if (balanceFactor((*x)->left) > 0)
      (*x)->left = rotateLeft((*x)->left);
    (*x) = rotateRight((*x));
  }
  return (*x);
}

int balanceFactor(Node *x)
{
  return height(x->right) - height(x->left);
}

int height(Node *x)
{
  if (!x)
    return -1;
  return x->height;
}

void insert(Node **root, int key)
{
  put(&(*root), key);
}

Node *put(Node **x, int key)
{
  if (!(*x))
  {
    (*x) = (Node *)malloc(sizeof(Node));
    (*x)->key = key;
    (*x)->left = (*x)->right = NULL;
    (*x)->n = 1;
    (*x)->height = 0;
    return (*x);
  }

  if (key < (*x)->key)
    put(&(*x)->left, key);
  else
    put(&(*x)->right, key);

  (*x)->n = 1 + size((*x)->left) + size((*x)->right);
  (*x)->height = 1 + fmax(height((*x)->left), height((*x)->right));

  return balance(&(*x));
}

Node *rotateLeft(Node *h)
{
  Node *x = h->right;
  h->right = x->left;
  x->left = h;
  x->n = h->n;
  h->n = 1 + size(h->left) + size(h->right);
  h->height = 1 + fmax(height(h->left), height(h->right));
  x->height = 1 + fmax(height(x->left), height(x->right));
  return x;
}

Node *rotateRight(Node *h)
{
  Node *x = h->left;
  h->left = x->right;
  x->right = h;
  x->n = h->n;
  h->n = 1 + size(h->left) + size(h->right);
  h->height = 1 + fmax(height(h->left), height(h->right));
  x->height = 1 + fmax(height(x->left), height(x->right));
  return x;
}

int size(Node *x)
{
  if (!x)
    return 0;
  return x->n;
}

int searchKeyOrBalanceFactor(Node **root, int key, int isBalanceFactor)
{
  if (root == NULL)
    return 0;

  Node *current = *root;

  while (current != NULL)
  {
    if (key == current->key)
    {
      if (isBalanceFactor)
        return balanceFactor(current);

      return 1;
    }

    if (key < current->key)
      current = current->left;
    else
      current = current->right;
  }
  if (isBalanceFactor)
    return -5;

  return 0;
}

Node *removeMin(Node **x)
{
  if ((*x)->left == NULL)
    return (*x)->right;
  (*x)->left = removeMin(&(*x)->left);
  (*x)->n = 1 + size((*x)->left) + size((*x)->right);
  (*x)->height = 1 + fmax(height((*x)->left), height((*x)->right));
  return balance(&(*x));
}

Node *min(Node *x)
{
  if (x->left == NULL)
    return x;

  return min(x->left);
}

Node *removeKey(Node **x, int key)
{
  if (x == NULL)
    return 0;

  if (key < (*x)->key)
    (*x)->left = removeKey(&(*x)->left, key);
  else if (key > (*x)->key)
    (*x)->right = removeKey(&(*x)->right, key);
  else
  {
    if ((*x)->left == NULL)
      return (*x)->right;
    else if ((*x)->right == NULL)
      return (*x)->left;
    else
    {
      Node *y = (*x);
      (*x) = min((*x)->right);
      (*x)->right = removeMin(&(y)->right);
      (*x)->left = y->left;
    }
  }
  (*x)->n = 1 + size((*x)->left) + size((*x)->right);
  (*x)->height = 1 + fmax(height((*x)->left), height((*x)->right));
  return balance(&(*x));
}

void percursoPreOrdem(Node **root)
{
  if (root == NULL)
    return;

  if (*root != NULL)
  {
    printf("%d ", (*root)->key);
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
    printf("%d ", (*root)->key);
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
    printf("%d ", (*root)->key);
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

void freeAVLTree(Node **root)
{
  if (root == NULL)
    return;
  freeNode(*root);
  free(root);
}