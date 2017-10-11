#include <stdio.h>
#include <stdlib.h>
#include "../include/SchnarrListAPI.h"

Node *initializeNode(void *data){
    Node *node = malloc(sizeof(Node));
    if(node != NULL){
        node->data = data;
        node->next = NULL;
        node->previous = NULL;
    }
    return node;
}

List *initializeList(void(*printFunction)(void *toBePrinted), void(*deleteFunction)(void *toBeDeleted), int (*compareFunction)(const void *first,const void *second)) {
    List *list = malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->compare = compareFunction;
    list->printData = printFunction;
    list->deleteData = deleteFunction;

    return list;
}

void deleteList(List *list){
    if(list == NULL){
        return;
    }else{
        Node *node = list->head;
        while(node != NULL){
            list->deleteData(node->data);
            Node *tmpNode = node;
            node = node->next;
            free(tmpNode);
        }
    }
    free(list);
}

int deleteSome(List *list,void *toBeDeleted){
    if(list == NULL){
        return 0;

    }else{
        Node *node = list->head;
        if(node == NULL){
            return 0;

        }
    
        while(node->data != toBeDeleted){
            node = node->next;
            if(node == NULL){
                return -1;
            }
        }
        if(node->previous == NULL){
            list->head = node->next;
            list->head->previous = NULL;
        }else if(node->next == NULL){
            list->tail = node->previous;
            list->tail->next = NULL;
        }else{
            node->previous->next = node->next;
            node->next->previous = node->previous;
        }
            list->deleteData(node->data);                                                                                                                                                                                                                                                                                                                                                                                                      
            free(node);
            return EXIT_SUCCESS;
    
        }
    }


void insertHead(List *list, void *toBeAdded){
    if(list != NULL){
        Node *newNode = initializeNode(toBeAdded);
        newNode->next = list->head;
        if(list->head != NULL){
            list->head->previous = newNode;
        }
        list->head = newNode;
        if(list->tail == NULL){
            list->tail = list->head;
        }

    }
}

void insertTail(List *list, void *toBeAdded){
    if(list != NULL){
        Node *newNode = initializeNode(toBeAdded);
        newNode->previous = list->tail;
        if(list->tail != NULL){
            list->tail->next = newNode;
        }
        list->tail = newNode;
        if(list->head == NULL){
            list->head = list->tail;
        }
        
    }
}

void insertSpecific(List *list, void *toBeAdded){
    if(list != NULL)
    {
        Node *node = list->head;
        if(node != NULL){
            while(list->compare(toBeAdded, node->data) >= 0){
                node = node->next;
                if(node != NULL){
                    return ;
                }
            }
            Node *new = initializeNode(toBeAdded);
            if(node == NULL){
                new->previous = list->tail;
                list->tail->next = new;
                list->tail = new;
            }else if(node->previous == NULL){
                list->head = new;
                new->next = node;
                node->previous = new;
            }else{
                node->previous->next = new;
                new->previous = node->previous;
                new->next = node;
                node->previous = new;
            }
        }else if(node == NULL){
            insertHead(list, toBeAdded);
        }
    }
}

void *returnHead(List *list){
    if(list->head == NULL){
        return NULL;
    }else{
       return  list->head->data;
    }
}

void *returnTail(List *list){
    if(list->tail == NULL){
        return NULL;
    }else{
        return list->head->data;
    }
}

void printList(List *list){
    if(list != NULL){
        Node *node = list->head;
        while(node != NULL){
            list->printData(node->data);
            node = node->next;
        }
    }
}

void printReverseList(List *list){
    if(list != NULL){
        Node *node = list->tail;
        while(node != NULL){
            list->printData(node->data);
            node = node->previous;
        }
    }
}