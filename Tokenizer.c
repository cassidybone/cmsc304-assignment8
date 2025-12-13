#ifndef TOKENIZER_C
#define TOKENIZER_C

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "Common.h"

char* printToken(Token* aToken);

Token* toToken(FILE* inputFile);

int main(int argc, char *argv[]){

    if(argc != 3){                      //make sure correct number of arguments
        exit(0);
    }

    FILE* in = fopen(argv[1], "r");     //open input file to read
    FILE* out = fopen(argv[2], "w");    //open output file to write

    Token* kenized = toToken(in);
    int i = 0;

    while (kenized[i] != NULL){
        fprintf(out, "%s\n", printToken(kenized[i]));
        i++;
    }

    fclose(in);
    fclose(out);

    return 0;


}


#endif