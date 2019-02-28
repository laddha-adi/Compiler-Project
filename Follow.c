#include "Follow.h"

void addFollow(grammarRules gr, hashtable* ht){
	
	element e = createElement("$");
    node n = createNode(e);

	gr -> head -> head -> ele -> follow = copyList(n);

	ll temp = gr->head->next1;
	while(temp!=NULL){
		node t2 = temp->head;
		while(t2->next!=NULL){
			if(t2->ele -> flag == -1){
				ll l = getRecursiveFirst(t2->next,ht,t2);
				ll l_copy = copyList(l->head);
				l_copy = removeEps(l_copy);
				
				t2 -> ele -> follow = concatList(t2->ele->follow, l_copy);

				printf("Follow for %s is : ", t2->ele->value);
				print(t2->ele->follow);
				printf("\n");
			}
			t2 = t2->next;
		}
		temp = temp->next1;		
	}
	return;
}

