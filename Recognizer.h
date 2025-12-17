
#ifndef RECOGNIZER_H
#define RECOGNIZER_H

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
int branch();
TokenType unString(char *s);
void shorten(char *aString);
int toLex(char *line);

#endif