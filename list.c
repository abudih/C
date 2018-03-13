/*
 *Andrew Budihardja
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "list.h"

/**
 * * returns 0 if the word does not exist
 * in the redBadge file as well
 * as if there is no nodes that
 * have been created to store these words.
 * returns 1 if word exists and matches
 * the word and adds the count of the rcount.
 */
int check_word_redBadge(char* wrr){

    if(total == 0){
    		return 0;
    }
    int i = 0;
    item * curr = head;

    for(; i < total; i++){
        if(strcmp(curr->word, wrr) == 0){
            curr->rCount += 1;
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}

/**
 * returns 0 if the word does not exist
 * in the LittleRegiment file as well
 * as if there is no nodes that
 * have been created to store these words.
 * returns 1 if word exists and matches
 * the word and adds the count of the lcount.
 */
int check_word_littleRegiment(char* wrr){

    if(total == 0){
    		return 0;
    }
    int i = 0; item * curr = head;
    for(; i < total; i++){
        if(strcmp(curr->word, wrr) == 0){
            curr->lCount += 1;
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}

/**
 *checks whether the word exists/equal in the
 *array read from redBadge file, if there is
 *no nodes that have been allocated to store
 *the words, this function creates them and
 *adds the total as a counter.
 */
void list_insertr(char* arr){

    int c = check_word_redBadge(arr);
    if(c == 0){
        item * curr;
        curr = (item *)malloc(sizeof(item));
        curr->next = head;
        curr->rCount = 1;
        curr->lCount = 0;
        strcpy(curr->word, arr);
        head = curr;
        total = total + 1;
    }
}

/**
 *checks whether the word exists/equal in the
 *array read from littleRegiment file, if there is
 *no nodes that have been allocated to store
 *the words, this function creates them and
 *adds the total as a counter.
 */
void list_insertl(char* arr){

    int c = check_word_littleRegiment(arr);
    if(c == 0){
        item * curr;
        curr = (item *)malloc(sizeof(item));
        curr->next = head;
        curr->lCount = 1;
        curr->rCount = 0;
        strcpy(curr->word, arr);
        head = curr;
        total = total + 1;
    }
}

/**
 *swaps the pointer
 *from the nodes that controls the
 *words in littleRegiment
 *and the second nodesthat controls
 *the words in redBadge
 */
void swap_ptr(item * tempPointer, item * tempNext){


    item * tmp = (item *)malloc(sizeof(item));
    strcpy(tmp->word, tempPointer->word);
    tmp->lCount = tempPointer->lCount;
    tmp->bCount = tempPointer->bCount;
    tmp->rCount = tempPointer->rCount;
    strcpy(tempPointer->word, tempNext->word);
    tempPointer->lCount = tempNext->lCount;
    tempPointer->bCount = tempNext->bCount;
    tempPointer->rCount = tempNext->rCount;
    strcpy(tempNext->word, tmp->word);
    tempNext->lCount = tmp->lCount;
    tempNext->bCount = tmp->bCount;
    tempNext->rCount = tmp->rCount;
    free(tmp);
}

/**
 *sorts the words in the linked
 *in descending order.
 */
void list_sort(){


    if(total ==0 || total == 1){
    		return; //empty list and single element are already sorted
    }

    item * iptr; item * jptr; item * jnptr;
    iptr = head;
    int i = 0, j = 0;
    for(i = 1; i < total; i++){
        jptr = iptr; jnptr = jptr->next;

        for(j = 0; j < total-1; j++){
            if(jptr->bCount < jnptr->bCount){
                swap_ptr(jptr, jnptr);
            }
            jptr = jnptr;
            jnptr = jptr->next;
        }
    }
}

/**
 * converts all the words in an array
 * to be lowercase.
 */
void convert_string_lowercase(char* arr){

    int n = strlen(arr);
    int i = 0, j = 0;
    for(; i < n; i++){
        if((arr[i] > 64) && (arr[i] < 91)){
        		arr[i] = (int)arr[i] + 32;
        }
    }
}

/**
 *checks whether the current words
 *checks in the array are valid characters
 *checks and set them to null if they are not.
 */
void check_word_validity(char* arr){

    int n = strlen(arr);
    int i = 0, j = 0;

    if(!((arr[0] > 96 && arr[0] < 123))){
        for (i = 1; i < n; i++){
            arr[i-1] = arr[i];
        }
        arr[n-1] = 0;
    }

    i = 0;
    for(; i < n; i++){
        if(arr[i] < 97){
            if((arr[i] != 39) && (arr[i] != 45)){
                arr[i] = 0;
                return;
            }
        }else if (arr[i] > 122){
            arr[i] = 0;
            return;
        }
    }
}
