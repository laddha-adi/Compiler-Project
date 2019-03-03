#include "parser.h"

int hash_size = 1000;

int hashcode(char* string){
	int hash = 3;
	for(int i = 0; i < strlen(string); i++){
		hash = (hash*37 + string[i])%hash_size;
	}
	return hash;
}

hashtable createHashTable(){
	hashtable ht = (hashtable)malloc(sizeof( helement)*(hash_size+1));
	//addMem(sizeof(element)*(hash_size+1), "Creatinn HashTable");
	if(ht==NULL) printf("Memory Error!\n");	
	return ht;
}

void insertToHash(helement e,hashtable ht){

	helement e_1 = searchInTable(ht, e->value);
	if(e_1 != NULL) {
		printf("***************Collision*************** %s %s\n",e->value, e_1 -> value);
		// return e_1;
	}
	int hash = hashcode(e->value);
	ht[hash] = e;
	return ;
}


helement searchInTable(hashtable ht,char* string){
	int hash = hashcode(string);
	if(ht[hash]==NULL)
		return NULL;
	else 
		return ht[hash];
}

helement createHashElement(char* string){
	helement e = (helement)malloc(sizeof(struct Helement));
	// addMem(sizeof(struct elementOfHash), "createElement");
	e->rules = (int*)malloc(sizeof(int)*10);
	e->first = NULL;
	e->follow =NULL;
	e->nrules=0;
	e->value = (char*) malloc(sizeof(char)*40);
	strcpy(e->value,string);
	if(string[0]>='A' && string[0]<='Z'){
    			e->flag=1;
    		}
    		else if(strcmp(string,"eps")==0){
    			e->flag=0;
    		}
    		else
    			e->flag=-1;
	return e;
}

node* readGrammar(char* filename,hashtable ht){
	
	node* grules=(node*)malloc(100*sizeof(node));

	FILE* fp=fopen(filename,"r");
	if(fp==NULL){
		printf("FILE ERROR\n");
		exit(1);
	}
	char* tok;
	int i=0;
	char grLine[400];
	char delimit[]=" \t\r\n\v\f";   
    while(fgets(grLine,400,fp)!=NULL){
    	
    	grules[i]=(node)malloc(sizeof(struct Node));
    	tok = strtok (grLine,delimit);
    	
    	node temp=grules[i];
		temp->string=(char*)malloc(40*sizeof(char));
		strcpy(temp->string,tok);
 		temp->flag=-1;
 		
 		helement h= searchInTable(ht,tok);
 		if(h==NULL){
 			h=createHashElement(tok);
 			insertToHash(h,ht);
 		}
 		h->rules[h->nrules]=i;
 		h->nrules++;
 		tok = strtok (NULL, delimit);

 		
     	while (tok != NULL){
     		
     		temp->next=(node)malloc(sizeof(struct Node));;
     		temp=temp->next;
    	 	temp->string=(char*)malloc(40*sizeof(char));
    		strcpy(temp->string,tok);
     		if(tok[0]>='A' && tok[0]<='Z'){
    			temp->flag=1;
    		}
    		else if(strcmp(tok,"eps")==0){
    			temp->flag=0;
    		}
    		else
    			temp->flag=-1;
		
			helement h= searchInTable(ht,tok);
	 		if(h==NULL){
	 			h=createHashElement(tok);
	 			insertToHash(h,ht);
	 		}

			tok = strtok (NULL, delimit);
			
		}
    	
    	// printrule(grules[i]);
    	i++;
    }
    // printf("%s\n",grules[45]->next->string);
   // printrule(grules[0]);
    fclose(fp);
    return grules;
}


void getFirst(hashtable ht,char* firstfile){
	FILE * fp = fopen(firstfile, "r");
	if (fp == NULL) {
		printf("Unable to read follow file.\n");
		return ;
	}	

	char grLine[400];
	char delimit[]=" \t\r\n\v\f";   
	
	char *tok;
   	tok = (char*) malloc(sizeof(char)*50);
    
    while(fgets(grLine,400,fp)!=NULL){    
    	node sr = (node)malloc(sizeof(struct Node));
   		tok = strtok (grLine,delimit);
   		helement nonterminal = searchInTable(ht, tok);
   		tok = strtok(NULL, delimit);

   		nonterminal->first=(node)malloc(sizeof(struct Node));
   		node temp=nonterminal->first;

  		while (tok != NULL){

  				temp->string=(char*)malloc(sizeof(char)*40);
  				temp->flag=1;
  				strcpy(temp->string,tok);
  				tok = strtok (NULL, delimit);
  				if(tok!=NULL){
  				temp->next=(node)malloc(sizeof(struct Node));
  				temp=temp->next;
    			}

  		}
  		temp=NULL;
  		printf("PRINTING FIRST\n");
  		printf("%s\n",nonterminal->value );
  		printrule(nonterminal->first);
   	}  
	fclose(fp);
	return;



}

void getFollow(hashtable ht,char* followfile){
	FILE * fp = fopen(followfile, "r");
	if (fp == NULL) {
		printf("Unable to read follow file.\n");
		return ;
	}	

	char grLine[400];
	char delimit[]=" \t\r\n\v\f";   
	
	char *tok;
   	tok = (char*) malloc(sizeof(char)*50);
    
    while(fgets(grLine,400,fp)!=NULL){    
    	node sr = (node)malloc(sizeof(struct Node));
   		tok = strtok (grLine,delimit);
   		helement nonterminal = searchInTable(ht, tok);
   		tok = strtok(NULL, delimit);

   		nonterminal->follow=(node)malloc(sizeof(struct Node));
   		node temp=nonterminal->follow;

  		while (tok != NULL){

  				temp->string=(char*)malloc(sizeof(char)*40);
  				temp->flag=1;
  				strcpy(temp->string,tok);
  				tok = strtok (NULL, delimit);
  				if(tok!=NULL){
  				temp->next=(node)malloc(sizeof(struct Node));
  				temp=temp->next;
    			}

  		}
  		temp=NULL;
  		printf("PRINTING FOLLOW\n");
  		printf("%s\n",nonterminal->value );
  		printrule(nonterminal->follow);
   	}  
	fclose(fp);
	return;

}



void printrule(node ls){

	node temp=ls;
	while(temp!=NULL){
		printf("%s %d\t",temp->string, temp->flag );
		
		temp=temp->next;
	}
	printf("\n");

return ;


}

void printRuleNo(helement h){
	for(int i=0;i<h->nrules;i++){
		printf("%d \n", h->rules[i]);
	}
}
void main(){
	hashtable ht=createHashTable();
	node* grules=readGrammar("Grammar.txt",ht);
	helement h=searchInTable(ht,"booleanExpression");

	//printf("%s",h->value);
	//printRuleNo(h);
	getFollow(ht,"Follow.txt");
	getFirst(ht,"First.txt");
	// printrule(grules[0]);
	

}