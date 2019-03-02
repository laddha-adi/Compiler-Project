#include "hash.h"
#include "Follow.h"
#include "First.h"




int MEM =0;
int hash_size = 1000;
int hashcode(char* string){
	int hash = 3;
	for(int i = 0; i < strlen(string); i++){
		hash = (hash*37 + string[i])%hash_size;
	}
	return hash;
}

hashtable createHashTable(){
	hashtable ht = (hashtable)malloc(sizeof(element)*(hash_size+1));
	MEM += (hash_size+1)*sizeof(hashtable);
	//printf("%d createHashTable \n", MEM);
	//printf("Here6");
	// int i;
	// for(i = 0; i < (hash_size + 1); i++){
	// 	ht[i]=(element)malloc(sizeof(struct elementOfHash));
	// 	// MEM += sizeof(struct elementOfHash);
	// 	// printf("%d createHashTable inside for\n", MEM);
	// 	// //ht[i]=NULL;
	// }
	// //ht->head= NULL
	if(ht==NULL) printf("LOL Sahil!!");
	//	printf("Here5");
	return ht;
}

element createElement(char* string){
	element e = (element)malloc(sizeof(struct elementOfHash));
		
		MEM += sizeof(struct elementOfHash);
		//printf("%d create Element\n", MEM);

	e->grammar = createListofList();
	e->first = createLinkedList();
	e->follow = createLinkedList();
	e->value = (char*) malloc(sizeof(char)*50);
	char* str = (char*) malloc(sizeof(char)*50);
	
		MEM += 50*sizeof(str);
		//printf("%d createElement 2\n", MEM);
	
	strcpy(str,string);
	e->value = str;
	//printf("%s\n",e->value);
	// if(strcmp("eps", str)==0){
	// 	e->flag = 0;
	// }else{
	// 	e->flag = 1;   //-1 : Non Terminal, 0: eps, 1: Terminal
	// }
	return e;
}

hashtable insertToHash(element e,hashtable ht){

	element e_1 = searchInTable(ht, e->value);
	if(e_1 != NULL) {
		printf("***************Collision*************** %s %s\n",e->value, e_1 -> value);
	}

	int hash = hashcode(e->value);
	//element temp = ht[hash]->head;
	//printf("here1\n");
	ht[hash] = e;
	//e->next = temp;
	return ht;
}

element searchInTable(hashtable ht,char* string){
	int hash = hashcode(string);
	//element temp = createElement("");
	if(ht[hash]==NULL)
		return NULL;
	else 
		return ht[hash];
	//printf("%s\n",ht[hash]->value);
	// element temp;
	// temp = ht[hash];
	// printf("%s\n",temp->value);
	// // while(temp!=NULL){
	// 	if(strcmp(temp->value, string)==0){
	// 		printf("exists\n");
	// 		return temp;
	// 	}
	// // 	temp = temp->next;
	// // }
	// //printf("element not found, inserting... %s\n", string);
	// return NULL;
}

dl createListofList(){
	dl list = (dl)malloc(sizeof(struct listOfList));

		MEM += sizeof(struct listOfList);
		//printf("%d createListofList\n", MEM);

	list->head = NULL;
	return list;
}

ll createLinkedList(){
	ll ls = (ll)malloc(sizeof(struct LinkedList));

		MEM += sizeof(struct LinkedList);
		//printf("%d createLinkedList\n", MEM);

	ls->head = NULL;
	return ls;
}

node createNode(element e){
	node n = (node)malloc(sizeof(struct Node));

		MEM += sizeof(struct Node);
		//printf("%d createNode\n", MEM);
	//char* str = (char*) malloc(sizeof(char)*20);
	//strcpy(str,a);
	n->ele = e;
	//printf("%s\n",n->data);
	return n;
}

ll insertInOrder(ll ls ,node n){
	node temp = ls->head;
	if(temp==NULL){
		ls->head = n;
		return ls;
	}
	while(temp->next!=NULL)
		temp = temp->next;
	temp->next = n;
	n->next = NULL;
	return ls;
}
ll insertInList(ll ls,node n){
	node temp = ls->head;
	ls->head = n;
	n->next = temp;
	return ls; 
}
void print2(dl d){
	ll temp = createLinkedList();
	temp = d->head;
	while(temp!=NULL){
		print(temp);
		temp = temp->next1;
		printf("\n");
	}
}
dl insertInOrderList(dl d,ll ls){
	ll temp = d->head;
	if(temp==NULL){
		d->head = createLinkedList();
		d->head = ls;
		return d;
	}
	while(temp->next1!=NULL)
		temp = temp->next1;
		temp->next1 = createLinkedList();
		temp->next1 = ls;
		ls->next1 = NULL;
	return d;
}

dl insertInListOfList(dl d,ll ls){
	ll temp = createLinkedList();
	temp = d->head;
	d->head = ls;
	ls->next1 = temp;
	//print2(d);
	return d;
}

void print(ll ls){
	node temp = ls->head;
	while(temp!=NULL){
		printf("%s(%d)\t",temp->ele->value, temp->ele->flag);
		temp = temp->next;
	}
}

/*void print2(dl d){
	ll temp = d->head;
	while(temp!=NULL){
		print(temp);
		printf("\n");
		temp = temp->next1;
	}
}
*/


void printNtList(ll ls){
	node temp = ls->head;
	while(temp!=NULL){
		//if(temp->flag == -1) printf("%s\n",temp->data);
		//temp = temp->next;
	}
}

void printTList(ll ls){
	node temp = ls->head;
	while(temp!=NULL){
		//if(temp->flag == 1) printf("%s\n",temp->data);
		//temp = temp->next;
	}
}


void printFollowSet(dl d){
	ll temp = createLinkedList();
	temp = d->head;
	while(temp!=NULL){
		printf("Follow [ %s ] = ",temp->head->ele->value);
		print(temp->head->ele->follow);
		printf("\n");
		temp = temp->next1;
	}
}
void printFirstSet(dl d){
	ll temp = createLinkedList();
	temp = d->head;
	while(temp!=NULL){
		printf("First [ %s ] = ",temp->head->ele->value);
		print(temp->head->ele->first);
		printf("\n");
		temp = temp->next1;
	}
}

void printT(dl d){
	ll temp = createLinkedList();
	temp = d->head;
	while(temp!=NULL){
		printTList(temp);
		temp = temp->next1;
	}
}

ll copyList(node n){
	ll l = createLinkedList();
	while(n!=NULL){
		node t = createNode(n->ele);
		l = insertInOrder(l, t);
		n = n->next;
	}
	return l;
}

int find(node n, ll l){
	node temp = l->head;
	while(temp!=NULL){
		if(strcmp(temp->ele->value, n->ele->value)==0) return 1;
		temp = temp->next;
	}
	return 0;
} 

ll concatList(ll l1, ll l2){
	node templ1 = l1->head;
	node templ2 = l2->head;
	if(templ1==NULL) return l2;
	if(templ2 == NULL) return l1;

	while(templ2!=NULL){
		if(find(templ2, l1)==0){
			l1 = insertInList(l1, createNode(templ2->ele));
		}
		templ2 = templ2->next;
	}	
	return l1;
}

int containsEPS(ll l){
	node temp = l->head;
	while(temp!=NULL){
		//printf("%s\t",temp->ele->value);
		if(temp->ele->flag == 0) return 1;
		temp = temp->next;
	}
	return 0;
}



//////readgrammar.c ka code

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
   		/*tok = (char*) malloc(sizeof(char)*50);
 			MEM2 += 50*sizeof(char);
			printf("%dreadGrammar -> readFile\n", MEM2);*/
   		tok = strtok (grLine,delimit);

  		while (tok != NULL){
  				element e = searchInTable(ht, tok);
    			if(e==NULL)	{
    				e = createElement(tok);
    				//printf("created\n");
    				ht = insertToHash(e, ht);
    				printf("adding to hash %s\n", e->value);
    			}
    			else{
    				//printf("collided\n");
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
	//ll temp = createLinkedList();
	ll temp = gr->head;
	
	while(temp!=NULL){
		element e = searchInTable(ht,temp->head->ele->value);
		ll n = createLinkedList();
		n->head = temp->head->next;
		// print(n);
		// printf("\n");
		e->grammar = insertInListOfList(e->grammar,n);
		// printf("%d\n", i);
		print2(e->grammar);
		printf("\n");
		//addGrammarRule(temp->head->ele, temp);
		temp = temp->next1;

	}
	return ;
}



void addGrammarRule(element e, ll l){
	e -> flag = -1;
	//printf("Adding Rule ");
	//printf("%s --> ", e->value);
	print(l);
	printf("\n");
	e -> grammar = insertInOrderList(e->grammar, l);
	return; 
}



int main(){
	//Someone Please test this! I am not able to run it on my PC.
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



	printf("\n--------------------------------------------------------");
	printf("\nCreating HashTable\n");
    printf("--------------------------------------------------------\n\n");

	hashtable ht = createHashTable();

	
	ht = insertToHash(createElement("$"), ht);

	printf("\n\n--------------------------------------------------------");
	printf("\nReading File\n");
    printf("--------------------------------------------------------\n\n");
	grammarRules gr = readFile("Grammar.txt", ht);
	printf("------------------------ %d ------------------------\n\n", MEM2);
	print2(gr);
	printf("\n\n--------------------------------------------------------");
	printf("\nInsert Grammar Rules in Elements\n");
    printf("--------------------------------------------------------\n\n");
	
    printf("%s\n",searchInTable(ht,"TK_ID")->value);
	insertAllRulesInHash(gr,ht);
	print2(gr);
	
	printf("\n\n--------------------------------------------------------");
	printf("\nAdding First\n");
    printf("--------------------------------------------------------\n\n");
	addFirst(gr, ht);
	printFirstSet(gr);
	//printf("\n--------------------------------------------------------\n");
	//print(getRecursiveFirst(gr->head->head->next, ht, gr->head->head));
	printf("\n\n--------------------------------------------------------");
	printf("\nAdding Follow\n");
    printf("--------------------------------------------------------\n\n");
	readFollow("Follow.txt", gr, ht);
	//addFollow(gr,ht);
	//printf("\nFollow Read\n");
	printFollowSet(gr);

	printf("\n\n--------------------------------------------------------");
	printf("\nEnd\n");
    printf("--------------------------------------------------------\n\n");

    free(ht);
    free(gr);

	return 0;
}