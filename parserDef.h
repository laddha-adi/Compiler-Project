#ifndef HASH
#define HASH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "First.h"
// #include "Follow.h"
#include "lexer.h"

typedef struct Node* node;
typedef struct Helement* helement;
typedef helement* hashtable;
// typedef struct LinkedList* ll;

struct Node
{
	char* string;
	int flag;
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
	
	char* lexeme;
	int id;
};

/*typedef struct LeafNode* leafNode; 
struct LeafNode{
	int nt_id;
	treenode children;
};

typedef struct NonLeafNode* nonLeafNode; 
struct NonLeafNode{
	int nt_id;
	treenode children;
	int T_NT;
};
*/

typedef int** table;

#endif
