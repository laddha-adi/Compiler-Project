#include "Follow.h"

void addFollow(grammarRules gr, hashtable ht){
	
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
		if(t2->ele->flag = -1) {

		}
		temp = temp->next1;		
	}

	int i = 0;
	for(i=0;i<20;i++){
		ll tem = gr->head;
		while(tem!=NULL){
			node t2 = tem->head;
			tem = tem->next1;		
		}
	}
	return;
}


void readFollow(char* fileName, grammarRules gr, hashtable ht){
	FILE * fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Unable to read grammar file.\n");
		return ;
	}	
	char c;
	char grLine[400];
	char delimit[]=" \t\r\n\v\f";   
	
	char *tok;
   	tok = (char*) malloc(sizeof(char)*50);
    
    while(fgets(grLine,400,fp)!=NULL){    
    	singleRule sr = createLinkedList();
   		tok = strtok (grLine,delimit);
   		element e_main = searchInTable(ht, tok);
   		tok = strtok(NULL, delimit);
  		while (tok != NULL){
  				element e = searchInTable(ht, tok);
    			if(e==NULL)	{
    				printf("Element %s Not found\n", tok);
    			}
    			node n = createNode(e);
				if(n!=NULL){
					sr = insertInOrder(sr, n);
    			}
    			else{
    				printf("Unable to create new Node.\n");
				}
    		tok = strtok (NULL, delimit);
  		}
  		e_main->follow = sr;
   	}  
	fclose(fp);
	return;
}

