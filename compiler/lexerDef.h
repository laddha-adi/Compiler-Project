
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

#endif 