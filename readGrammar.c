#include "readGrammar.h"
#include <string.h>
#include "lexer.h"

int MEM2 = 0;

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
   		/*tok = (char*) malloc(sizeof(char)*50);
 			MEM2 += 50*sizeof(char);
			printf("%dreadGrammar -> readFile\n", MEM2);*/
   		tok = strtok (grLine,delimit);

  		while (tok != NULL){
  				element e = searchInTable(ht, tok);
    			if(e==NULL)	{
    				e = createElement(tok);
    				ht = insertToHash(e, ht);
    			}
    			node n = createNode(e);
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

 void insertAllRulesInHash(grammarRules gr){
	//ll temp = createLinkedList();
	ll temp = gr->head;
	while(temp!=NULL){
		addGrammarRule(temp->head->ele, temp);
		temp = temp->next1;
	}
	return ;
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

	printf("\n--------------------------------------------------------");
	printf("\nCreating HashTable\n");
    printf("--------------------------------------------------------\n\n");

	hashtable* ht = createHashTable();

	
	ht = insertToHash(createElement("$"), ht);

	printf("\n\n--------------------------------------------------------");
	printf("\nReading File\n");
    printf("--------------------------------------------------------\n\n");
	grammarRules gr = readFile("Grammar.txt", ht);
	printf("------------------------ %d ------------------------\n\n", MEM2);

	printf("\n\n--------------------------------------------------------");
	printf("\nInsert Grammar Rules in Elements\n");
    printf("--------------------------------------------------------\n\n");
	
	insertAllRulesInHash(gr);
	//print2(gr);
	
	printf("\n\n--------------------------------------------------------");
	printf("\nAdding First\n");
    printf("--------------------------------------------------------\n\n");
	addFirst(gr, ht);
	//printFirstSet(gr);
	//printf("\n--------------------------------------------------------\n");
	//print(getRecursiveFirst(gr->head->head->next, ht, gr->head->head));
	printf("\n\n--------------------------------------------------------");
	printf("\nAdding Follow\n");
    printf("--------------------------------------------------------\n\n");
	readFollow("Follow.txt", gr, ht);
	//addFollow(gr,ht);
	//printf("\nFollow Read\n");
	//printFollowSet(gr);

	printf("\n\n--------------------------------------------------------");
	printf("\nEnd\n");
    printf("--------------------------------------------------------\n\n");

    free(ht);
    free(gr);

	return 0;
}





