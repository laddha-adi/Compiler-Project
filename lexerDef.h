/*
GROUP NUMBER: 11
NIKKI GUPTA 2016A7PS0057P
SAHIL RANADIVE 2016A7PS0097P
ADITI AGARWAL 2016A7PS0095P
ADITYA LADDHA 2016A7PS0038P
*/

#ifndef LEXERDEF_INCLUDED
#define LEXERDEF_INCLUDED

#include <stdlib.h>

typedef struct{
	char* keyword;
	int tokenId;
} hashTableEntry;


typedef struct{
	int tokenId;
	char* value;
	int line;
}tokenInfo;



int state;
int offset;
int lexicalerror;
int lineNo;

#endif 