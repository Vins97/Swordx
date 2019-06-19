#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "sorting.h"

void bubbleSort(analisys_t *start){
    int swapped;
    analisys_t *ptr1;
    analisys_t *lptr = NULL;
    if (start == NULL)
        return; 
    do{
        swapped = 0;
        ptr1 = start; 
        while (ptr1->next != lptr){			
            if (occCompare(ptr1)){ 
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }while (swapped);
}
int occCompare(analisys_t * w){
	return w->occurrency>w->next->occurrency;
}
void swap(analisys_t *a, analisys_t *b){
	int tOc;
    string tStr;
    strcpy(tStr,a->word);
    strcpy(a->word,b->word);
    strcpy(b->word,tStr);
    tOc = a->occurrency;
    a->occurrency=b->occurrency;
    b->occurrency = tOc;
}
