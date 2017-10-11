#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "SchnarrListAPI.h"

typedef struct vehicleInfo {
    int readEnter;
    float timeEntered;
    float reachIntersection;
    float reachEnd;
    char cardinal;
    char direction;
     
} Vehicle;

void printNode(void *data);
void deleteNode(void *data);
int compareData(const void *first,const void *second);

int main(int argc, char *argv[])
{
    FILE *fp;
    List *line[4]; 
    Vehicle **vehicle = NULL;
    int multiplier;
    int allVehicles = 0;
    int lineVehc[4];
    int i;
    int j = 0;
    int buffLen = 0;
    double clock = 0.0;
    char buff[1024];
    char arrival[1024];
    if (argc != 2) {
        printf("Invalid command format");
        return 1;
    }
    fp = fopen(argv[1],"r");
    if (fp == NULL) {
        printf("Failed to open file");
        return 1;
    }

    for (i = 0;i < 4;i++) {
        line[i] = initializeList(printNode,deleteNode,compareData);
    }
    while (fgets(buff,1024,fp) != NULL) {
        buffLen = strlen(buff);
        if(buff[buffLen - 1] == '\n') {
            buff[buffLen - 1] = '\0';
        }
        for(i = 4;i < buffLen;i++) {
            if(isdigit(buff[i])){
                arrival[j] = buff[i]; 
            }else{
                break;
            }
            
        }
        vehicle = realloc(vehicle, sizeof(Vehicle *) * (allVehicles + 1));
        vehicle[allVehicles] = malloc(sizeof(Vehicle));
        vehicle[allVehicles]->readEnter = atoi(arrival);
        vehicle[allVehicles]->cardinal = buff[0];
        vehicle[allVehicles]->direction = buff[2];
        vehicle[allVehicles]->timeEntered = vehicle[allVehicles]->readEnter;
        allVehicles++;
        
    }

    fclose(fp);
    i = 0;
    j = 0;
    while(i < allVehicles) {
        for (j = 0; j < allVehicles; j++) {
            if (vehicle[j]->timeEntered  == clock) {
                i++;
                if (vehicle[j]->cardinal == 'N') {
                    printf("N");
                    insertHead(line[0], (void*)(vehicle[j]));
                    lineVehc[0] = lineVehc[0] + 1;
                } else if (vehicle[j]->cardinal == 'E') {
                    printf("E");
                    insertHead(line[1], (void*)(vehicle[j]));
                    lineVehc[1] = lineVehc[1] + 1;
                } else if (vehicle[j]->cardinal == 'S') {
                    printf("S");
                    insertHead(line[2], (void*)(vehicle[j]));
                    lineVehc[2] = lineVehc[2] + 1;
                } else if (vehicle[j]->cardinal == 'W') {
                    printf("W");
                    insertHead (line[3], (void*)(vehicle[j]));
                    lineVehc[3] = lineVehc[3] + 1;
                }
            }
        }
        clock = clock + 1;
    }

    clock = 1;
    multiplier = 1;
    if (returnHead(line[1]) == NULL) {
        printf("sdjfksd");

    }

    while (returnHead(line[0]) != NULL || returnHead(line[1]) != NULL || returnHead(line[2]) != NULL || returnHead(line[3]) != NULL){
        for (; clock < 10 * multiplier; clock++) {
            if (((Vehicle*)line[0]->tail)->timeEntered <= 10 * multiplier && ((Vehicle*)line[0]->tail)->timeEntered < ((Vehicle*)line[2]->tail)->timeEntered) {
                ((Vehicle*)line[0]->tail)->reachIntersection = clock;
                if (((Vehicle*)line[0]->tail)->direction == 'F') {
                    ((Vehicle*)line[0]->tail)->reachEnd = clock + 2;
                    clock = clock + 2;
                } else if (((Vehicle*)line[0]->tail)->direction == 'L') {
                    ((Vehicle*)line[0]->tail)->reachEnd = clock + 2.5;
                    clock = clock + 2.5;
                } else if (((Vehicle*)line[0]->tail)->direction == 'R') {
                    ((Vehicle*)line[0]->tail)->reachEnd = clock + 1;
                    clock = clock + 1;
                }
                printNode(line[0]->tail);
                deleteSome(line[0], line[0]->tail);
            }else if (((Vehicle*)line[2]->tail)->timeEntered <= 10 * multiplier && ((Vehicle*)line[0]->tail)->timeEntered > ((Vehicle*)line[2]->tail)->timeEntered) {
                ((Vehicle*)line[2]->tail)->reachIntersection = clock;
            if (((Vehicle*)line[2]->tail)->direction == 'F') {
                ((Vehicle*)line[2]->tail)->reachEnd = clock + 2;
                clock = clock + 2;
            } else if (((Vehicle*)line[2]->tail)->direction == 'L') {
                ((Vehicle*)line[2]->tail)->reachEnd = clock + 2.5;
                clock = clock + 2.5;
            } else if (((Vehicle*)line[2]->tail)->direction == 'R') {
                ((Vehicle*)line[2]->tail)->reachEnd = clock + 1;
                clock = clock + 1;
            }
            printNode(line[2]->tail);
            deleteSome(line[2], line[2]->tail);
        } else if (((Vehicle*)line[1]->tail)->timeEntered <= 10 * multiplier) {
            ((Vehicle*)line[1]->tail)->reachIntersection = clock;

        } else if (((Vehicle*)line[3]->tail)->timeEntered <= 10 * multiplier) {
            ((Vehicle*)line[3]->tail)->reachIntersection = clock;
        }
        }
        if (clock == 11 * multiplier && ((Vehicle*)line[0]->tail)->direction == 'L') {
            ((Vehicle*)line[0]->tail)->reachIntersection = clock;
            ((Vehicle*)line[0]->tail)->reachEnd = clock + 2.5;
            printNode(line[0]->tail);
            deleteNode(line[0]->tail);
        } else if(clock == 11 * multiplier && ((Vehicle*)line[2]->tail)->direction == 'L') {
            ((Vehicle*)line[2]->tail)->reachIntersection = clock;
            ((Vehicle*)line[2]->tail)->reachEnd = clock + 2.5;
            printNode(line[2]->tail);
            deleteNode(line[2]->tail);
        }
        clock = 15 * multiplier;
        for (; clock < 26 * multiplier; clock++) {
            if (((Vehicle*)line[1]->tail)->timeEntered <= 26 * multiplier && ((Vehicle*)line[1]->tail)->timeEntered < ((Vehicle*)line[3]->tail)->timeEntered) {
                ((Vehicle*)line[1]->tail)->reachIntersection = clock;
            if (((Vehicle*)line[1]->tail)->direction == 'F') {
                ((Vehicle*)line[1]->tail)->reachEnd = clock + 2;
                clock = clock + 2;
            } else if (((Vehicle*)line[1]->tail)->direction == 'L') {
                ((Vehicle*)line[1]->tail)->reachEnd = clock + 2.5;
                clock = clock + 2.5;
            } else if (((Vehicle*)line[1]->tail)->direction == 'R') {
                ((Vehicle*)line[1]->tail)->reachEnd = clock + 1;
                clock = clock + 1;
            }
            printNode(line[1]->tail);
            deleteSome(line[1], line[1]->tail);
        } else if(((Vehicle*)line[3]->tail)->timeEntered <= 26 * multiplier && ((Vehicle*)line[1]->tail)->timeEntered > ((Vehicle*)line[3]->tail)->timeEntered) {
            ((Vehicle*)line[3]->tail)->reachIntersection = clock;
            if (((Vehicle*)line[3]->tail)->direction == 'F') {
                ((Vehicle*)line[3]->tail)->reachEnd = clock + 2;
                clock = clock + 2;
            } else if (((Vehicle*)line[3]->tail)->direction == 'L') {
                ((Vehicle*)line[3]->tail)->reachEnd = clock + 2.5;
                clock = clock + 2.5;
            } else if (((Vehicle*)line[3]->tail)->direction == 'R') {
                ((Vehicle*)line[3]->tail)->reachEnd = clock + 1;
                clock = clock + 1;
            }
            printNode(line[3]->tail);
            deleteSome(line[3], line[3]->tail);
        } else if(((Vehicle*)line[0]->tail)->timeEntered <= 26 * multiplier) {
            ((Vehicle*)line[0]->tail)->reachIntersection = clock;

        } else if (((Vehicle*)line[2]->tail)->timeEntered <= 26 * multiplier) {
            ((Vehicle*)line[2]->tail)->reachIntersection = clock;
        }
    }
    if (clock == 31 * multiplier && ((Vehicle*)line[1]->tail)->direction == 'L') {
        ((Vehicle*)line[1]->tail)->reachIntersection = clock;
        ((Vehicle*)line[1]->tail)->reachEnd = clock + 2.5;
        printNode(line[1]->tail);
        deleteNode(line[1]->tail);
        } else if (clock == 31 * multiplier && ((Vehicle*)line[3]->tail)->direction == 'L') {
            ((Vehicle*)line[3]->tail)->reachIntersection = clock;
            ((Vehicle*)line[3]->tail)->reachEnd = clock + 2.5;
            printNode(line[3]->tail);
            deleteNode(line[3]->tail);
        }
        multiplier =  multiplier + 1;


    }

    return 0;
}

void printNode(void *data) 
{
    fprintf(stdout,"%c %c %.1f    %.2f    %.2f\n",((Vehicle*)data)->cardinal,((Vehicle*)data)->direction,((Vehicle*)data)->timeEntered,((Vehicle*)data)->reachIntersection,((Vehicle*)data)->reachEnd);
    return;
}

void deleteNode(void *data) 
{
    return;
}

int compareData(const void *first, const void *second)
{
    return 0;
}