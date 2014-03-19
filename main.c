#include "abclang.h"
#include <stdio.h>

int main(int args, char **argv) {
    FILE *fp;
    ABC_Interpreter *inter;

    if (args != 2) {
        fprintf(stderr, "usage:...\n");
        exit(1);
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "%s not found", argv[1]);
        exit(1);
    }
    inter = ABC_create_interpreter(); 
    fprintf(stderr, "create interpreter complete...\n");
    ABC_compile(inter, fp);
    fprintf(stderr, "compile complete...\n");
    ABC_execute(inter);
    fprintf(stderr, "execute complete\n");
    return 0;
}
