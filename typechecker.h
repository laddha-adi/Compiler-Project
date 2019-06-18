/*
GROUP NUMBER: 11
NIKKI GUPTA 2016A7PS0057P
SAHIL RANADIVE 2016A7PS0097P
ADITI AGARWAL 2016A7PS0095P
ADITYA LADDHA 2016A7PS0038P
*/


#include "symboltable.h"


void typechecker(treenode root, symbolTable stable,variable globalVarList, recordVar recList);

int checkassignstmt(treenode stmt,char* scope,symbolTable stable,variable globalVarList, recordVar recList);

void checkiterstmt(treenode stmt,char* scope,symbolTable stable,variable globalVarList, recordVar recList);

void checkcondstmt(treenode stmt,char* scope,symbolTable stable,variable globalVarList, recordVar recList);


// variable searchInlist(variable varlist, char* var_name);
recordVar searchInRecList(recordVar list, char* lex);


int typeOfSingleRec(treenode node,char* scope,symbolTable stable,variable globalVarList, recordVar recList);


int typeOfArithmetic(treenode node,char* scope,symbolTable stable,variable globalVarList, recordVar recList);


int checkBoolExp(treenode node ,char* scope,symbolTable stable,variable globalVarList, recordVar recList);
