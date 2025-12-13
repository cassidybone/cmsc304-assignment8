#ifndef COMMON_H
#define COMMON_H

#define MAX_LINE_SIZE 256

typedef enum{
    LEFT_PARENTHESIS, 		//--> (
    RIGHT_PARENTHESIS,   	//--> )
    LEFT_BRACKET, 		    //--> {
    RIGHT_BRACKET, 		    //--> }
    WHILE_KEYWORD, 		    //--> while
    RETURN_KEYWORD,      	//--> return
    EQUAL, 		 	        //--> =
    COMMA,			        //--> ,
    EOL, 				    //--> ;
    VARTYPE, 			    //--> int | void
    IDENTIFIER, 			    //--> [a-zA-Z][a-zA-Z0-9]*
    BINOP, 				    //--> + | * | != | == | %
    NUMBER, 			        //--> [0-9][0-9]*

}TokenType;

typedef struct{

    TokenType type;
    char lexeme[MAX_LINE_SIZE]

}Lex;


#endif