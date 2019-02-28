#include "First.h"

void addFirst(grammarRules gr, hashtable* ht){
	
	ll temp = gr->head;
	while(temp!=NULL){
		if(temp->head->ele->first->head==NULL){
			printf("First of %s DNE \n", temp->head->ele->value);
			temp->head->ele->first = getFirst(temp->head->ele, ht);
		}else{
			printf("First exists\n");
		}
		temp = temp->next1;	
	}
	return;
}



ll getFirst(element e, hashtable* ht){

	printf("\tFinding First of %s ...\n", e->value);
	if(e->first->head!=NULL) {
			ll temp_list = getFirst(e, ht);
			ll l_copy = copyList(temp_list->head);
			return l_copy;
	}

	ll l = createLinkedList();
	if(e->flag == 0 || e->flag==1) {
		l = insertInList(l, createNode(createElement(e->value)));
		return l;
	}
	ll temp = e->grammar->head;
	while(temp!=NULL){
		node n = temp->head;
		while(n!=NULL){
			if(e!=n->ele){
			ll temp_list = getFirst(n->ele, ht);
			//int fl = 0;
			ll l_copy = copyList(temp_list->head);
			l = concatList(l, l_copy);
			if(!containsEPS(temp_list)) break;
			}
			n = n->next;
		}
		temp = temp->next1;
	}
	return l;
}

ll removeEps(ll l){
	node temp = l->head;
	if(temp==NULL) return l;
	while(temp->next!=NULL){
		if(strcmp(temp->next->ele->value,"eps")==0){
			temp->next = temp->next->next;
		}
		temp = temp->next;
	}
	return l;
}

ll getRecursiveFirst(node n, hashtable* ht, node self){

	ll l = createLinkedList();
	while(n!=NULL){
		if(self->ele!=n->ele){
			ll temp_list = n->ele->first;
			ll l_copy = copyList(temp_list->head);
			l = concatList(l, l_copy);
			if(!containsEPS(temp_list)) break;
		}
		n = n->next;
	}	
	l = removeEps(l);
	return l;
}

