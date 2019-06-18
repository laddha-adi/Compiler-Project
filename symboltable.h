/*
GROUP NUMBER: 11
NIKKI GUPTA 2016A7PS0057P
SAHIL RANADIVE 2016A7PS0097P
ADITI AGARWAL 2016A7PS0095P
ADITYA LADDHA 2016A7PS0038P
*/


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


variable insertAtEnd(variable list,variable var);
int searchInList(variable var, variable list);
recordVar findRecord(recordVar list, char* lex);
variable createVar(treenode declaration, char* scope);
variable createParVar(treenode type, treenode TK_ID, char* scope, recordVar list);
variable addToGlobalList(variable list, treenode declaration, char* scope );
variable addToVariableList(variable list, variable v);
int searchInGlobalList(variable list, char* lex);
variable findAndInsertGVariables( treenode root, recordVar globalRecordDefList);
void findAndInsertGRecVariables(variable globalVarList, treenode root, recordVar rlist);
recordField createRecordField(treenode fieldDef);
recordVar createRecordVar(treenode typeDef);
recordVar addToRecordList(recordVar list, treenode typeDefs);
int searchInRecordList(recordVar list, char* lex);
recordVar findAndInsertRecordDefs(treenode root);
symbolTableElement createFunction(treenode function, symbolTable stable, variable globalVarList, recordVar recordDefList);
symbolTableElement createMainFunction(treenode function, symbolTable stable, variable globalVarList, recordVar recordDefList);
symbolTable addInSTable(symbolTable stable, symbolTableElement sElement);
symbolTable addFunctions(treenode root, variable globalVarList, recordVar recordDefList);
void printVarList(variable head, recordVar list);
void printGlobalVarList(variable head);
void printRecordDefList(recordVar head);
void printSymbolElement(symbolTableElement sElement, recordVar list);
void printSymbolTable(symbolTable stable, recordVar list);
void addListOffset(variable head, recordVar recordDefList);
void addOffset(symbolTable stable, recordVar recordDefList);
void cleanVars();
variable searchInListStr(variable list, char* lexeme);
symbolTableElement findInSTable(symbolTable stable, char* fname);
void printFunctionOffset(symbolTable stable);
void printRecordDef(recordVar head);
#endif
