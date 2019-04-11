#ifndef SYMBOL_H_INCLUDED
#define SYMBOL_H_INCLUDED

#include "symboltabledef.h"
#include "parser.h"
#include "lexer.h"
#include "ast.h"

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
/*
// invoked by driver to create symbol table
hashtable *createSymbolTable(treenode PT, int size);

// prints symbol table in desired formats
void printSymbolTable(hashtable *ht, int size);

// helper function used by typechecker to fetch input parameters of a given function
entry *getInputParameter(hashtable *ht, char *function, int ParameterNumber);
// helper function used by typechecker to fetch output parameters of a given function
entry *getOutputParameter(hashtable *ht, char *function, int ParameterNumber);

// keeps track of symboltable errors like redeclarations
char symboltable_errors[500][500];*/
int error_count;

int symbolerror;

variable createVar(treenode declaration, char* scope);
variable addToGlobalList(variable list, treenode declaration, char* scope);
int searchInGlobalList(variable list, char* lex);
variable findAndInsertGVariables(variable globalVarList, treenode root, recordVar globalRecordDefList);
symbolTable create();
int hash(char *str);
symbolTable insert(char* scope, variable var, int typeList, symbolTable stable);
variable lookupSTable(variable var, char*scope, symbolTable stable, variable globalVarList);
variable insertAtEnd(variable list,variable var);
int searchInList(variable var, variable list);
recordVar createRecordVar(treenode typeDef);

recordField createRecordField(treenode fieldDef);
recordVar createRecordVar(treenode typeDef);
recordVar addToRecordList(recordVar list, treenode typeDefs);
int searchInRecordList(recordVar list, char* lex);
recordVar findAndInsertRecordDefs(recordVar globalRecordDefList, treenode root, recordVar head);
void findAndInsertGRecVariables(variable globalVarList, treenode root, recordVar rlist);

void printRecordDefList(recordVar head);
symbolTable addFunctions(treenode root, variable globalVarList, recordVar recordDefList);
variable addToVariableList(variable list, variable v);
void printVarList(variable head);
symbolTableElement createMainFunction(treenode function, symbolTable stable, variable globalVarList, recordVar recordDefList);
void printSymbolTable(symbolTable stable);
void addOffset(symbolTable stable, recordVar recordDefList);
void addListOffset(variable head, recordVar recordDefList);

#endif
