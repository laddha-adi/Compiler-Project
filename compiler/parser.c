#include "parser.h"

int hash_size = 10000;
#define PTrows 52
#define PTcols 55
#define Ngrammar 94

int hashcode(char* string){
  const int p=31;
  const int m=hash_size;
  int hashValue=0;
  long long power=1;
  for(int i=0;i<strlen(string);i++){
    hashValue+=(string[i]*power)%m;
    power*=p;
  }
  return hashValue%m;
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
        printf("***************Collision*************** \n");
        // return e_1;
    }
    int hash = hashcode(e->value);
    // printf("%d\n",hash );
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
	
	node* grules=(node*)malloc(Ngrammar*sizeof(node));

    

    FILE* fp1=fopen(filename,"r");
    if(fp1==NULL){
        printf("FILE ERROR\n");
        exit(1);
    }
    char* tok;
    int i=0;
    char grLine[400];
    char delimit[]=" \t\r\n\v\f";   
    while(fgets(grLine,400,fp1)!=NULL){
        
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
    if(fclose(fp1)==0) printf("GrammarFile closed\n");
    return grules;
}


void getFirst(hashtable ht,char* firstfile){
	FILE * fp2 = fopen(firstfile, "r");
	if (fp2 == NULL) {
		printf("Unable to read follow file.\n");
		return ;
	}	

	char grLine[400];
	char delimit[]=" \t\r\n\v\f";   
	
	char *tok;
   	tok = (char*) malloc(sizeof(char)*50);
    
    while(fgets(grLine,400,fp2)!=NULL){    
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
  		// printf("PRINTING FIRST\n");
  		// printf("%s\n",nonterminal->value );
  		// printrule(nonterminal->first);
   	}  
    if(fclose(fp2)==0) printf("FirstFile closed\n");
	return;



}

void getFollow(hashtable ht,char* followfile){
	FILE * fp3 = fopen(followfile, "r");
	if (fp3 == NULL) {
		printf("Unable to read follow file.\n");
		return ;
	}	

	char grLine[400];
	char delimit[]=" \t\r\n\v\f";   
	
	char *tok;
    int i=0;
   	tok = (char*) malloc(sizeof(char)*50);
    
    while(fgets(grLine,400,fp3)!=NULL){   

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
  		// printf("PRINTING FOLLOW\n");
  		// printf("%s\n",nonterminal->value );
  		// printrule(nonterminal->follow);
   	}  
    if(fclose(fp3)==0) printf("FollowFile closed\n");
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


int hashFun(char* string ){
	int hash = 3;
	for(int i = 0; i < strlen(string); i++){
		hash = (hash*397 + string[i])%5000;
	}
	return hash;
}

// char* get(){
  
// }

int getColumnIndex(char* string){

	char* tokens[PTcols-1]= {"TK_ASSIGNOP", "TK_COMMENT", "TK_FIELDID", "TK_ID", "TK_NUM", "TK_RNUM", "TK_FUNID", "TK_RECORDID", "TK_WITH", "TK_PARAMETERS", 
	"TK_END", "TK_WHILE", "TK_TYPE", "TK_MAIN", "TK_GLOBAL", "TK_PARAMETER", "TK_LIST", "TK_SQL", "TK_SQR", "TK_INPUT", "TK_OUTPUT", "TK_INT", "TK_REAL", "TK_COMMA",
	 "TK_SEM", "TK_COLON", "TK_DOT", "TK_ENDWHILE", "TK_OP", "TK_CL", "TK_IF", "TK_THEN", "TK_ENDIF", "TK_READ", "TK_WRITE", "TK_RETURN", "TK_PLUS", "TK_MINUS", "TK_MUL", "TK_DIV",
	  "TK_CALL", "TK_RECORD", "TK_ENDRECORD", "TK_ELSE", "TK_AND", "TK_OR", "TK_NOT", "TK_LT", "TK_LE", "TK_EQ", "TK_GT", "TK_GE", "TK_NE", "$"};

	for(int i=0; i<PTcols-1; i++){
		if(strcmp(string, tokens[i])==0)
		{
		  return i+1;
		}
		
	}
	return -1;
}

int getRowIndex(char* string){
  char* nt[PTrows]= {"program", "mainFunction", "otherFunctions", "function", "input_par", "output_par", "parameter_list", "dataType", "primitiveDatatype",
  "constructedDatatype","remaining_list","stmts","typeDefinitions","typeDefinition","fieldDefinitions","fieldDefinition","moreFields",
  "declarations","declaration","global_or_not","otherStmts","stmt","assignmentStmt","singleOrRecId","new_24","funCallStmt","outputParameters","inputParameters",
  "iterativeStmt","conditionalStmt","elsePart","ioStmt","allVar","arithmeticExpression","expPrime","term","termPrime","factor","lowPrecedenceOperators",
  "highPrecedenceOperators","all","temp","booleanExpression","var","logicalOp","relationalOp","returnStmt","optionalReturn","idList","more_ids","newallvar","allnew"};
  for(int i=0; i<PTrows; i++)
  {
    if(strcmp(string, nt[i])==0)
    {
      return i;
    }
  }
  return -1;
}


parseTable createParseTable(hashtable ht,node* grules){

	// parseTable pt;
	parseTable pt=(parseTable)malloc(PTrows*sizeof(int*));

	for(int i=0;i<PTrows;i++){
		pt[i]=(int*)malloc(PTcols*sizeof(int));
	}

	for(int i=0;i<PTrows;i++){
		for(int j=0;j<PTcols;j++){
			pt[i][j]=-1;
			// printf("%d ",pt[i][j] );
		}
		// printf("\n");
	}

	node firstalpha;
	
	for(int i=0;i<Ngrammar;i++){
		
		
		firstalpha=(node)malloc(Ngrammar*sizeof(struct Node));
		firstalpha=getFirstAlpha(grules[i]->next, ht);
    // printf("%d\n",i );
    // printrule(firstalpha);

		char* nonterminal=(char*)malloc(40*sizeof(char));
		nonterminal=grules[i]->string;

		node temp=firstalpha;
		int eps=0,dollar=0;
		while(temp!=NULL){
			if(strcmp(temp->string,"eps")){
				pt[getRowIndex(nonterminal)][getColumnIndex(temp->string)]=i;
				
			}
			else{
				eps=1;
				node temp2= ht[hashcode(nonterminal)]->follow;
				while(temp2!=NULL){
				if(strcmp(temp2->string,"$")){
					dollar=1;
				}
				pt[getRowIndex(nonterminal)][getColumnIndex(temp2->string)]=i;
				temp2=temp2->next;
				}

			}
			temp=temp->next;
		}
		if(eps==0){
				node follow= ht[hashcode(nonterminal)]->follow;
				node temp2 = follow;
				while(temp2!=NULL){
				if(strcmp(temp2->string,"$")){
					dollar=1;
				}
				if(pt[getRowIndex(nonterminal)][getColumnIndex(temp2->string)]==-1)
				pt[getRowIndex(nonterminal)][getColumnIndex(temp2->string)]=-2;
				temp2=temp2->next;
				}
			}
		if(dollar==1 && eps==1){
			pt[getRowIndex(nonterminal)][getColumnIndex("$")]=i;
		}

		free(firstalpha);
	}
	return pt;
}

node getFirstAlpha(node rule, hashtable ht){//be careful while using this. first set ka first element is garbage. use first->next
	node first=(node)malloc(sizeof(struct Node));
	first->next=NULL;
	node temp=rule;
	while(temp!=NULL){
    // printf("%s\n",temp->string );
    // printrule(ht[hashcode(temp->string)]->first);
		mergeLists(first,ht[hashcode(temp->string)]->first);
    // printrule(first);
		if(epsinFirst(temp,ht)){
			temp=temp->next;
			if(temp==NULL){
				// printf("eps detected\n");
				node temprandom=first->next;
				node addeps=(node)malloc(sizeof(struct Node));
				addeps->string = (char*)malloc(sizeof(char)*40);
				strcpy(addeps->string,"eps");
				//printf("%s\n",tempprev->next->string);
				addeps->flag=0;
				addeps->next=temprandom;
				first->next=addeps;
			}
			//printf("%s\n",first->string );
			continue;
		}

		break;
		
	}
	return first->next;

}

void mergeLists(node list1,node list2){//copies second list into first without duplicates


		node temp2=list2;
		node temp;
		node tempprev;
		while(temp2!=NULL){
			temp=list1;

			int flag=0;
			while(temp!=NULL){

				if(!strcmp(temp->string,temp2->string)){
					flag=1;
					break;
				}
				tempprev=temp;
				temp=temp->next;
			}
			if(flag==0 && strcmp(temp2->string,"eps")!=0 ){
				tempprev->next=(node)malloc(sizeof(struct Node));
				tempprev->next->string = (char*)malloc(sizeof(char)*40);
				strcpy(tempprev->next->string,temp2->string);
				//printf("%s\n",tempprev->next->string);
				tempprev->next->flag=temp2->flag;
				tempprev->next->next=NULL;

			}
			//printrule(list1);
			temp2=temp2->next;
		}


		//printrule(list1);
}


int epsinFirst(node nonterminal,hashtable ht){
	node temp=ht[hashcode(nonterminal->string)]->first;

	while(temp!=NULL){
		if(!strcmp(temp->string,"eps"))
			return 1;
		temp=temp->next;
	}
	return 0;
}


int stack_size = 10000;


stack createStack(){
    stack s = (stack) malloc(sizeof(struct Stack));
    s->arr = (int*) malloc(sizeof(int)*stack_size);
    s->top = -1;
    return s;
}

void push(stack s, int rule_no, char* lable){
	  // printf("Pushing Rule no: %d in %s\n", rule_no, lable);
    s->top = s->top +1 ;
    if(s->top==stack_size) printf("Stack size reached %d\n", s->top);
    s->arr[s->top] = rule_no;
}

int getTop(stack s){
    return s->arr[s->top];
}


int pop(stack s, char* lable){
    int d = s->arr[s->top];
    s->top = s->top - 1;
	  // printf("Popping Rule no: %d From %s\n", d, lable);
    return d;
}


int isEmpty(stack s){
    if(s->top == -1) return 1;
    return 0;
}

treenode createTreeNode(char *a, int Id){
    treenode newNode = (treenode) malloc(sizeof(struct TreeNode)); 
    
    newNode->children = NULL;
    newNode->next = NULL;
    newNode->parent = NULL;
    newNode->prev = NULL;

    char* c_temp = (char*) malloc(sizeof(char)*30);
    strcpy(c_temp, a);
    newNode -> lexeme = c_temp;
    newNode -> id = Id;
    return newNode;
}
/*nonLeafNode* createNonLeafNode(){
    return (nonLeafNode) malloc(sizeof(struct NonLeafNode)); 
}
leafNode* createLeafNOde(){
    return (leafNode) malloc(sizeof(struct LeafNode)); 
}
*/
void printStack(stack s){
  //int end = getTop(s);
  printf("printing stack:\n");
  while(!isEmpty(s)){

    printf("%d \n", pop(s,"sdf"));
  }
}
void printTree(treenode t){
    printf("%s ==> ",t->lexeme);
    treenode temp = t->children;
    while(temp!=NULL) {
        printf("%s,",temp->lexeme);
        temp = temp -> next;
    }
    printf("\n");
    treenode temp2 = t->children;
    while(temp2!=NULL) {
        printTree(temp2);
        temp2 = temp2 -> next;
    }
    return;
}

treenode parseInputSourceCode(FILE* fp, table pTable, node* gRules, tokenInfo token, char*buffer, int bsize){
   // FILE* fp=fopen("Testcases/testcase2.txt","r");
    if (fp==NULL) 
        {
            fputs ("File error",stderr);
            exit (1);
        }


  //  int bsize=30;
  //  char *buffer=(char*)malloc(bsize*sizeof(char));
    //printf("Token: %s\n",token.value);

    while(strcmp(token.value,"%")==0){
      token = getNextToken(fp,buffer,bsize);
    }
    int ip = token.tokenId;

    stack s = createStack();

    push(s, 54, "Stack1");
    push(s, 100, "Stack1");

    treenode t_head = createTreeNode("program",0);
    treenode t_ptr = t_head;

    int X = getTop(s); 

    do{  // (X != $ )
    printf("rule no For X = %d , ip = %d ,line no: %d : %d\n", X, ip,token.line, pTable[X%100][ip]);
        if(X==ip) {
            int t = pop(s, "Stack1");
            //t_ptr = t_ptr->parent;

            token = getNextToken(fp,buffer,bsize);
            // printf("buffer %s offset %d\n",buffer,offset );
            while(strcmp(token.value,"%")==0){
              token = getNextToken(fp,buffer,bsize);
            }
            ip = token.tokenId;

//Uncomment this

            //Go to parent ya right
            while(t_ptr->next == NULL){
                if(t_ptr==t_head){
                    return t_head;
                }
                t_ptr = t_ptr -> parent;
            }
            t_ptr = t_ptr -> next;
			//printf("t_ptr %s", t_ptr->lexeme);
	    

    }

        else if(X<100){
             error(X, ip);
            // moove tree pointer up.
        }
        else if(pTable[X%100][ip] == -1){
            //Error
          //printTree(t_head);
          printStack(s);
            error(X, ip);
        }
        else if(pTable[X%100][ip] == -2){
            //Sync
            printStack(s);
            sync(X,ip);
        }
        else {
            int rule_id = pTable[X%100][ip];

            node rule = gRules[rule_id];

            //Insert Rule in parse Tree.
            rule = rule -> next;
            //printrule(rule);
            if(strcmp(rule->string,"eps")!=0){
                t_ptr->children = (treenode) malloc(sizeof(struct TreeNode));
				        t_ptr->children =  addChildrenRule(t_ptr,rule);
                //printf("Added to parent: %s\n",t_ptr->lexeme);
                t_ptr=t_ptr->children;
                //printf("T_ptr now: %s\n",t_ptr->lexeme);

                //pop the stack.
                pop(s, "Stack1");

                stack temp_stack = createStack(); 
                //push in dummy stack;
                node temp = rule;
                while(temp!=NULL){
					//printf("Calling!...\n");
                    int temp_id = getId(temp->string);
					//printf("id getting here for %s-> %d \n", temp->string, temp_id);
                    push(temp_stack, temp_id, "Stack2");
					         temp = temp->next;
                }
                while(!isEmpty(temp_stack)){
                    push(s, pop(temp_stack, "Stack2"), "Stack1");
                }
			//printf("out\n");
            }

            else{
                //handle eps.
                while(t_ptr->next == NULL){
                if(t_ptr==t_head){
                    return t_head;
                }
                t_ptr = t_ptr -> parent;
            }
            t_ptr = t_ptr -> next;
                pop(s, "Stack1");
            }

        }
        X = getTop(s);
    }while(X!=54);

    //error(X,ip);
    return t_head;
}

/*

treenode copyRule(treeneode parent,node n){
	treenode head = createTreenode();	  
	while(n!=NULL){
		
	}
}*/
void error(int X, int ip){
    printf("error: X : %d ip: %d\n", X, ip);
    exit(0);
}

void sync(int X, int ip){
    printf("sync: X : %d ip: %d\n", X, ip);
    exit(0);
}


/*
void printParseTree(table pTable,char* outFile){
    
}*/

// int isFollow(int X, int ip,hashtable ht){

    
//     //add if (X is a terminal ) return 1; stmt.

//     return 0;
// }

// void addChild(treenode pNode, treenode cNode){
//     treenode temp = pNode->children;
//     cNode->parent = pNode;
//     if(temp==NULL) {
//         pNode->children = cNode;
//         return;
//     }
//     while(temp->next != NULL) temp = temp->next;
//     temp->next = cNode;
//     cNode->prev = temp;
// }

// treenode  addChildrenRule(treenode parent, node gListHead){
// 	//printf("Inserting children of %s \n",parent->lexeme);
// 	//printrule(gListHead);

//     node temp = gListHead;
//     int a = 1;
//     treenode ret_node;
//     while(temp!=NULL){
//         a--;
//         int id = getId(temp->string);
//         treenode t_node = createTreeNode(temp->string,id);
//         if(a==0) ret_node = t_node;
//         addChild(parent,t_node);
//         temp = temp->next;
//     }
// 	//printTree(ret_node);
//     return ret_node;
// }

treenode addChildrenRule(treenode parent,node n){
    //printf("Inserting children of %s \n",parent->lexeme);
    //printrule(n);

    node temp = n;
    treenode head = createTreeNode(n->string,getId(n->string));
    head->next = NULL;
    treenode t = head;
    head->parent = parent;
    n = n->next;
    treenode temp2;
    while(n!=NULL){
      t->next = createTreeNode(n->string,getId(n->string));
      t->next->next = NULL;
      t->next->parent=parent; 
      n = n->next;
      //temp = t;
      t = t->next;
    }
    //t=NULL;
    return head;
}

int getId(char* string)
{
	int i;
  if(string[0]>='A' && string[0]<='Z')
    i =  getColumnIndex(string);
  else
    i = getRowIndex(string)+100;

//printf("%s -> %d \n",string, i );
return i;
}
/*const int bsize=1000;
char *buffer=(char*)malloc(bsize*sizeof(char));
*/
int main(){
    hashtable ht=createHashTable();
    node * gRules = readGrammar("Grammar.txt",ht);
    getFirst(ht,"First.txt");
    getFollow(ht,"Follow.txt");
    parseTable pTable = createParseTable(ht,gRules);
    FILE* fp=fopen("Testcases/testcase3.txt","r");
    if (fp==NULL) 
        {
            fputs ("File error",stderr);
            exit (1);
        }
 int bsize=1000;
char *buffer=(char*)malloc(bsize*sizeof(char));
    
    
    tokenInfo t;
    t=getNextToken(fp,buffer,bsize);
    // printf("buffer %s offset %d\n",buffer,offset );
    
    // printf("creating\n");
    // fclose(fp);
    // parseTable pTable = createParseTable(ht,gRules);
//FILE* fw = fopen("parseTable2.txt", "w");
     // for(int i=0;i<PTrows;i++){
     //   for(int j=1;j<PTcols;j++){
     //    printf("%d ",pTable[i][j] );
     //   }
     //  printf("\n");
     // }
//fclose(fw);
     // printf("%d\n",pTable[getRowIndex("lowPrecedenceOperators")][getColumnIndex("TK_PLUS")] );
     // printrule(ht[hashcode("TK_PLUS")]->first);
     // printf("%d %d\n",hashcode("TK_PLUS"),hashcode("TK_RETURN") );
   treenode w = parseInputSourceCode(fp, pTable,gRules,t,buffer, bsize);
   // printf("%s", w->lexeme);

   printTree(w);
    // if(fclose(lexerfile)==0) printf("lexerFile closed\n");
    return 0;
}

