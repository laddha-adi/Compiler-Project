#include<stdio.h>

typedef struct variable* variable;
struct recordfields;
typedef struct recordfields* recordField;
typedef struct symbolTable** symbolTable;
typedef struct record** recordTable;
typedef struct record* recordVar;
typedef struct symbolTable* symbolTableElement;

struct variable{
	int type;
	char* lexeme;
	int width;
	int offset;
	char* scope;
	variable next; 
	int lineno;
	char* recordName;
}; 



struct recordfields{
	int type;
	char* lexeme;
	int width;
	recordField next; 
}; 

struct record{
	char* rname;
	int width;
	recordField head; 
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