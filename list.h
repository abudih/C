/*
 *Andrew Budihardja
 */
#ifndef LIST_HEADERFILE_H
#define LIST_HEADERFILE_H

struct words_list {

   char word[256];
   int rCount;
   int lCount;
   int bCount; //will be used and populated in sorting
   struct words_list * next;
};

typedef struct words_list item;
item * head;
int total;
int check_word_redBadge(char* wrr);
int check_word_littleRegiment(char* wrr);
void list_insertr(char* arr);
void list_insertl(char* arr);
void swap_ptr();
void list_sort();
void convert_string_lowercase(char* arr);
void check_word_validity(char* arr);

#endif
