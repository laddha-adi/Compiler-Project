#include "Follow.h"

void addFollow(grammarRules gr, hashtable* ht){
	ll temp = gr->head;
	while(temp!=NULL){
		node t2 = temp->head;
		while(t2->next!=NULL){
				ll l = getRecursiveFirst(t2->next,ht,t2);
				ll l_copy = copyList(l->head);
				l_copy = removeEps(l_copy);
				printf("Follow for %s is : ", t2->ele->value);
				print(l_copy);
				printf("\n");
			t2 = t2->next;
		}
		temp = temp->next1;		
	}
	return;
}

