#include "readGrammar.h"
#include <string.h>

grammarRules readFile(char * fileName, hashtable* ht){
	grammarRules gRules = createListofList();
	FILE * fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Unable to read grammar file.\n");
		return gRules;
	}	
	char c;
	char grLine[400];
	char delimit[]=" \t\r\n\v\f";   
    while(fgets(grLine,400,fp)!=NULL){    
    	singleRule sr = createLinkedList();
   		char *tok;
   		tok = (char*) malloc(sizeof(char)*50);
   		tok = strtok (grLine,delimit);

  		while (tok != NULL){
  				element e = searchInTable(ht, tok);
    			if(e==NULL)	e = createElement(tok);
    			node n = createNode(e);
			    ht = insertToHash(e, ht);
				if(n!=NULL){
					sr = insertInOrder(sr, n);
    			}else{
    				printf("Unable to create new Element.\n");
				}
    		tok = strtok (NULL, delimit);
  		}

  		gRules = insertRule(gRules, sr);
   	}  
	fclose(fp);
	return gRules;
}

grammarRules insertRule(grammarRules gRules, singleRule sRule){
	gRules = insertInOrderList(gRules, sRule);
	return gRules;
}

hashtable* insertAllRulesInHash(grammarRules gr, hashtable* ht){
	ll temp = createLinkedList();
	temp = gr->head;
	while(temp!=NULL){
		node nl = temp->head->next;
		ll l_copy = copyList(nl);
		addGrammarRule(temp->head->ele, l_copy);
		temp = temp->next1;
	}
	return ht;
}



void addGrammarRule(element e, ll l){
	e -> flag = -1;
	//printf("Adding Rule ");
	//printf("%s --> ", e->value);
	//print(l);
	//printf("\n");
	e -> grammar = insertInOrderList(e->grammar, l);
	return; 
}



int main(){
	//Someone Please test this! I am not able to run it on my PC.
	hashtable* ht = createHashTable();
	ht = insertToHash(createElement("$"), ht);
	grammarRules gr = readFile("Grammar.txt", ht);
	ht = insertAllRulesInHash(gr, ht);
	print2(gr);
	addFirst(gr, ht);
	printFirstSet(gr);
	printf("\n--------------------------------------------------------\n");
	//print(getRecursiveFirst(gr->head->head->next, ht, gr->head->head));
	readFollow("Follow.txt", gr, ht);
	//addFollow(gr,ht);
	printf("\nFollow Read\n");
	printFollowSet(gr);
//	return 0;
}



