#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "omp.h"
#include <sys/stat.h>


#define MAX_SIZE 1000000
int thread_count = 0;
int int_count = 0;

int *generate_list(){

    int i = 0;
    int buffer[2];

    FILE *in_file = fopen("girdi.txt", "r");

    struct stat sb;
    stat("girdi.txt", &sb);

    char *file_contents = malloc(sb.st_size);
    int counter = 0;

    while (fscanf(in_file, "%[^\n] ", file_contents) != EOF && counter<2) {
        printf("> %s\n", file_contents);
        buffer[counter] = atoi(file_contents);
        counter++;
    }
    
    fclose(in_file);

    for(i=0; i<2 ; i++){
        printf("%d ", buffer[i]);
    }
    
    thread_count = buffer[0];
    int_count = buffer[1];
    
    int *sortPtr;
    sortPtr = (int*) malloc(buffer[1]* sizeof(int));
    
    if(sortPtr == NULL){  
        printf("\nMemory could not be allocated...\n");
        exit(0);
    }

    else{ //arrayi doldur
        printf("Memory allocated!\n");
        
        FILE *in_file = fopen("girdi.txt", "r");

        struct stat sb;
        stat("girdi.txt", &sb);

        char *file_contents = malloc(sb.st_size);
        int counter = 0;
        int ptrCounter = 0;

        while (fscanf(in_file, "%[^\n] ", file_contents) != EOF) {

            if(counter>1){
                printf("> %s\n", file_contents);
                sortPtr[ptrCounter] = atoi(file_contents);
                ptrCounter++;
            }
            counter++;
        }
        
        fclose(in_file);

    
    }
    
    return sortPtr;
}

int main(){

    int *arrayToSort;
    double start, stop;

    arrayToSort = generate_list();


    for (int i = 0; i < 10; ++i) {
        printf("%d ", arrayToSort[i]);
    }  

    printf("\nTotal thread count: %d", thread_count);
    printf("\nTotal integer count: %d", int_count);


    start = omp_get_wtime();
    #pragma omp parallel{

    }
    stop = omp_get_wtime();




    return 0;
}
