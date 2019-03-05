


#ifndef HASH
#define HASH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

typedef struct Node* node;
typedef struct Helement* helement;
typedef helement* hashtable;
typedef int** parseTable;   //-2 entry denotes syn -1:error else ruleno
// typedef struct LinkedList* ll;

struct Node
{
	char* string;
	int flag;//terminal 1 nonterminal-1 eps 0
	node next;
};

struct Helement{

	node first;
	node follow;
	int* rules;
	int nrules;
	char* value;
	int flag;

};

typedef struct Stack* stack;

struct Stack{
	int *arr;
	int top;
};

typedef struct TreeNode* treenode; 

struct TreeNode{
	//struct nonLeafNode N;
	//struct leafNode L;
	treenode next;
	treenode children;
	treenode parent;
	treenode prev;
	int line;
	char* lexeme;
	
	int id;
};




#endif
