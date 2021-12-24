#include <stdio.h>

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