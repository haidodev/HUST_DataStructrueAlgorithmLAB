#include<stdio.h>
int main(int argc, int *argv[]){
    printf("ARGC = %d\n", argc);
    for (int i = 0; i < argc; ++i){
        printf("%s\n", argv[i]);
    }
}