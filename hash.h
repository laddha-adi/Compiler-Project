#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node* node;
typedef struct LinkedList* ll;
typedef struct listOfList* dl;
typedef struct elementOfHash* element;
typedef struct listForHash* hashtable;
struct Node{
	int  data;
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
