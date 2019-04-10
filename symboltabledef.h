#include<stdio.h>

typedef struct variable* variable;
struct recordfields;
typedef struct recordfields* recordfield;
typedef struct symbolTable** symbolTable;
typedef struct record** recordTable;
typedef struct record* recordVar;


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
	recordfield next; 
}; 

struct record{
	char* rname;
	int width;
	recordfield head; 
	int lineno;
	recordVar next;
};


struct symbolTable{
	char* scope;
	variable inputpars;
	variable outputpars;
	variable localvars;
	struct symbolTable* next;
};