/*
 * Andrew Budihardja
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "list.h"

//file pointers
FILE *firstFile;
FILE *secondFile;
FILE *out;


int main() {

    firstFile = fopen("RedBadge.txt", "r");
    //inR = fopen("R.txt", "r");
    secondFile = fopen("LittleRegiment.txt", "r");
    //inL = fopen("L.txt", "r");
    char string_temp[256];
    item * curr;
    int i;
    head = NULL;
    total = 0;

    while(!feof(firstFile)){
        fscanf(firstFile, "%s", string_temp);

        convert_string_lowercase(&string_temp);
        check_word_validity(&string_temp);
        list_insertr(&string_temp);
    }
    while(!feof(secondFile)){
        fscanf(secondFile, "%s", string_temp);

        convert_string_lowercase(&string_temp);
        check_word_validity(&string_temp);
        list_insertl(&string_temp);
    }

    curr = head;
    for(i=0;i<total;i++) {
        //this part of code selects the smaller of the two counts of a word
        //to change it, simply change the if condition to (curr->lCount > curr->rCount)
        if(curr->lCount < curr->rCount) {
        		curr->bCount = curr->lCount;
        }else {
        		curr->bCount = curr->rCount;
        }
        curr = curr->next;
    }

    list_sort();
    curr = head;
    i = 0;
    while(curr){

        if(strlen(curr->word) ==0){
        		curr = curr->next;
        		i++;
        		continue;
        }
        //if(strlen(curr->word) ==1){printf("found a string: %s\t%d\n", curr->word, curr->word[0]);}
        //if(strlen(curr->word) ==2){printf("found a string: %s\t%d %d\n", curr->word, curr->word[0], curr->word[2]);}
        printf("%s\t%d\t%d\n", curr->word, curr->bCount, curr->rCount);
        curr = curr->next ;
        i++;

        if(i == 50){
        		break;
        }
    }
    return 0;
}
