#include <stdio.h>
#include <stdlib.h>
#ifndef _LIST_API_
#define _LIST_API_

typedef struct listNode{
    void *data;
    struct listNode *next;
    struct listNode *previous;
} Node;


typedef struct listHead{
    Node *head;
    Node *tail;
    void(*printData)(void *toBePrinted);
    void(*deleteData)(void *toBeDeleted);
    int(*compare)(const void *first, const void *second);
} List;

Node *initializeNode(void * data);
List *initializeList(void(*printFunction)(void *toBePrinted), void(*deleteFunction)(void *toBeDeleted), int(*compareFunction)(const void *first, const void *second));
void deleteList (List *list);
int deleteSome(List *list,void *toBeDeleted);
void insertHead(List *list, void *toBeAdded);
void insertTail(List *list, void *toBeAdded);
void insertSpecific(List *list, void *toBeAdded);
void *returnHead(List *list);
void *returnTail(List *list);
void printList(List *list);
void printReverseList(List *list);
#endif

