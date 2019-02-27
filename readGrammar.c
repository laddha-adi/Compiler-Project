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
	char grLine[200];
	char delimit[]=" \t\r\n\v\f";   
    while(fgets(grLine,200,fp)!=NULL){    
    	singleRule sr = createLinkedList();
   		char *tok;
   		tok = (char*) malloc(sizeof(char)*20);
   		tok = strtok (grLine,delimit);
   		
  		while (tok != NULL){
    			ht = insertToHash(tok, ht);
    			node n = createNode(tok);
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
	//print2(gr);
	while(temp!=NULL){
		//printf("1\n");
		ll l = createLinkedList();
		
		//printf("2\n");
		l -> head = temp -> head -> next;
		
		//printf("3\n");
		element e = (element)malloc(sizeof(struct elementOfHash));
		 e = searchInTable(ht, temp->head->data);
		//printf("%s", e->value);
		//printf("4\n");
		//print(l);
		//printf("\n");

		e -> grammar = insertInOrderList(e->grammar, l);
		
		//printf("5\n");
		temp = temp->next1;	
		
		//printf("6\n");

	}
	return ht;
}

int main(){
	hashtable* ht = createHashTable();
	grammarRules gr = readFile("grr.txt", ht);
	//print2(gr);
	ht = insertAllRulesInHash(gr, ht);
	print2(searchInTable(ht, "output_par")->grammar);
	//print2(gr);
	return 0;
}



