/*
GROUP NUMBER: 11
NIKKI GUPTA 2016A7PS0057P
SAHIL RANADIVE 2016A7PS0097P
ADITI AGARWAL 2016A7PS0095P
ADITYA LADDHA 2016A7PS0038P
*/


#include <stdio.h>
#include <stdlib.h>

#include "lexerDef.h"
#ifndef LEXERH_INCLUDED
#define LEXERH_INCLUDED

FILE *getStream(FILE* fp,char* buffer,int bsize);

tokenInfo getNextToken(FILE *fp, char* buffer,int bsize);

void createLexerHashTable();
long long hashFunc(char* string);
int lookup(char* lexeme);

void removeComments(FILE* testfile);
int getLexerErrors();
void resetLexError();
#endif