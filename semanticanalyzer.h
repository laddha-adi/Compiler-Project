/*
GROUP NUMBER: 11
NIKKI GUPTA 2016A7PS0057P
SAHIL RANADIVE 2016A7PS0097P
ADITI AGARWAL 2016A7PS0095P
ADITYA LADDHA 2016A7PS0038P
*/


#ifndef SYM_H_INCLUDED
#define SYM_H_INCLUDED

#include "parser.h"
#include "lexer.h"
#include "ast.h"
#include "symboltable.h"
#include "typechecker.h"

void checkonefuncall(treenode funcallstmt, char* scope, symbolTable stable, variable globalVarList);
int searchInFuncList(char** funlist, char* name, int num);
variable checkifdeclared(char* var_name, symbolTableElement stentry, variable globalVarList);
void checkfuncallstmts(treenode root, symbolTable stable, variable globalVarList,recordVar recList);
void checkIOstmt(treenode iostmt, char* scope, symbolTable stable,variable globalVarList,recordVar recList);
void checkSingleorRec(treenode node, char* scope, symbolTable stable,variable globalVarList,recordVar recList);


#endif
