#include "Tokenizer.h"


void shorten(char *aString);


// method to print token type
const char *toString(TokenType t) {
    switch (t) {
        case LEFT_PARENTHESIS:  return "LEFT_PARENTHESIS";
        case RIGHT_PARENTHESIS: return "RIGHT_PARENTHESIS";
        case LEFT_BRACKET:      return "LEFT_BRACKET";
        case RIGHT_BRACKET:     return "RIGHT_BRACKET";
        case WHILE_KEYWORD:     return "WHILE_KEYWORD";
        case RETURN_KEYWORD:    return "RETURN_KEYWORD";
        case EQUAL:             return "EQUAL";
        case COMMA:             return "COMMA";
        case EOL:               return "EOL";
        case VARTYPE:           return "VARTYPE";
        case IDENTIFIER:        return "IDENTIFIER";
        case BINOP:             return "BINOP";
        case NUMBER:            return "NUMBER";
        default:                return "UNKNOWN";
    }
}

// to identify and return token type from lexeme
TokenType identify(char* lexeme){
    
    shorten(lexeme);

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

// to get rid of extra space to left
void shorten(char *aString) {
    int len = (int)strlen(aString);
    while (len > 0 && isspace((unsigned char)aString[len - 1])) {
        aString[--len] = '\0';
    }
}

// to split lines into lexemes
Lex* toToken(Lex** slot, char* line, int* count){
    

    int i = 0; //index in line
    while (line[i] != '\0') { // check each character at a time until null terminator
        char temp[MAX_LINE_SIZE];
        int len = 0;
        temp[len++] = line[i];
        temp[len]= '\0';
        if (isalpha((unsigned char)line[i])) {
            i++;
            while(((isalpha((unsigned char)line[i])) || (isdigit((unsigned char)line[i])))){ //while a character or letter string collect
            temp[len++]= line[i++];
            temp[len]= '\0';
            }
        }
        else if (isdigit((unsigned char)line[i])) {
            i++;
            while(((isdigit((unsigned char)line[i])))){ //while string of digits collect
            temp[len++]= line[i++];
            temp[len]= '\0';
            }
        }
        else if (isspace((unsigned char)line[i])) { // if space loop
            i++;
            continue;
        }
        else {
            i++;
            while(!((isspace((unsigned char)line[i])) || (isalpha((unsigned char)line[i])) || (isdigit((unsigned char)line[i])))){

                temp[len++]= line[i];
                temp[len]= '\0';
                i++;
            }
        }

        // Build new struct with founf lexeme
        Lex newLex;
        strcpy(newLex.lexeme, temp);
        newLex.type = identify(temp);      // run to identify TokenType
        (*slot)[*count] = newLex;             // add to array
        (*count)++;                        // increment number of tokens found
        if((*count)%5 == 0){               // increase array size if needed
            *slot = realloc(*slot, sizeof(Lex)*((*count)+5));
        }


    }

    return *slot;

}


int main(int argc, char *argv[]){

    if(argc != 3){                      //make sure correct number of arguments
        exit(0);
    }

    FILE* in = fopen(argv[1], "r");     //open input file to read
    FILE* out = fopen(argv[2], "w");    //open output file to write


    char line[MAX_LINE_SIZE];
    int count = 0; //count number of tokens

    Lex* kenized = malloc(sizeof(Lex)*5); // to store new Lex structs

    //read each line and process into tokens
    while (fgets(line, sizeof(line), in) != NULL) {
        shorten(line);
        toToken(&kenized, line, &count);
    }

    // print out to file
    for (int i = 0; i< count; i++){
        fprintf(out, "%s %s\n", toString(kenized[i].type), kenized[i].lexeme);

    }

    
    free(kenized); //no garbage around here

    //cloe files
    fclose(in);
    fclose(out);

    return 0;


}

