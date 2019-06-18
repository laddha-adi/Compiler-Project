/*
GROUP NUMBER: 11
NIKKI GUPTA 2016A7PS0057P
SAHIL RANADIVE 2016A7PS0097P
ADITI AGARWAL 2016A7PS0095P
ADITYA LADDHA 2016A7PS0038P
*/


#include "parser.h"

int hash_size = 10000;
#define PTrows 52
#define PTcols 55
#define Ngrammar 94

int P_TREE_SIZE = 0;
int parser_error = 0;

int getPTreeSize(){
  return P_TREE_SIZE;
}

int getParsingErrors(){
  return parser_error;
}

void resetParserError(){
  parser_error = 0;
}

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
    
    rewind(fp1);
    fclose(fp1);
    // if(fclose(fp1)==0) printf("GrammarFile closed\n");
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
    rewind(fp2);
    fclose(fp2);
    // if(fclose(fp2)==0) printf("FirstFile closed\n");
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
    fclose(fp3);
    // if(fclose(fp3)==0) printf("FollowFile closed\n");
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

char* getCorrespondingString(int f){
    switch(f){
        case 1: return "TK_ASSIGNOP";
        case 2: return "TK_COMMENT";
        case 3: return "TK_FIELDID";
        case 4: return "TK_ID";
        case 5: return "TK_NUM";
        case 6: return "TK_RNUM";
        case 7: return "TK_FUNID";
        case 8: return "TK_RECORDID";
        case 9: return "TK_WITH";
        case 10: return "TK_PARAMETERS";
        case 11: return "TK_END";
        case 12: return "TK_WHILE";
        case 13: return "TK_TYPE";
        case 14: return "TK_MAIN";
        case 15: return "TK_GLOBAL";
        case 16: return "TK_PARAMETER";
        case 17: return "TK_LIST";
        case 18: return "TK_SQL";
        case 19: return "TK_SQR";
        case 20: return "TK_INPUT";
        case 21: return "TK_OUTPUT";
        case 22: return "TK_INT";
        case 23: return "TK_REAL";
        case 24: return "TK_COMMA";
        case 25: return "TK_SEM";
        case 26: return "TK_COLON";
        case 27: return "TK_DOT";
        case 28: return "TK_ENDWHILE";
        case 29: return "TK_OP";
        case 30: return "TK_CL";
        case 31: return "TK_IF";
        case 32: return "TK_THEN";
        case 33: return "TK_ENDIF";
        case 34: return "TK_READ";
        case 35: return "TK_WRITE";
        case 36: return "TK_RETURN";
        case 37: return "TK_PLUS";
        case 38: return "TK_MINUS";
        case 39: return "TK_MUL";
        case 40: return "TK_DIV";
        case 41: return "TK_CALL";
        case 42: return "TK_RECORD";
        case 43: return "TK_ENDRECORD";
        case 44: return "TK_ELSE";
        case 45: return "TK_AND";
        case 46: return "TK_OR";
        case 47: return "TK_NOT";
        case 48: return "TK_LT";
        case 49: return "TK_LE";
        case 50: return "TK_EQ";
        case 51: return "TK_GT";
        case 52: return "TK_GE";
        case 53: return "TK_NE";
        case 54: return "$";

        case 100: return "program";
        case 101: return "mainFunction";
        case 102: return "otherFunctions";
        case 103: return "function";
        case 104: return "input_par";
        case 105: return "output_par";
        case 106: return "parameter_list";
        case 107: return "dataType";
        case 108: return "primitiveDatatype";
        case 109: return "constructedDatatype";
        case 110: return "remaining_list";
        case 111: return "stmts";
        case 112: return "typeDefinitions";
        case 113: return "typeDefinition";
        case 114: return "fieldDefinitions";
        case 115: return "fieldDefinition";
        case 116: return "moreFields";
        case 117: return "declarations";
        case 118: return "declaration";
        case 119: return "global_or_not";
        case 120: return "otherStmts";
        case 121: return "stmt";
        case 122: return "assignmentStmt";
        case 123: return "singleOrRecId";
        case 124: return "new_24";
        case 125: return "funCallStmt";
        case 126: return "outputParameters";
        case 127: return "inputParameters";
        case 128: return "iterativeStmt";
        case 129: return "conditionalStmt";
        case 130: return "elsePart";
        case 131: return "ioStmt";
        case 132: return "allVar";
        case 133: return "arithmeticExpression";
        case 134: return "expPrime";
        case 135: return "term";
        case 136: return "termPrime";
        case 137: return "factor";
        case 138: return "lowPrecedenceOperators";
        case 139: return "highPrecedenceOperators";
        case 140: return "all";
        case 141: return "temp";
        case 142: return "booleanExpression";
        case 143: return "var";
        case 144: return "logicalOp";
        case 145: return "relationalOp";
        case 146: return "returnStmt";
        case 147: return "optionalReturn";
        case 148: return "idList";
        case 149: return "more_ids";
        case 150: return "newallvar";
        case 151: return "allnew";
        default:
                {
                    
                    return "Nothing";
                }
    }
}

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
		}
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
        if(temp->string!=NULL && temp2->string!=NULL)
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

treenode createTreeNode(char *a, int Id, char* lexeme){
    treenode newNode = (treenode) malloc(sizeof(struct TreeNode)); 
    
    newNode->children = NULL;
    newNode->next = NULL;
    newNode->parent = NULL;
    newNode->prev = NULL;

    newNode -> lexeme = (char*) malloc(sizeof(char)*30);

    newNode -> id = Id;
    P_TREE_SIZE += sizeof(struct TreeNode);
    return newNode;
}


int isFollow(int X, int ip,hashtable ht){

  node follow =ht[hashcode(getCorrespondingString(X))]->follow;
  while(follow!=NULL){
    if(ip==getId(follow->string)){
      return 1;
    }
    follow=follow->next;
  }
    //add if (X is a terminal ) return 1; stmt.

    return 0;
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
  exit(0);
}

void printTree(treenode t){
    printf("%s ==> ",getCorrespondingString(t->id));
    treenode temp = t->children;
    if(temp==NULL) printf("(null)");
    while(temp!=NULL) {
        printf("%s,",getCorrespondingString(temp->id));
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

treenode parseInputSourceCode(FILE* fp, parseTable pTable, node* gRules, tokenInfo token, char*buffer, int bsize, hashtable ht,int* error){
   // FILE* fp=fopen("Testcases/testcase2.txt","r");
    if (fp==NULL) 
        {
            fputs ("File error",stderr);
            exit (1);
        }
  
   // printf("Token: %s\n",token.value);

    while(strcmp(token.value,"%")==0){
      token = getNextToken(fp,buffer,bsize);
    }
    int ip = token.tokenId;

    stack s = createStack();

    push(s, 54, "Stack1");
    push(s, 100, "Stack1");

    treenode t_head = createTreeNode("program",100, "program");
    treenode t_ptr = t_head;

    int X = getTop(s); 

    do{  // (X != $ )
    // printf("rule no For X = %d , ip = %d ,line no: %d : %d\n", X, ip,token.line, pTable[X%100][ip]);
        if(X==ip) {
            int t = pop(s, "Stack1");
            //t_ptr = t_ptr->parent;
            //t_ptr->lexeme = (char)
            strcpy(t_ptr->lexeme,token.value);
            t_ptr->line = token.line;

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

        else if(X<100){ //terminal terminal clash
             //errorTerminal(X, ip);
            // move tree pointer up.

         pop(s, "error");
             while(t_ptr->next == NULL){
                if(t_ptr==t_head){
                    return t_head;
                }
                t_ptr = t_ptr -> parent;
              }
            t_ptr = t_ptr -> next;
            *error=1;
            printf("Line No:%d The token %s for lexeme %s  does not match with the expected token %s\n", token.line, getCorrespondingString(ip), token.value,getCorrespondingString(X));
            parser_error++;

          }
        else if(pTable[X%100][ip] == -1){
           //Error
          //printTree(t_head);
          while(pTable[X%100][ip]==-1){
               token = getNextToken(fp,buffer,bsize);
               ip = token.tokenId;
          }

          if(isFollow(X,ip, ht)==1){
                pop(s,"error");
             while(t_ptr->next == NULL){
                if(t_ptr==t_head){
                    return t_head;
                }
                t_ptr = t_ptr -> parent;
              }
            t_ptr = t_ptr -> next;

          }   *error=1;
              printf("Line No: %d Error: Invalid token %s encountered with value %s stack top %s\n",token.line, getCorrespondingString(ip), token.value, getCorrespondingString(X));
              parser_error++;
        }
        else if(pTable[X%100][ip] == -2){
            //Sync
            //printStack(s);
            pop(s,"compiler");
             while(t_ptr->next == NULL){
                if(t_ptr==t_head){
                    return t_head;
                }
                t_ptr = t_ptr -> parent;
            }
            t_ptr = t_ptr -> next;
              *error=1;
              printf("Line No: %d Error: Invalid token %s encountered with value %s stack top %s\n",token.line, getCorrespondingString(ip), token.value, getCorrespondingString(X));
              parser_error++;


        }
        else {
            int rule_id = pTable[X%100][ip];

            node rule = gRules[rule_id];

            //Insert Rule in parse Tree.
            rule = rule -> next;
            //printrule(rule);
            if(strcmp(rule->string,"eps")!=0){
                t_ptr->children = (treenode) malloc(sizeof(struct TreeNode));
				        t_ptr->children =  addChildrenRule(t_ptr,rule,token.line, token.value);
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

    
    return t_head;
}

void printParseTree(treenode pTree)
{
  /*char term[15];
  char lexemeCurrentNode[20];
  int lineNo;
  char token[20];
  char parentNodeSym[20];
  char value[20];
  char nodeSymbol[20];
  char isLeaf[4];*/

  if(pTree != NULL){
    printParseTree(pTree->children);
    //strcpy(term ,getCorrespondingString(pTree->id));
    
    char value[40]="N/A";
    if(pTree!=NULL && pTree->id <100) {
      if(pTree->id==6||pTree->id==5)
          strcpy(value,pTree->lexeme);
              // fprintf(fp,"LEXEME:%s\tLINE NO:%d\tTOKEN:%s\tVALUE:%s\tPARENT NODE:%s\tISLEAF():%s\tNODE SYMBOL:%s\n", pTree->lexeme, pTree->line, getCorrespondingString(pTree->id),value,getCorrespondingString(pTree->parent->id),"yes","\t" );      
          printf("%15s %6d %19s %15s %25s %8s %18s\n", pTree->lexeme, pTree->line, getCorrespondingString(pTree->id),value,getCorrespondingString(pTree->parent->id),"yes","\t" );      

    
    } 
    else {
      if(pTree!=NULL && pTree->id==100)
        printf("%15s %6d %19s %15s %25s %8s %18s\n", "----", pTree->line, "\t",value,"ROOT","no",getCorrespondingString(pTree->id) );
      else
        printf("%15s %6d %19s %15s %25s %8s %18s\n", "----", pTree->line, "\t",value,getCorrespondingString(pTree->parent->id),"no",getCorrespondingString(pTree->id) );
    }


    //printf("%-15s%-6d%-22s%-22s%-26s%-6s%-22s\n",lexemeCurrentNode, lineNo, token,value,parentNodeSym,isLeaf,nodeSymbol);
    //fprintf(outfp,"%-15s%-6d%-22s%-22s%-26s%-6s%-22s\n",lexemeCurrentNode, lineNo, token,value,parentNodeSym,isLeaf,nodeSymbol);
    if(pTree->children != NULL)
    {
      if(pTree->children->next != NULL)
      {
        treenode temp = pTree->children->next;
        while(temp != NULL)
        {
          printParseTree(temp);
          temp = temp->next;
        } 
      }
    }
  }
}



treenode addChildrenRule(treenode parent,node n, int line, char*lexeme){
    //printf("Inserting children of %s \n",parent->lexeme);
    //printrule(n);

    node temp = n;
    
    treenode head = createTreeNode(n->string,getId(n->string), lexeme);
    //if(head->line==0)
    head-> line = line;
    head->next = NULL;
    treenode t = head;
    head->parent = parent;
    n = n->next;
    treenode temp2;
    while(n!=NULL){
      t->next = createTreeNode(n->string,getId(n->string), lexeme);
      t->next->line = line;
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




void printInorderTraversal(treenode tree,char* outputFileName){
  FILE* fp=fopen(outputFileName,"w");
  inorder(tree,fp);
}

void inorder(treenode tree,FILE* fp){
  if(tree==NULL)
    return;
  inorder(tree->children,fp);
  fprintf(fp,"\n");
  fprintf(fp,"%s ",getCorrespondingString(tree->id));
  if(tree->children == NULL) {
    return;
  }
  treenode temp = tree->children->next;
  while(temp!=NULL){
      inorder(temp,fp);
      temp = temp->next;
  }
  fclose(fp);
}

int nodenum = 0;

int countNodes(treenode tree){
  if(tree == NULL) return 0;
  int i = 0;
  if(tree->children==NULL) return 1;
  treenode temp = tree->children;
  while(temp!=NULL){
    i+=countNodes(temp);
    temp = temp->next;
  }
  return i+1;
}