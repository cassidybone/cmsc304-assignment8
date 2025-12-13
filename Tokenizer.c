
#include "Tokenizer.h"


// to identify and return token type from lexeme
TokenType identify(char* lexeme){
    
    rstrip(lexeme);

    // Check if reserved words
    if (strcmp(lexeme, "while") == 0)  return WHILE_KEYWORD;
    if (strcmp(lexeme, "return") == 0) return RETURN_KEYWORD;
    if (strcmp(lexeme, "int") == 0 || strcmp(lexeme, "void") == 0) return VARTYPE;

    // Check if Symbol
    if (strcmp(lexeme, "(") == 0) return LEFT_PARENTHESIS;
    if (strcmp(lexeme, ")") == 0) return RIGHT_PARENTHESIS;
    if (strcmp(lexeme, "{") == 0) return LEFT_BRACKET;
    if (strcmp(lexeme, "}") == 0) return RIGHT_BRACKET;
    if (strcmp(lexeme, "=") == 0) return EQUAL;
    if (strcmp(lexeme, ",") == 0) return COMMA;
    if (strcmp(lexeme, ";") == 0) return EOL;
    if (strcmp(lexeme, "+") == 0 || strcmp(lexeme, "*") == 0 ||
        strcmp(lexeme, "==") == 0 || strcmp(lexeme, "!=") == 0 ||
        strcmp(lexeme, "%") == 0) return BINOP;

    // Check if number
    if (isdigit((unsigned char)lexeme[0]))  return NUMBER;

    // Otherwise IDENTIFIER 
    return IDENTIFIER;


}

// to split lines into lexemes
Lex* toToken(char* line, int* count){
    

    int i = 0;
    Lex* slot = malloc(sizeof(Lex)*5); // to store new Lex structs
    while (line[i] != '\0') { // check each character at a time until null terminator
        char temp[MAX_LINE_SIZE];
        temp[i] = line[i];
        if (isalpha((unsigned char)line[i])) {
            while(((isalpha((unsigned char)line[i+1])) || (isdigit((unsigned char)line[i+1])))){ //while a character or letter string collect
            i++;
            temp[i]= line[i];
            }
        }
        else if (isdigit((unsigned char)line[i])) {
            while(((isdigit((unsigned char)line[i+1])))){ //while string of digits collect
            i++;
            temp[i]= line[i];
            }
        }
        else if (isspace((unsigned char)line[i])) { // if space loop
            i++;
            continue;
        }
        else {
            while(!((isspace((unsigned char)line[i])) || (isalpha((unsigned char)line[i+1])) || (isdigit((unsigned char)line[i+1])))){
                i++;
                temp[i]= line[i];
            }
        }

        // Build new struct with founf lexeme
        Lex newLex;
        strcpy(newLex.lexeme, temp);
        newLex.type = identify(temp);      // run to identify TokenType
        slot[*count] = newLex;             // add to array
        (*count)++;                        // increment number of tokens found
        if((*count)%5 == 0){               // increase array size if needed
            slot = realloc(slot, sizeof(Lex)*(*count)+5);
        }


    }

    return slot;

}


int main(int argc, char *argv[]){

    if(argc != 3){                      //make sure correct number of arguments
        exit(0);
    }

    FILE* in = fopen(argv[1], "r");     //open input file to read
    FILE* out = fopen(argv[2], "w");    //open output file to write


    char line[MAX_LINE_SIZE];
    int count = 0; //count number of tokens

    Lex* kenized;

    //read each line and process into tokens
    while (fgets(line, sizeof(line), in) != NULL) {
        kenized = toToken(line, &count);
    }

    // print out to file
    for (int i = 0; i< count; i++){
        fprintf(out, "%s\n", kenized[i].type + " "+ kenized[i].lexeme);
        i++;
    }

    //cloe files
    fclose(in);
    fclose(out);

    return 0;


}
