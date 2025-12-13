#ifndef TOKENIZER_C
#define TOKENIZER_C

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "Common.h"

char* printToken(Token* aToken);


Lex* toToken(Char* line, int* count){
    
    int i = 0;
    Lex[] slot = malloc(sizeof(Lex)*5);
    while (line[i] != '\0') { // check each character at a time until null terminator
        char temp[MAX_LINE_SIZE] = line[i];
        if (isalpha((unsigned char)line[i])) {
            while(((isalpha((unsigned char)line[i+1])) || (isdigit((unsigned char)line[i+1])))){ //while a character or letter string collect
            i++;
            temp[i]= line[i];
            }
        }
        else if (isdigit((unsigned char)c)) {
            // start or continue NUMBER
        }
        else if (isspace((unsigned char)c)) {
            // delimiter
        }
        else {
            // symbol
        }

        slot[count] = struct Lex
        *count++; //increment number of tokens found


    }
}


int main(int argc, char *argv[]){

    if(argc != 3){                      //make sure correct number of arguments
        exit(0);
    }

    FILE* in = fopen(argv[1], "r");     //open input file to read
    FILE* out = fopen(argv[2], "w");    //open output file to write


    char line[MAX_LINE_SIZE];
    int count = 0; //count number of tokens

    //read each line and process into tokens
    while (fgets(line, sizeof(line), in) != NULL) {
        toToken(line, &count);
    }


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