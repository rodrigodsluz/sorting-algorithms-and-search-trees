#include <stdio.h>
#include <stdlib.h>

#define MAX 13

struct node
{
    int key;
    struct node *next;
};

int chaveDivisao(int chave, int n);
void insertKey(struct node **hashTable, int value);
int searchKey(struct node **hashTable, int value);
void printHashTable(struct node **hashTable);

int main()
{
    int menu, key;

    struct node *hashTable[MAX];

    for (int i = 0; i < MAX; i++)
        hashTable[i] = NULL;

    do
    {
        scanf("%d", &menu);

        switch (menu)
        {
        case 1:
            scanf("%d", &key);

            insertKey(hashTable, key);

            break;

        case 2:
            scanf("%d", &key);

            if (searchKey(hashTable, key))
                printf("%d\n", key);
            else
                printf("x\n");

            break;

        case 3:
            printHashTable(hashTable);

            break;

        case 9:
            break;
        }
    } while (menu != 9);

    return 0;
}

int chaveDivisao(int chave, int n)
{
    return (chave & 0x7FFFFFFF) % n;
}

void insertKey(struct node **hashTable, int value)
{
    struct node *no = malloc(sizeof(struct node));
    no->key = value;
    no->next = NULL;

    int index = chaveDivisao(value, MAX);

    if (hashTable[index] == NULL)
        hashTable[index] = no;
    else
    {
        struct node *aux = hashTable[index];

        while (aux->next)
            aux = aux->next;

        aux->next = no;
    }
}

int searchKey(struct node **hashTable, int value)
{
    int index = chaveDivisao(value, MAX);

    struct node *aux = hashTable[index];

    while (aux)
    {
        if (aux->key == value)
            return 1;

        aux = aux->next;
    }
    return 0;
}

void printHashTable(struct node **hashTable)
{
    for (int i = 0; i < MAX; i++)
    {
        struct node *aux = hashTable[i];

        printf("[%d]: ", i);

        while (aux)
        {
            printf("%d ", aux->key);
            aux = aux->next;
        }

        printf("\n");
    }
}
