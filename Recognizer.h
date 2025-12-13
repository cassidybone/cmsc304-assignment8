#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "Common.h"

int isTerm(void);
int isExpression(void);


int isAssignment(void);
int isReturn(void);
int isWhileLoop(void);
int isStatement(void);
int isStatementList(void);


int isBody(void);
int isArgDecl(void);
int isHeader(void);


int isFunction(void);

#endif