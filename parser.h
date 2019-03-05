/*
GROUP NUMBER: 11
NIKKI GUPTA 2016A7PS0057P
SAHIL RANADIVE 2016A7PS0097P
ADITI AGARWAL 2016A7PS0095P
ADITYA LADDHA 2016A7PS0038P
*/

#ifndef PARSER
#define PARSER

#include "parserDef.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hashcode(char* string);
hashtable createHashTable();
void insertToHash(helement e,hashtable ht);
helement searchInTable(hashtable ht,char* string);
helement createHashElement(char* string);
node* readGrammar(char* filename,hashtable ht);
void getFirst(hashtable ht,char* firstfile);
void getFollow(hashtable ht,char* followfile);
void printrule(node ls);
void printRuleNo(helement h);
int hashFun(char* string );
char* getCorrespondingString(int f);
int getRowIndex(char* s);
int getColumnIndex(char* s);
node getFirstAlpha(node rule, hashtable ht);
parseTable createParseTable(hashtable ht,node* grules);
void mergeLists(node list1,node list2);
int epsinFirst(node nonterminal,hashtable ht);
stack createStack();
void push(stack s, int rule_no, char* a);
int getTop(stack s);
int pop(stack s, char* a);
int isEmpty(stack s);
treenode createTreeNode(char *lexeme, int id, char* a);
int isFollow(int X, int ip,hashtable ht);
void printStack(stack s);
treenode parseInputSourceCode(FILE* fp, parseTable pTable, node* gRules, tokenInfo token, char*buffer, int bsize, hashtable ht,int* error);

treenode  addChildrenRule(treenode parent, node gListHead, int line, char* lexeme);
int getId(char* str);
void printInorderTraversal(treenode tree,char* outputFileName);
void inorder(treenode tree,FILE* fp);
void printParseTree(treenode pTree, FILE* fp);
#endif
