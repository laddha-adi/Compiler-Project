#ifndef HASH
#define HASH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "First.h"
// #include "Follow.h"
#include "lexer.h"


typedef struct Node* node;
typedef struct LinkedList* ll;
typedef struct listOfList* dl;
typedef struct elementOfHash* element;
typedef  element* hashtable;
typedef dl grammarRules;
typedef ll singleRule;



struct Node{
	//char*  data;
	element ele;
	node next;
};

struct LinkedList{
	node head;
	ll next1;
};

struct listOfList{
	ll head;
};

struct elementOfHash{
	dl grammar;
	ll first;
	ll follow;
	int flag; // -1 : Non Terminal, 0: eps, 1: Terminal 
	char* value;
	element next;
};

// struct listForHash{
// 	element head;
// };

dl readFile(char * fileName, hashtable ht);
grammarRules insertRule(grammarRules gRules, singleRule sRule);
void insertAllRulesInHash(grammarRules gr,hashtable ht);
void addGrammarRule(element e, ll l);
int hashcode(char* string);
hashtable createHashTable();
element createElement(char*string);
hashtable insertToHash(element e,hashtable ht);
element searchInTable(hashtable ht,char* string);
dl createListofList();
ll createLinkedList();
node createNode(element a);
ll insertInList(ll ls,node n);
ll insertInOrder(ll ls ,node n);
dl insertInListOfList(dl d,ll ls);
dl insertInOrderList(dl d,ll ls);
void print(ll ls);
void print2(dl d);
void printNtList(ll ls);
void printTList(ll ls);
void printNT(dl d);
void printT(dl d);
ll copyList(node n);
ll concatList(ll l1, ll l2);
void printFollowSet(dl d);
int containsEPS(ll l);
void printFirstSet(dl d);

#endif