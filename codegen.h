/*
GROUP NUMBER: 11
NIKKI GUPTA 2016A7PS0057P
SAHIL RANADIVE 2016A7PS0097P
ADITI AGARWAL 2016A7PS0095P
ADITYA LADDHA 2016A7PS0038P
*/




#ifndef CODEGEN_INCLUDED
#define CODEGEN_INCLUDED

#include "symboltable.h"
#include "parser.h"
#include "lexer.h"
#include "ast.h"
#include "semanticanalyzer.h"
#include "typechecker.h"

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>

variable findIfDeclared(symbolTable stable,char* scope, char* lexeme,variable globalVarList);
void readem(char* what, FILE* f);
void writem(char* what, FILE* f);
variable findIfDeclared(symbolTable stable,char* scope, char* lexeme,variable globalVarList);
void handleIOstmt(treenode ionode, FILE* f, symbolTable stable, variable globalVarList,recordVar recList);
void handleDeclarations(treenode decnode, FILE* f, symbolTable stable, variable globalVarList,recordVar recList);
void move(char* one, char* two, FILE* f);
int handleArithmetic(treenode arithexp, FILE* f, symbolTable stable, variable globalVarList,recordVar recList);
void handleAssignmentStmt(treenode assstmt, FILE* f, symbolTable stable, variable globalVarList,recordVar recList);
void handleBoolean(treenode boolexp, FILE* f, int reverse);
void handleIterativeStmt(treenode iterstmt, FILE* f, symbolTable stable, variable globalVarList,recordVar recList);
void handleConditionalStmt(treenode condstmt, FILE* f, symbolTable stable, variable globalVarList,recordVar recList);
void handleStmt(treenode stmt, FILE* f, symbolTable stable, variable globalVarList,recordVar recList);
void CodeGeneration(treenode ast,symbolTable stable,variable globalVarList,recordVar recList, char* fname);
void clearvars();

#endif
