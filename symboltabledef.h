#include<stdio.h>

typedef struct variable* variable;
struct recordfields;
typedef struct recordfields* recordfields;
typedef struct symbolTable** symbolTable;
typedef struct record** recordTable;
typedef struct record* record;


struct variable{
	int type;
	char* lexeme;
	int width;
	int offset;
	char* scope;
	variable next; 
	int lineno;
}; 



struct recordfields{
	int type;
	char* lexeme;
	int width;
	recordfields next; 
}; 

struct record{
	char* rname;
	int width;
	recordfields head; 
	int lineno;
};


struct symbolTable{
	char* scope;
	variable inputpars;
	variable outputpars;
	variable localvars;
	struct symbolTable* next;
};