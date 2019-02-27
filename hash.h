#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node* node;
typedef struct LinkedList* ll;
typedef struct listOfList* dl;
typedef struct elementOfHash* element;
typedef struct listForHash* hashtable;
struct Node{
	char*  data;
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
	int flag;
	char* value;
	element next;
};
struct listForHash{
	element head;
};



int hashcode(char* string);
hashtable* createHashTable();
element createElement(char*string);
hashtable* insertToHash(char* string,hashtable* ht);
element searchInTable(hashtable* ht,char* string);
dl createListofList();
ll createLinkedList();
node createNode(char* a);
ll insertInList(ll ls,node n);
ll insertInOrder(ll ls ,node n);
dl insertInListOfList(dl d,ll ls);
dl insertInOrderList(dl d,ll ls);
void print(ll ls);
void print2(dl d);
