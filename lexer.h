#include <stdio.h>
#include <stdlib.h>
#include "memlog.h"

#include "lexerDef.h"
#ifndef LEXERH_INCLUDED
#define LEXERH_INCLUDED

FILE *getStream(FILE* fp,char* buffer,int bsize);


tokenInfo getNextToken(FILE *fp, char* buffer,int bsize);


void createLexerHashTable();
long long hashFunc(char* string);
int lookup(char* lexeme);

void removeComments(FILE* testfile,FILE* cleanfile);

#endif
