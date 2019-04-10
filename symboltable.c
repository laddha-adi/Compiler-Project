#include "symboltable.h"

int size;
/*
symboltable create(){
	symboltable st = (symboltable)malloc(sizeof(struct symboltable*)*size);
	int i = 0;
	while(i<size){
		st[i]=NULL;
		i++;
	}
	return st;
}

int hash(char *str){
	unsigned long int hashvalue = 6669;
	int i = 0;
	while(hashvalue < ULONG_MAX && i < strlen(str)){
		hashvalue  =  str[i] + 71 * hashvalue;
		i++;
	}
	return hashvalue % size;
}

symboltable insert(char* scope, variable var, int typeList, symboltable stable){//typelist = 0,1,2:input,output,local{}
	//char* scope = (char*)maloc(sizeof(char)*50);
	int index = hash(scope);
	if(	stable[index]==NULL){

		stable[index] = (struct symboltable*)malloc(sizeof(struct symboltable));
		stable[index]->scope = (char*)malloc(sizeof(char)*50);
		strcpy(stable[index]->scope,scope);
	}
	else{ //check if function already present in stable
		struct symboltable* t = stable[index];
		int flag=0;
		while(t!=NULL){
			if(!strcmp(t->scope,scope)){//scope already present
				if(typelist==0){
					stable[index]->inputpars= insertAtEnd(stable[index]->inputpars,variable);
				}
				else if(typelist==1){
					stable[index]->outputpars= insertAtEnd(stable[index]->outputpars,variable);
				}
				else {
					stable[index]->localvars= insertAtEnd(stable[index]->localvars,variable);
				}
				flag=1;
				return stable;

			}
			else
				t=t->next;
		
		}
		if(!flag){
			while(t->next!=NULL)
				t=t->next;
			t->next=(struct symboltable*)malloc(sizeof(struct symboltable));
			t->next->scope = (char*)malloc(sizeof(char)*50);
			strcpy(t->next->scope,scope);

		}
	}

	if(typelist==0){
		stable[index]->inputpars= insertAtEnd(stable[index]->inputpars,variable);
	}
	else if(typelist==1){
		stable[index]->outputpars= insertAtEnd(stable[index]->outputpars,variable);
	}
	else {
		stable[index]->localvars= insertAtEnd(stable[index]->localvars,variable);
	}

	return stable;
}

variable lookup(variable var, char*scope, symboltable stable){
	int index=hash(scope);
	
	if(	stable[index]==NULL){
		return 1;
	}
	int a,b,c,d;
	int flag = 0;
	struct symboltable* t = stable[index];
	while(t!=NULL){
		if(strcmp(t->scope,scope)==0){
			a = searchInList(var,t->inputpars);
			b = searchInList(var,t->outputpars)
			c = searchInList(var,t->localvars);
			
			break;
		}
		t = t->next;
	}
	struct symboltable* global = stable[hash("global")];
	d = searchInList(var,global->localvars); // all vars in global to be stored in localvars
	if(a||b||c||d==1)
		return var;
	else{
		return NULL;
	}

}



variable insertAtEnd(variable list,variable var){

	if(list == NULL)
			list = var;
		else{
			variable temp = list;
			while(temp->next!=NULL)
				temp = temp->next;
			temp->next = var;
		}

		var->next = NULL;
	return list;
}

int searchInList(variable var, variable list){
	while(list!=NULL){
		if(strcmp(var->lexeme,list->lexeme)==0)
			return 1;
		list = list->next;
	}
	return 0;
}

*/


variable createVar(treenode declaration){
	variable temp = (variable)malloc(sizeof(struct variable));
	temp -> lexeme = declaration -> lexeme;
	return temp;
}

variable addToGlobalList(variable list, treenode declaration ){
	printf("Adding : %s to global list", declaration->children->next->lexeme);
	variable newVar = createVar(declaration);
	if(list==NULL) return newVar; 
	variable temp = list;
	while(temp->next!=NULL){
		temp = temp->next;
	}
	temp->next = newVar;
	return list;
}

int searchInGlobalList(variable list, char* lex){
	variable temp = list;
	while(temp!=NULL){
		if(strcmp(temp->lexeme,lex)==0) return 1;
	}
	return 0;
}


void findAndInsertGVariables(variable globalVarList, treenode root){
	//t : declaration ==>  TK_INT, TK_ID, global_or_not.
	//OR , 			  ==>  TK_REAL, TK_ID, global_or_not

	//FROM Main: 
	treenode declarations = root->children->next->children->children->next;
	treenode declaration = declarations->children;
	printTree(declaration);
	while(declaration!=NULL){
		if(declaration->children->next->next->children != NULL){ //if child of global_or_not is not NULL
			if(searchInGlobalList(globalVarList, declaration->children->next->lexeme)==1){
				printf("ERROR: Global Var %s already declared\n", declaration->children->next->lexeme);
			}
			//if(typeCheckVar(declaration)==1){ 
				globalVarList = addToGlobalList(globalVarList, declaration);
		//	}
		}
		declaration = declaration -> next;
	}

}


