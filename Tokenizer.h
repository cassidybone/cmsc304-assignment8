#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "Common.h"

const char *toString(TokenType t);
TokenType identify(char* lexeme);
void shorten(char *aString);

Lex* toToken(Lex** slot, char* line, int* count);

#endif
