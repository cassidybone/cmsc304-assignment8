#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "Common.h"

void printToken(Token aToken);
TokenType identify(char* lexeme);
void toToken(File* aFile);
int main(int argc, char *argv[]);


#endif