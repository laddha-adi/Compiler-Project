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

int stack_size = 10000;


stack createStack(){
    stack s = (stack) malloc(sizeof(struct Stack));
    s->arr = (int*) malloc(sizeof(int)*stack_size);
    s->top = -1;
    return s;
}

void push(stack s, int rule_no){
    s->top++;
    if(s->top==stack_size) printf("Stack size reached\n");
    s->arr[s->top] = rule_no;
}

int getTop(stack s){
    return s->arr[s->top];
}


int pop(stack s){
    int d = s->arr[s->top];
    s->top--;
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

treenode parseInputSourceCode(char* testCasefile, table pTable, node* gRules){
    FILE* fp=fopen(testCasefile,"r");
    if (fp==NULL) 
        {
            fputs ("File error",stderr);
            exit (1);
        }

    int bsize=30;
    char *buffer=(char*)malloc(bsize*sizeof(char));
    tokenInfo token;
    token=getNextToken(fp,buffer,bsize);
    int ip = token.tokenId;

    stack s = createStack();
    push(s, 54);
    push(s, 0);

    treenode t_head = createTreeNode("program",0);
    treenode t_ptr = t_head;

    int X = getTop(s); 
    
    while(X!=54){  // (X != $ )
        if(X==ip) {
            int t = pop(s);
            ip = getNextToken(fp,buffer,bsize).tokenId;
            
            //Go to parent ya right
            while(t_ptr->next == NULL){
                if(t_ptr==t_head){
                    return t_head;
                }
                t_ptr = t_ptr -> parent;
            }
            t_ptr = t_ptr -> next;
        }

        else if(isTerminal(X)){
            error(X, ip);
            // moove tree pointer right or up.
        }
        else if(pTable[X][ip] == -1){
            //Error
            error(X, ip);
        }
        else if(pTable[X][ip] == -2){
            //Sync
            sync(X,ip);
        }
        else {
            int rule_id = pTable[X][ip]-1;
            node rule = gRules[rule_id];
            //Insert Rule in parse Tree.
            rule = rule -> next;
            if(strcmp(rule->string,"eps")!=0){

                 t_ptr = addChildrenRule(t_ptr,rule);
                //pop the stack.
                pop(s);

                stack temp_stack = createStack(); 
                //push in dummy stack;
                node temp = rule;
                while(temp!=NULL){
                    int temp_id = getId(temp->string);
                    push(temp_stack, temp_id);
                }
                while(!isEmpty(temp_stack)){
                    push(s, pop(temp_stack));
                }
            }

            else{
                //handle eps.
                pop(s);
            }

        }
        X = getTop(s);
    }

    error(X,ip);
    return t_head;
}




void error(int X, int ip){
    printf("X : %d ip: %d", X, ip);
}

void sync(int X, int ip){
    printf("X : %d ip: %d", X, ip);
}


/*
void printParseTree(table pTable,char* outFile){
    
}*/

int isTerminal(int X){

    //add if (X is a terminal ) return 1; stmt.

    return 0;
}

void addChild(treenode pNode, treenode cNode){
    treenode temp = pNode->children;
    cNode->parent = pNode;
    if(temp==NULL) {
        pNode->children = cNode;
        return;
    }
    while(temp->next != NULL) temp = temp->next;
    temp->next = cNode;
    cNode->prev = temp;
}

treenode  addChildrenRule(treenode parent, node gListHead){
    node temp = gListHead;
    int a = 1;
    treenode ret_node;
    while(temp!=NULL){
        a--;
        int id = getId(temp->string);
        treenode t_node = createTreeNode(temp->string,id);
        if(a==0) ret_node = t_node;
        addChild(parent,t_node);
        temp = temp->next;
    }
    printf("Add Child Error\n");
    return ret_node;
}

int getId(char* str){
	return 0;
}

int main(){
    hashtable ht=createHashTable();
    node * grules = readGrammar("Grammar.txt",ht);
   // treenode t = parseInputSourceCode("Testcases/testcase1.txt", pTable,grules);
    return 0;
}

void LexerMain(){
    FILE* fp=fopen("Testcases/testcase1.txt","r");
    if (fp==NULL) 
        {
            fputs ("File error",stderr);
            exit (1);
        }
    
    int bsize=30;
    char *buffer=(char*)malloc(bsize*sizeof(char));
    tokenInfo token;
    token=getNextToken(fp,buffer,bsize);

    while(token.tokenId!=54){
        printf("token %d %d %s \n",token.tokenId,token.line,token.value);
        token=getNextToken(fp,buffer,bsize);
    }

}
