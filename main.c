#include "abclang.h"
#include <stdio.h>
#include <stdlib.h>

int main(int args, char **argv) {
    FILE *fp;

    if (args != 2) {
        fprintf(stderr, "usage:...\n");
        exit(1);
    }

    ABC_Interpreter *inter = create_interpreter();
    
}