/*
 * Andrew Budihardja
 */

#include <stdio.h>
#include <stdlib.h>
#include "mallok.h"

void *my_heap;
struct ListNode;

typedef struct ListNode{

    struct ListNode *next;//pointer to the next node
    unsigned char inuse;// 0 means free, 1 means in use
    unsigned int start_of_block;//int which indicates the offset of block address in the private heap. add my_heap to get physical address
    unsigned int size_of_block;
} Node;

Node *head;
int total;//total number of assigned and free blocks
unsigned int size_of_heap;

/**
 *swaps pointer between two nodes in the linkedlist
 */
void swap_ptr(Node* tmpPtr, Node* tmpNxt){

    Node* temp = (Node*)malloc(sizeof(Node));

    temp->inuse = tmpPtr->inuse;
    temp->size_of_block = tmpPtr->size_of_block;
    temp->start_of_block = tmpPtr->start_of_block;

    tmpPtr->inuse = tmpNxt->inuse;
    tmpPtr->size_of_block = tmpNxt->size_of_block;
    tmpPtr->start_of_block = tmpNxt->start_of_block;

    tmpNxt->inuse = temp->inuse;
    tmpNxt->size_of_block = temp->size_of_block;
    tmpNxt->start_of_block = temp->start_of_block;

    free(temp);
}

/**
 *sorts the linkedlist data
 */
void list_sort(){

    if(total ==0 || total == 1){
    		return; //empty list and single element are already sorted
    }
    Node* iptr; Node* jptr; Node* rptr;
    iptr = head;
    int i = 0, j = 0;

    for(i = 1; i < total; i++){

        jptr = iptr; rptr = jptr->next;
        for(j = 0; j < total-1; j++){
            if(jptr->start_of_block > rptr->start_of_block){
                swap_ptr(jptr, rptr);
            }
            jptr = rptr;
            rptr = jptr->next;
        }
    }
}

/**
 *prints heap information and address
 */
void print_my_heap(){

    printf("Heap Info\n");
    Node* temporary = head;
    int i = 0;

    for(; i < total;  i++){
        printf("In Use: %d, Size of: %d, Start of: %d\n", temporary->inuse, temporary->size_of_block, temporary->start_of_block);
        temporary = temporary->next;
    }

}

/**
 *merges the linkedlist data of malloc space.
 */
void list_merge(){

    if(total ==0 || total == 1) {
    		return; //empty list and single element are already merged
    }
    Node* iptr; Node* jptr; Node* rptr;
    iptr = head;
    int i = 0, j = 0;

    for(i = 1; i < total - 1; i++){
        if(iptr->inuse == 0){

            //printf("found free block: %d\n", iptr->start_of_block);
            if(iptr->next->inuse == 0){
                //printf("found free block: %d\n", iptr->next->start_of_block);
                iptr->size_of_block = iptr->size_of_block + iptr->next->next->size_of_block;
                rptr = iptr->next;
                iptr->next = iptr->next->next;
                free(rptr);
                total = total - 1;
            }
        }
        iptr = iptr->next;
    }

}


void create_pool(int size){

    my_heap = malloc(size*sizeof(char));
    head = malloc(sizeof(Node));
    head->next = NULL;
    head->inuse = 0;
    head->start_of_block = (int)my_heap;
    head->size_of_block = size;
    total = 1;
    size_of_heap = size;
    //printf("%d\t%d\t%d\n", head->next, head->start_of_block, head->size_of_block);

}

void *my_malloc(int size){

    Node* temp = head;
    int i = 0;

    for(; i < total; i++){
        if(temp->size_of_block > size && !(temp->inuse)){//found a block of bigger size
            Node* temp2 = malloc(sizeof(Node));
            temp2->inuse = 0;
            temp2->next = temp->next;
            temp2->size_of_block = temp->size_of_block - size;
            temp2->start_of_block = temp->start_of_block + size;
            temp->inuse = 1;
            temp->size_of_block = size;
            temp->next = temp2;
            total = total + 1;
            return (my_heap + temp->start_of_block);
        }else if(temp->size_of_block == size && !(temp->inuse)){//found a block of exact size
            temp->inuse = 1;
            return (my_heap + temp->start_of_block);
        }else{//the current block is less than the size requested
            temp = temp->next;
        }
    }
    return NULL;
}

void my_free(void *block){

    void* addr = block - my_heap;

    if(addr < my_heap){

    }else if (addr > my_heap + size_of_heap){

    }else{

        Node* tmp = head;
        int i = 0;

        for(; i < total; i++){
            if(tmp->start_of_block == (int) addr){
                tmp->inuse = 0;
                list_sort();
                list_merge();
                return;
            }else{
                tmp = tmp->next;
            }
        }
    }
}
