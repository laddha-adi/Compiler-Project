#include<stdio.h>

typedef struct variable* variable;
struct recordfields;
typedef struct recordfields* recordfields;

struct variable{
	char* type;
	char* lexeme;
	int width;
	int offset;
	char* scope;
	variable next; 
	recordfields rfields;
	int lineno;
}; 

struct recordfields{
	char* type;
	char* lexeme;
	int width;
	int offset;
	char* scope;
	recordfields* next; 
	int lineno;
};

struct symbolTable** symbolTable;

struct symbolTable{
	char* scope;
	variable inputpars;
	variable outputpars;
	variable localvars;
	struct symbolTable* next;
};