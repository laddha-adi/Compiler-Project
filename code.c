#include "code.h"

element* createHashTable(){
	element* ht = (element*)malloc(sizeof(element)*100);
	return ht;
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
int main(){
	ll ls = createLinkedList();
	ll ls2 = createLinkedList();

	node n1 = createNode(12);
	node n2 = createNode(28);
	node n3 = createNode(15);
	ls = insertInList(ls,n1);
	ls = insertInList(ls,n2);
	ls2 = insertInList(ls2,n3);
	//ls2 = insertInList(ls2,n2);
	dl d = createListofList();
	d = insertInListOfList(d,ls);
	//print(d->head);
	//ls = insertInList(ls,n3);
	//printf("\n");
	d = insertInListOfList(d,ls2);
	print2(d);
	//if(d->head->next1->next1==NULL)
		//printf("1\n");
	//print2(d);
	//printf("%d\n",ls->head->data);
}