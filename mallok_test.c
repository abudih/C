/*
 * Andrew Budihardja
 */

#include <stdlib.h>
#include <stdio.h>
#include "mallok.h"

int main(){

    create_pool(1000);
    //print_my_heap();
    void* a1 = my_malloc(200);
    void* a2 = my_malloc(200);
    void* a3 = my_malloc(200);
    void* a4 = my_malloc(200);
    void* a5 = my_malloc(200);
    print_my_heap();
    a3 = my_malloc(210);
    if(a3 == NULL){
        printf("Couldnt get memory for: %d bytes\n", 210);
    }
    a3 = my_malloc(150);
    print_my_heap();
    a3 = my_malloc(60);
    if(a3 == NULL){
        printf("Couldnt get memory for: %d bytes\n", 60);
    }
    a3 = my_malloc(50);
    print_my_heap();
    return 0;

}
