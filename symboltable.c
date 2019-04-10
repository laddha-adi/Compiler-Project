#include "symboltable.h"

int offset = 0;
int size = 10000;

symbolTable create(){
	symbolTable st = (symbolTable)malloc(sizeof(struct symbolTable*)*size);
	int i = 0;
	while(i<size){
		st[i]=NULL;
		i++;
	}
	return st;
}

recordTable createRT(){
	recordTable st = (recordTable)malloc(sizeof(record)*size);
	int i = 0;
	while(i<size){
		st[i]=NULL;
		i++;
	}
	return st;
}

/*recordTable insertToRT(recordTable rt, treenode){

}
*/
int hash(char *str){
	unsigned long int hashvalue = 6669;
	int i = 0;
	while(hashvalue < ULONG_MAX && i < strlen(str)){
		hashvalue  =  str[i] + 71 * hashvalue;
		i++;
	}
	return hashvalue % size;
}

symbolTable insert(char* scope, variable var, int typelist, symbolTable stable){//typelist = 0,1,2:input,output,local{}
	//char* scope = (char*)maloc(sizeof(char)*50);
	int index = hash(scope);
	if(	stable[index]==NULL){

		stable[index] = (struct symbolTable*)malloc(sizeof(struct symbolTable));
		stable[index]->scope = (char*)malloc(sizeof(char)*50);
		strcpy(stable[index]->scope,scope);
	}
	else{ //check if function already present in stable
		struct symbolTable* t = stable[index];
		int flag=0;
		while(t!=NULL){
			if(!strcmp(t->scope,scope)){//scope already present
				if(typelist==0){
					stable[index]->inputpars= insertAtEnd(stable[index]->inputpars,var);
				}
				else if(typelist==1){
					stable[index]->outputpars= insertAtEnd(stable[index]->outputpars,var);
				}
				else {
					stable[index]->localvars= insertAtEnd(stable[index]->localvars,var);
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
			t->next=(struct symbolTable*)malloc(sizeof(struct symbolTable));
			t->next->scope = (char*)malloc(sizeof(char)*50);
			strcpy(t->next->scope,scope);

		}
	}

	if(typelist==0){
		stable[index]->inputpars= insertAtEnd(stable[index]->inputpars,var);
	}
	else if(typelist==1){
		stable[index]->outputpars= insertAtEnd(stable[index]->outputpars,var);
	}
	else {
		stable[index]->localvars= insertAtEnd(stable[index]->localvars,var);
	}

	return stable;
}

variable lookupSTable(variable var, char*scope, symbolTable stable, variable globalVarList){
	int index=hash(scope);
	
	if(	stable[index]==NULL){
		return NULL;
	}
	int a,b,c,d;
	int flag = 0;
	struct symbolTable* t = stable[index];
	while(t!=NULL){
		if(strcmp(t->scope,scope)==0){
			a = searchInList(var,t->inputpars);
			b = searchInList(var,t->outputpars);
			c = searchInList(var,t->localvars);
			
			break;
		}
		t = t->next;
	}
	//struct symbolTable* global = stable[hash("global")];
	//d = searchInList(var,global->localvars); // all vars in global to be stored in localvars
	d = searchInGlobalList(globalVarList, var->lexeme);
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

variable createVar(treenode declaration, char* scope){
	variable temp = (variable)malloc(sizeof(struct variable));
	temp -> lexeme = (char*)malloc(sizeof(char)*50); 
	strcpy(temp->lexeme,declaration -> lexeme);
	temp->next = NULL;
	//temp->type = (char*)malloc(sizeof(char)*20);
	temp->type = declaration->children->id;
	temp->scope = (char*)malloc(sizeof(char)*30); 
	temp->scope = scope;
		if(temp->type == 22) {
			temp->width = 2;
			temp->offset = offset;
			offset = offset+ temp->width;
		}else if(temp->type == 23){
			temp->width = 4;
			temp->offset = offset;
			offset = offset+ temp->width;
		}
	temp->lineno = declaration->line;
	return temp;
}

variable addToGlobalList(variable list, treenode declaration ){
	printf("Adding : %s to global list\n", declaration->children->next->lexeme);
	variable newVar = createVar(declaration, "global");
	if(list==NULL) return newVar; 
	variable temp = list;
	while(temp->next!=NULL){
		temp = temp->next;
	}
	temp->next = newVar;
	return list;
}

int searchInGlobalList(variable list, char* lex){
			//printf("Entry\n");

	variable temp = list;
	while(temp!=NULL){
		if(temp->lexeme !=NULL && lex!=NULL && strcmp(temp->lexeme,lex)==0) return 1;
		temp = temp->next;
	}
			//printf("Exit\n");

	return 0;
}


void findAndInsertGVariables(variable globalVarList, treenode root){
	//t : declaration ==>  TK_INT, TK_ID, global_or_not.
	//OR , 			  ==>  TK_REAL, TK_ID, global_or_not



	treenode functions = root->children;
	treenode stmt, declarations;
	while(functions!=NULL){
		if(functions->next!=NULL){
			stmt = functions->children->next->next->next;
		}
		else{
			stmt = functions->children; 
		}
		declarations = stmt->children->next;
		if(declarations->children==NULL) return;
		treenode declaration = declarations->children;

		while(declaration!=NULL){
			if(declaration->children->next->next->children != NULL){ //if child of global_or_not is not NULL
				if(searchInGlobalList(globalVarList, declaration->children->next->lexeme)==1){
					printf("ERROR: Global Var %s already declared\n", declaration->children->next->lexeme);
				}
				else
					globalVarList = addToGlobalList(globalVarList, declaration);
			}
			declaration = declaration -> next;
		}
		functions = functions->next;
	}
}

recordField createRecordField(treenode fieldDef){
	recordField newField = (recordField) malloc(sizeof(struct recordfields));
	newField->type = fieldDef->children->id; 
	newField->lexeme = (char*) malloc(sizeof(char)*30);
	strcpy(newField->lexeme,fieldDef->children-> next->lexeme);
	if(newField->type == 22) {
		newField->width = 2;
	}else if(newField->type == 23){
		newField->width = 4;
	}
	newField->next = NULL; 
}

recordVar createRecordVar(treenode typeDef, recordVar recordList){
	recordVar newVar = (recordVar)malloc(sizeof(struct record));
	newVar->rname = (char*) malloc(sizeof(char)*30);
	newVar->width = 0;
	newVar->head = NULL; 
	newVar->lineno = typeDef-> children->line;
	strcpy(newVar->rname,typeDef->children-> lexeme);
	newVar->next = NULL;

	treenode fieldDef = typeDef->children->next->children;
	recordField newField = createRecordField(fieldDef);
	newVar->width += newField->width;
	newVar -> head = newField;
	recordField temp = newVar->head;
	while(fieldDef!=NULL){
		temp->next = createRecordField(fieldDef);
		temp = temp->next;
		newField->width += temp->width;
		fieldDef = fieldDef->next;
	}
	return newVar;
}

recordVar addToRecordList(recordVar list, treenode declaration ){
	printf("Adding : %s to Record list\n", declaration->children->next->lexeme);
	variable newVar = createVar(declaration, "global");
	if(list==NULL) return newVar; 
	variable temp = list;
	while(temp->next!=NULL){
		temp = temp->next;
	}
	temp->next = newVar;
	return list;
}

int searchInRecordList(recordVar list, char* lex){
			//printf("Entry\n");

	recordVar temp = list;
	while(temp!=NULL){
		if(temp->rname !=NULL && lex!=NULL && strcmp(temp->rname,lex)==0) return 1;
		temp = temp->next;
	}
			//printf("Exit\n");

	return 0;
}















































