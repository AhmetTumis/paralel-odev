#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "omp.h"

#define MAX_SIZE 1000000

void generate_array(){

}

int main(){

    FILE *fp;
    char buff[255];
    int num;

    fp = fopen("girdi.txt", "r");

    if(fp == NULL){
        printf("error!");
        exit(1);
    }

    
    printf("anan");

    return 0;
}