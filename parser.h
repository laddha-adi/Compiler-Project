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
int getRowIndex(char* s);
int getColumnIndex(char* s);
node getFirstAlpha(node rule, hashtable ht);
parseTable createParseTable(hashtable ht,node* grules);
int hashFun(char* string );
void mergeLists(node list1,node list2);
int epsinFirst(node nonterminal,hashtable ht);


#endif