#include "hash.h"

int hashcode(char* string){
	int hash = 3;
	for(int i = 0; i < strlen(string); i++){
		hash = (hash*29 + string[i])%500;
	}
	return hash;
}

hashtable* createHashTable(){
	hashtable* ht = (hashtable*)malloc(sizeof(hashtable)*501);
	for(int i = 0; i < 501; i++){
		ht[i]->head=NULL;
	}
	return ht;
}

element createElement(char*string){
	element e = (element)malloc(sizeof(struct elementOfHash));
	e->grammar = NULL;
	e->first = NULL;
	e->follow = NULL;
	e->value = string;
	return e;
}

void insertToHash(char* string,hashtable* ht){
	element e = createElement(string);
	int hash = hashcode(string);
	element temp = ht[hash]->head;
	ht[hash]->head = e;
	e->next = temp;
	return;
}

element searchInTable(hashtable* ht,char* string){
	int hash = hashcode(string);
	element temp = ht[hash]->head;
	while(temp!=NULL){
		if(temp->value == string)
			return temp;
		temp = temp->next;
	}
	return NULL;
}

dl createListofList(){
	dl list = (dl)malloc(sizeof(struct listOfList));
	list->head = NULL;
	return list;
}

ll createLinkedList(){
	ll ls = (ll)malloc(sizeof(struct LinkedList));
	ls->head = NULL;
	return ls;
}
node createNode(int a){
	node n = (node)malloc(sizeof(struct Node));
	n->data = a;
	return n;
}
ll insertInList(ll ls,node n){
	node temp = ls->head;
	ls->head = n;
	n->next = temp;
	return ls; 
}
dl insertInListOfList(dl d,ll ls){
	ll temp = d->head;
	d->head = ls;
	ls->next1 = temp;
	return d;
}

void print(ll ls){
	node temp = ls->head;
	while(temp!=NULL){
		printf("%d\t",temp->data);
		temp = temp->next;
	}
}
void print2(dl d){
	ll temp = d->head;
	while(temp!=NULL){
		print(temp);
		temp = temp->next1;
	}
}
