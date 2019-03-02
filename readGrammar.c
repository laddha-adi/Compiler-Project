#include "readGrammar.h"
#include <string.h>
#include "lexer.h"
#include "lexerDef.h"

int MEM2 = 0;

grammarRules readFile(char * fileName, hashtable ht){
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

 void insertAllRulesInHash(grammarRules gr,hashtable ht){
	ll temp = gr->head;
	while(temp!=NULL){
		element e = searchInTable(ht,temp->head->ele->value);
		ll n = createLinkedList();
		n->head = temp->head->next;
		e->flag = -1;
		e->grammar = insertInListOfList(e->grammar,n);
		temp = temp->next1;
	}
	return ;
}



int main(){

	printf("\n--------------------------------------------------------");
	printf("\nCreating HashTable\n");
    printf("--------------------------------------------------------\n");
	hashtable ht = createHashTable();

	
	ht = insertToHash(createElement("$"), ht);


	printf("\n--------------------------------------------------------");
	printf("\nReading File\n");
    printf("--------------------------------------------------------\n");
	grammarRules gr = readFile("Grammar.txt", ht);



	printf("\n--------------------------------------------------------");
	printf("\nInserting Grammar Rules in Elements\n");
    printf("--------------------------------------------------------\n");
	insertAllRulesInHash(gr,ht);

	
	printf("\n--------------------------------------------------------");
	printf("\nAdding First\n");
    printf("--------------------------------------------------------\n");
	addFirst(gr, ht);
	//printFirstSet(gr);


	printf("\n--------------------------------------------------------");
	printf("\nAdding Follow\n");
    printf("--------------------------------------------------------\n");
	readFollow("Follow.txt", gr, ht);
	//printFollowSet(gr);


	printf("\n--------------------------------------------------------");
	printf("\nEnd\n");
    printf("--------------------------------------------------------\n");


    free(ht);
    free(gr);

    LexerMain();

	return 0;
}

void LexerMain(){
	FILE* fp=fopen("Testcases/testcase1.txt","r");
	if (fp==NULL) 
		{
			fputs ("File error",stderr);
			exit (1);
		}
	
	FILE* fp2=fopen("cleanfile","w");
	if (fp2==NULL) 
		{
			fputs ("File error",stderr);
			exit (1);
		}

	removeComments(fp,fp2);
	int bsize=30;
	char *buffer=(char*)malloc(bsize*sizeof(char));
	tokenInfo token;
	token=getNextToken(fp,buffer,bsize);

	while(token.tokenId!=54){
		printf("token %d %d %s \n",token.tokenId,token.line,token.value);
		token=getNextToken(fp,buffer,bsize);
	}

}





