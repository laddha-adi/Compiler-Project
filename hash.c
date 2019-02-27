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
	//printf("Here6");
	int i;
	for(i = 0; i < 501; i++){
		ht[i]=(hashtable)malloc(sizeof(struct listForHash));
		ht[i]->head=NULL;
	}
	if(ht==NULL) printf("LOL Sahil!!");
	//	printf("Here5");
	return ht;
}

element createElement(char*string){
	element e = (element)malloc(sizeof(struct elementOfHash));
	e->grammar = createListofList();
	e->first = createLinkedList();
	e->follow = createLinkedList();
	char* str = (char*) malloc(sizeof(char)*20);
	strcpy(str,string);
	e->value = str;
	return e;
}

hashtable* insertToHash(char* string,hashtable* ht){
	element e = createElement(string);
	//printf(e->value);
	int hash = hashcode(string);
	//printf("%d",hash);
	element temp = ht[hash]->head;
	ht[hash]->head = e;
	e->next = temp;
	return ht;
}

element searchInTable(hashtable* ht,char* string){
	int hash = hashcode(string);
	element temp = createElement("");
	temp = ht[hash]->head;
	while(temp!=NULL){
		//printf("%s \t %s \n", temp->value, string);
		if(strcmp(temp->value, string)==0)
			return temp;
		temp = temp->next;
	}
	printf("element not found");
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

node createNode(char* a){
	node n = (node)malloc(sizeof(struct Node));
	char* str = (char*) malloc(sizeof(char)*20);
	strcpy(str,a);
	n->data = str;
	//printf("%s\n",n->data);
	return n;
}
ll insertInOrder(ll ls ,node n){
	node temp = ls->head;
	if(temp==NULL){
		ls->head = n;
		return ls;
	}
	while(temp->next!=NULL)
		temp = temp->next;
	temp->next = n;
	return ls;
}
ll insertInList(ll ls,node n){
	node temp = ls->head;
	ls->head = n;
	n->next = temp;
	return ls; 
}
void print2(dl d){
	ll temp = createLinkedList();
	temp = d->head;
	while(temp!=NULL){
		print(temp);
		//printf("\n");
		temp = temp->next1;
		printf("\n");
	}
}
dl insertInOrderList(dl d,ll ls){
	ll temp = d->head;
	if(temp==NULL){
		d->head = ls;
		return d;
	}
	while(temp->next1!=NULL)
		temp = temp->next1;
	temp->next1 = ls;
	return d;
}
dl insertInListOfList(dl d,ll ls){
	ll temp = createLinkedList();
	temp = d->head;
	d->head = ls;
	ls->next1 = temp;
	//print2(d);
	return d;
}

void print(ll ls){
	node temp = ls->head;
	while(temp!=NULL){
		printf("%s\t",temp->data);
		temp = temp->next;
	}
}
/*void print2(dl d){
	ll temp = d->head;
	while(temp!=NULL){
		print(temp);
		printf("\n");
		temp = temp->next1;
	}
}
*/