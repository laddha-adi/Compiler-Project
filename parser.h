#ifndef PARSER
#define PARSER

#include "parserDef.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void printrule(node ls);
node* readGrammar(char* filename,hashtable ht);
int hashcode(char* string);
hashtable createHashTable();
void insertToHash(helement e,hashtable ht);
helement searchInTable(hashtable ht,char* string);
helement createHashElement(char* string);
void printRuleNo(helement h);

stack createStack();
void push(stack s, int rule_no);
int getTop(stack s);
int pop(stack s);
int isEmpty(stack s);

treenode createTreeNode(char *lexeme, int id);
/*nonLeafNode* createNonLeafNode();
leafNode* createLeafNOde();
*/
void sync(int X, int ip);
void error(int X, int ip);
int isTerminal(int X);
treenode* parser();
treenode  addChildrenRule(treenode parent, node gListHead);
int getId(char* str);

#endif