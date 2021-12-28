#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "omp.h"
#include <sys/stat.h>


#define TASK_SIZE 1000000
int thread_count = 0;
int int_count = 0;

int *generateList(){

    int i = 0;
    int buffer[2];

    FILE *in_file = fopen("girdi.txt", "r");

    struct stat sb;
    stat("girdi.txt", &sb);

    char *file_contents = malloc(sb.st_size);
    int counter = 0;

    while (fscanf(in_file, "%[^\n] ", file_contents) != EOF && counter<2) {
        //printf("> %s\n", file_contents);
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
                //printf("> %s\n", file_contents);
                sortPtr[ptrCounter] = atoi(file_contents);
                ptrCounter++;
            }
            counter++;
        }
        
        fclose(in_file);

    
    }
    
    return sortPtr;
}

void mergeSortAux(int *X, int n, int *tmp) {
    int i = 0;
    int j = n/2;
    int ti = 0;

    while (i<n/2 && j<n) {
        if (X[i] < X[j]) {
            tmp[ti] = X[i];
            ti++; i++;
        } else {
            tmp[ti] = X[j];
            ti++; j++;
        }
    }
    while (i<n/2) { /* finish up lower half */
        tmp[ti] = X[i];
        ti++; i++;
    }
    while (j<n) { /* finish up upper half */
        tmp[ti] = X[j];
        ti++; j++;
    }
    memcpy(X, tmp, n*sizeof(int));
} 

void mergeSort(int *X, int n, int *tmp)
{
    if (n < 2) return;

    #pragma omp task shared(X) if (n > TASK_SIZE)
    mergeSort(X, n/2, tmp);

    #pragma omp task shared(X) if (n > TASK_SIZE)
    mergeSort(X+(n/2), n-(n/2), tmp + n/2);

    #pragma omp taskwait
    mergeSortAux(X, n, tmp);
}

int writeToFile(int *array){

    FILE *fptr;
    int i;

    fptr = fopen("cikti.txt", "w");

    fprintf(fptr, "%d\n", thread_count);
    fflush(fptr);
    fprintf(fptr, "%d\n", int_count);
    fflush(fptr);

    for(i=0; i<int_count; i++){
        fprintf(fptr, "%d\n", array[i]);
        fflush(fptr);
    }
    fclose(fptr);

}
int main(){

    int *arrayToSort;
    double start, stop;
    
    arrayToSort = generateList();

    for (int i = 0; i < 10; i++) {
        printf("%d ", arrayToSort[i]);
    }  

    printf("\nTotal thread count: %d", thread_count);
    printf("\nTotal integer count: %d", int_count);

    int *tmp = malloc(int_count * sizeof(int));

    omp_set_dynamic(0);
    omp_set_num_threads(thread_count);

    start = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        mergeSort(arrayToSort, int_count, tmp);
    }
    stop = omp_get_wtime();

    printf("\nTime: %f (s) n",stop-start);

    writeToFile(arrayToSort);

    return 0;
}
