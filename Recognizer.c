
#include "Recognizer.h"



// Class vars
static Lex  *tokens = NULL;
static int   count = 0;
static int   pos = 0;
static FILE *message = NULL;


TokenType unString(char *s) {
    if (strcmp(s, "LEFT_PARENTHESIS") == 0) return LEFT_PARENTHESIS;
    if (strcmp(s, "RIGHT_PARENTHESIS") == 0) return RIGHT_PARENTHESIS;
    if (strcmp(s, "LEFT_BRACKET") == 0) return LEFT_BRACKET;
    if (strcmp(s, "RIGHT_BRACKET") == 0) return RIGHT_BRACKET;
    if (strcmp(s, "WHILE_KEYWORD") == 0) return WHILE_KEYWORD;
    if (strcmp(s, "RETURN_KEYWORD") == 0) return RETURN_KEYWORD;
    if (strcmp(s, "EQUAL") == 0) return EQUAL;
    if (strcmp(s, "COMMA") == 0) return COMMA;
    if (strcmp(s, "EOL") == 0) return EOL;
    if (strcmp(s, "VARTYPE") == 0) return VARTYPE;
    if (strcmp(s, "IDENTIFIER") == 0)   return IDENTIFIER;
    if (strcmp(s, "BINOP") == 0) return BINOP;
    if (strcmp(s, "NUMBER") == 0) return NUMBER;
    //else;
    return IDENTIFIER;
}

// to get rid of extra space to left
void shorten(char *aString) {
    int len = (int)strlen(aString);
    while (len > 0 && isspace((unsigned char)aString[len - 1])) {
        aString[--len] = '\0';
    }
}

//function 	--> header body
int isFunction(void);

//header 		--> VARTYPE IDENTIFIER LEFT_PARENTHESIS [arg-decl] RIGHT_PARENTHESIS
int isHeader(void);


//arg-decl		--> VARTYPE IDENTIFIER {COMMA VARTYPE IDENTIFIER}
int isArgDecl(void);

//body 		--> LEFT_BRACKET [statement-list] RIGHT_BRACKET
int isBody(void);



//statement-list 	--> statement {statement}
int isStatementList(void);

//statement 	--> while-loop | return | assignment 
int isStatement(void);

//while-loop 	--> WHILE_KEYWORD LEFT_PARENTHESIS expression RIGHT_PARENTHESIS body
int isWhileLoop(void);

//return 		--> RETURN_KEYWORD expression EOL
int isReturn(void);

//assignment 	--> IDENTIFIER EQUAL expression EOL
int isAssignment(void);

//expression 	--> term {BINOP term} | LEFT_PARENTHESIS expression RIGHT_PARENTHESIS
int isExpression(void);

//term 		--> IDENTIFIER | NUMBER 
int isTerm(void){

    if(tokens[pos].type == IDENTIFIER || tokens[pos].type == NUMBER){
        pos++;
        return 1;
    }
    else{
        // message is error 
        return 0;
    }
}


// split token at space, identify and branch
int toLex(char* line){
    static int bucket = 5;  // how much room in the array

 
    char type[100]; //to store token type
    char lexeme[MAX_LINE_SIZE]; // to store lexeme

    int i = 0;
    int len = 0;

    shorten(line);

    // read type until space
    while (line[i] != '\0' && !isspace((unsigned char)line[i])) {
        type[len++] = line[i++];
    }
    type[len] = '\0';

    while (isspace((unsigned char)line[i])) {
        i++;
    }

    //rest is lexeme
    strncpy(lexeme, line + i, sizeof(lexeme) - 1);
    lexeme[sizeof(lexeme) - 1] = '\0';

    shorten(lexeme);

    // new Lex struct
    Lex newLex;
    newLex.type = unString(type);
    strncpy(newLex.lexeme, lexeme, MAX_LINE_SIZE - 1);
    newLex.lexeme[MAX_LINE_SIZE - 1] = '\0';

     // more room if needed
    if (count >= bucket) {
        tokens = realloc(tokens, sizeof(Lex)*(bucket*2));
        bucket = bucket*2;
    }

    // add to bucket
    (tokens)[count] = newLex;
    (count)++;

    return 1;
}

int branch(){

    //if first token not identifier error
    if(tokens[0].type != IDENTIFIER){ 

        //return error
        return 0;
    }
    else{
        if(isTerm() == 0){
            return 0;
        }
        return 1;

    }
    
}


int main(int argc, char *argv[]){

    if(argc != 3){                      //make sure correct number of arguments
        exit(0);
    }

    FILE* in = fopen(argv[1], "r");     //open input file to read
    FILE* out = fopen(argv[2], "w");    //open output file to write

    message = out;

    char line[MAX_LINE_SIZE];
    tokens = malloc(sizeof(Lex)*5); // to store new Lex structs

    int flag = 1;
    //read each line and process into tokens
    while (fgets(line, sizeof(line), in) != NULL) {
        
        toLex(line);
    }
   
    int i = 0;

    while(i<= count && flag ==  1){

        flag = branch();
        i++;

    }


    //close files
    fclose(in);
    fclose(out);

    return 0;

}