#include "hash.h"
#include "memlog.h"

int hash_size = 1000;
int hashcode(char* string){
	int hash = 3;
	for(int i = 0; i < strlen(string); i++){
		hash = (hash*37 + string[i])%hash_size;
	}
	return hash;
}

hashtable createHashTable(){
	hashtable ht = (hashtable)malloc(sizeof(element)*(hash_size+1));
	addMem(sizeof(element)*(hash_size+1), "Creatinn HashTable");
	if(ht==NULL) printf("Memory Error!\n");	
	return ht;
}

element createElement(char* string){
	element e = (element)malloc(sizeof(struct elementOfHash));
	addMem(sizeof(struct elementOfHash), "createElement");
	e->grammar = createListofList();
	e->first = createLinkedList();
	e->follow = createLinkedList();
	e->value = (char*) malloc(sizeof(char)*50);
	char* str = (char*) malloc(sizeof(char)*50);
	strcpy(str,string);
	e->value = str;
	if(strcmp("eps", str)==0){
		e->flag = 0;
	}else{
		e->flag = 1;   //-1 : Non Terminal, 0: eps, 1: Terminal
	}
	return e;
}

hashtable insertToHash(element e,hashtable ht){

	element e_1 = searchInTable(ht, e->value);
	if(e_1 != NULL) {
		printf("***************Collision*************** %s %s\n",e->value, e_1 -> value);
	}
	int hash = hashcode(e->value);
	ht[hash] = e;
	return ht;
}

element searchInTable(hashtable ht,char* string){
	int hash = hashcode(string);
	if(ht[hash]==NULL)
		return NULL;
	else 
		return ht[hash];
}

dl createListofList(){
	dl list = (dl)malloc(sizeof(struct listOfList));
	addMem(sizeof(struct listOfList), "Create List of List");
	list->head = NULL;
	return list;
}

ll createLinkedList(){
	ll ls = (ll)malloc(sizeof(struct LinkedList));
	addMem(sizeof(struct LinkedList), "Create List");
	ls->head = NULL;
	return ls;
}

node createNode(element e){
	node n = (node)malloc(sizeof(struct Node));
	addMem(sizeof(struct Node), "Create Node");
	n->ele = e;
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
	n->next = NULL;
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
		temp = temp->next1;
		printf("\n");
	}
}

dl insertInOrderList(dl d,ll ls){
	ll temp = d->head;
	if(temp==NULL){
		d->head = createLinkedList();
		d->head = ls;
		return d;
	}
	while(temp->next1!=NULL)
		temp = temp->next1;
		temp->next1 = createLinkedList();
		temp->next1 = ls;
		ls->next1 = NULL;
	return d;
}

dl insertInListOfList(dl d,ll ls){
	ll temp = createLinkedList();
	temp = d->head;
	d->head = ls;
	ls->next1 = temp;
	return d;
}

void print(ll ls){
	node temp = ls->head;
	while(temp!=NULL){
		printf("%s(%d)\t",temp->ele->value, temp->ele->flag);
		temp = temp->next;
	}
}

void printNtList(ll ls){
	node temp = ls->head;
	while(temp!=NULL){
		//if(temp->flag == -1) printf("%s\n",temp->data);
		//temp = temp->next;
	}
}

void printTList(ll ls){
	node temp = ls->head;
	while(temp!=NULL){
		//if(temp->flag == 1) printf("%s\n",temp->data);
		//temp = temp->next;
	}
}


void printFollowSet(dl d){
	ll temp = createLinkedList();
	temp = d->head;
	while(temp!=NULL){
		printf("Follow [ %s ] = ",temp->head->ele->value);
		print(temp->head->ele->follow);
		printf("\n");
		temp = temp->next1;
	}
}
void printFirstSet(dl d){
	ll temp = createLinkedList();
	temp = d->head;
	while(temp!=NULL){
		printf("First [ %s ] = ",temp->head->ele->value);
		print(temp->head->ele->first);
		printf("\n");
		temp = temp->next1;
	}
}

void printT(dl d){
	ll temp = createLinkedList();
	temp = d->head;
	while(temp!=NULL){
		printTList(temp);
		temp = temp->next1;
	}
}

ll copyList(node n){
	ll l = createLinkedList();
	while(n!=NULL){
		node t = createNode(n->ele);
		l = insertInOrder(l, t);
		n = n->next;
	}
	return l;
}

int find(node n, ll l){
	node temp = l->head;
	while(temp!=NULL){
		if(strcmp(temp->ele->value, n->ele->value)==0) return 1;
		temp = temp->next;
	}
	return 0;
} 

ll concatList(ll l1, ll l2){
	node templ1 = l1->head;
	node templ2 = l2->head;
	if(templ1==NULL) return l2;
	if(templ2 == NULL) return l1;

	while(templ2!=NULL){
		if(find(templ2, l1)==0){
			l1 = insertInList(l1, createNode(templ2->ele));
		}
		templ2 = templ2->next;
	}	
	return l1;
}

int containsEPS(ll l){
	node temp = l->head;
	while(temp!=NULL){
		//printf("%s\t",temp->ele->value);
		if(temp->ele->flag == 0) return 1;
		temp = temp->next;
	}
	return 0;
}
