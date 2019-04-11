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

/*recordTable createRT(){
	recordTable st = (recordTable)malloc(sizeof(record)*size);
	int i = 0;
	while(i<size){
		st[i]=NULL;
		i++;
	}
	return st;
}
*/
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

recordVar findRecord(recordVar list, char* lex){
//printf("Entry\n");
	recordVar temp = list;
	while(temp!=NULL){
		if(temp->rname !=NULL && lex!=NULL && strcmp(temp->rname,lex)==0) {
			//printf("Exit\n");
return temp;}
		temp = temp->next;
	}
//printf("Exit\n");

	return NULL;
}

variable createVar(treenode declaration, char* scope){
	variable temp = (variable)malloc(sizeof(struct variable));
	temp -> lexeme = (char*)malloc(sizeof(char)*50); 
	strcpy(temp->lexeme,declaration ->children -> next-> lexeme);
	temp->next = NULL;
	temp->recordName = NULL;
	//temp->type = (char*)malloc(sizeof(char)*20);
	if(declaration->children->lexeme[0]=='#'){
		temp->type = 8;
	}else {
		temp->type = declaration->children->id;
	}
	if(temp->type==8){
		temp -> recordName = (char*)malloc(sizeof(char)*50); 
		strcpy(temp->recordName,declaration->children->lexeme);
	}
	temp->scope = (char*)malloc(sizeof(char)*30); 
	strcpy(temp->scope,scope);
		if(temp->type == 22) {
			temp->width = 2;
			temp->offset = offset;
			offset = offset+ temp->width;
		}else if(temp->type == 23){
			temp->width = 4;
			temp->offset = offset;
			offset = offset+ temp->width;
		}
		else{

			/*
			recordVar this_record_type = findRecord(list,temp->recordName);
			temp->width = this_record_type->width;
			temp->offset = offset;
			offset+=temp->width;*/
		}
	temp->lineno = declaration->line;
	//printf("Creating %s variable of type %d\n", temp->lexeme, temp->type);
	return temp;
}
/*

variable createRecVar(treenode declaration, char* scope, recordVar list){
	variable temp = (variable)malloc(sizeof(struct variable));
	temp -> lexeme = (char*)malloc(sizeof(char)*50); 
	strcpy(temp->lexeme,declaration ->children -> next-> lexeme);
	temp->next = NULL;
	//temp->type = (char*)malloc(sizeof(char)*20);
	temp->type = declaration->children->id;
	if(temp->type==8){
		temp -> recordName = (char*)malloc(sizeof(char)*50); 
		strcpy(temp->recordName,declaration ->children-> lexeme);
	}
	temp->scope = (char*)malloc(sizeof(char)*30); 
	strcpy(temp->scope,scope);
		if(temp->type == 22) {
			temp->width = 2;
			temp->offset = offset;
			offset = offset+ temp->width;
		}else if(temp->type == 23){
			temp->width = 4;
			temp->offset = offset;
			offset = offset+ temp->width;
		}
		else{
			recordVar this_record_type = findRecord(list,temp->recordName);
			temp->width = this_record_type->width;
			temp->offset = offset;
			offset+=temp->width;
		}
	temp->lineno = declaration->line;

	return temp;
}
*/

variable createParVar(treenode type, treenode TK_ID, char* scope, recordVar list){
	variable temp = (variable)malloc(sizeof(struct variable));
	temp -> lexeme = (char*)malloc(sizeof(char)*50); 
	strcpy(temp->lexeme,TK_ID-> lexeme);
	temp->next = NULL;
	//temp->type = (char*)malloc(sizeof(char)*20);
	temp->type = type->id;

	if(type->lexeme[0] == '#'){
		temp -> recordName = (char*)malloc(sizeof(char)*50); 
		strcpy(temp->recordName,type-> lexeme);
	}
	temp->scope = (char*)malloc(sizeof(char)*30); 
	strcpy(temp->scope,scope);

		if(temp->type == 22) {
			temp->width = 2;
			temp->offset = offset;
			offset = offset+ temp->width;
		}else if(temp->type == 23){
			temp->width = 4;
			temp->offset = offset;
			offset = offset+ temp->width;
		}
		else{
			recordVar this_record_type = findRecord(list,temp->recordName);
			temp->width = this_record_type->width;
			temp->offset = offset;
			offset+=temp->width;
		}
	temp->lineno = -1;
	return temp;
}


variable addToGlobalList(variable list, treenode declaration, char* scope ){
	//printf("Adding : %s to %s list\n", declaration->children->next->lexeme, scope);
	variable newVar = createVar(declaration, scope);
	if(list==NULL) return newVar; 
	variable temp = list;
	while(temp->next!=NULL){
		temp = temp->next;
	}
	temp->next = newVar;
	return list;
}

variable addToVariableList(variable list, variable v){
	//printf("Adding : %s to variable list\n", v->lexeme);
	variable head = list;
	if(list==NULL){ 
		list = v;
		return list;
	}
	variable temp = list;
	while(temp->next!=NULL){
		temp = temp->next;
	}
	temp->next = v;
	return head;
}


int searchInGlobalList(variable list, char* lex){
	variable temp = list;
	while(temp!=NULL){
		if(temp->lexeme !=NULL && lex!=NULL && strcmp(temp->lexeme,lex)==0) return 1;
		temp = temp->next;
	}

	return 0;
}

variable findAndInsertGVariables(variable globalVarList, treenode root, recordVar globalRecordDefList){
	//t : declaration ==>  TK_INT, TK_ID, global_or_not.
	//OR , 			  ==>  TK_REAL, TK_ID, global_or_not

	treenode functions = root->children;
	treenode stmt, declarations;

	while(functions!=NULL){
		if(functions->children==NULL)
			{functions=functions->next;
			continue;}
		if(functions->next!=NULL && functions->children!=NULL){
			//Function is otherFunctions here.

			stmt = functions->children->next->next->next;
		}
		else{

			//Function is main here.
			stmt = functions->children; 
		}
		declarations = stmt->children->next;
		if(declarations->children==NULL) 
			{	functions=functions->next;
				continue;}
		treenode declaration = declarations->children;

		while(declaration!=NULL){
			if(declaration->children->id == 22 || declaration->children->id == 23){
				//Var is of type int or real.
				if(declaration->children->next->next->children != NULL){ //if child of global_or_not is not NULL
					if(searchInGlobalList(globalVarList, declaration->children->next->lexeme)==1){
						printf("ERROR: Global Var %s already declared\n", declaration->children->next->lexeme);
					}
					else
						globalVarList = addToGlobalList(globalVarList, declaration, "global");
				}
			}
			else if(declaration->children->id == 8){
				//var is of type record.
				if(searchInRecordList(globalRecordDefList, declaration->children->lexeme)==1){
					if(declaration->children->next->next->children != NULL){ //if child of global_or_not is not NULL
						if(searchInGlobalList(globalVarList, declaration->children->next->lexeme)==1){
							printf("ERROR: Global Var %s already declared\n", declaration->children->next->lexeme);
						}
						else
							globalVarList = addToGlobalList(globalVarList, declaration, "global");
					}
				}else{
					printf("ERROR: Record Definition of type %s not found\n", declaration->children->lexeme);
				}
			}
			declaration = declaration -> next;
		}
		functions = functions->next;
	}
	return globalVarList;
}

void findAndInsertGRecVariables(variable globalVarList, treenode root, recordVar rlist){
	//t : declaration ==>  TK_INT, TK_ID, global_or_not.
	//OR , 			  ==>  TK_REAL, TK_ID, global_or_not

	treenode functions = root->children;
	treenode stmt, declarations;

	while(functions!=NULL){
		if(functions->children==NULL)
			{functions=functions->next;
			continue;}
		if(functions->next!=NULL && functions->children!=NULL){
			//Function is otherFunctions here.

			stmt = functions->children->next->next->next;
		}
		else{

			//Function is main here.
			stmt = functions->children; 
		}
		declarations = stmt->children->next;
		if(declarations->children==NULL) {	
			functions=functions->next;
			continue;
		}
		treenode declaration = declarations->children;

		while(declaration!=NULL){
			
			if(declaration->children->next->next->children != NULL){ //if child of global_or_not is not NULL
				if(searchInGlobalList(globalVarList, declaration->children->next->lexeme)==1){
					printf("ERROR: Global Var %s already declared\n", declaration->children->next->lexeme);
				}
				else
					globalVarList = addToGlobalList(globalVarList, declaration, "global");
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
	return newField;
}

recordVar createRecordVar(treenode typeDef){
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
	fieldDef = fieldDef->next;
	while(fieldDef!=NULL){
		recordField temp;
		temp = createRecordField(fieldDef);
		temp->next = newVar->head;
		newVar->head = temp;
		newVar->width += temp->width;
		fieldDef = fieldDef->next;
	}
	return newVar;
}

recordVar addToRecordList(recordVar list, treenode typeDefs){
	treenode typeDef = typeDefs->children;
	recordVar head = list;

	while(typeDef!=NULL){
		if(searchInRecordList(list, typeDef->children->lexeme)==1){
			printf("ERROR: Record Def %s already declared\n", typeDef->children->lexeme);
			return list;
		}
		else{
			recordVar newVar = createRecordVar(typeDef);
			printf("Adding : %s to Record list\n", typeDef->children->lexeme);	
			recordVar temp = head;
			if(temp==NULL)
				head = newVar;
			else {
				while(temp->next!=NULL){
					temp = temp->next;
				}
				temp->next = newVar;
			}
		}
		typeDef = typeDef->next;
	}
	return head;
}

int searchInRecordList(recordVar list, char* lex){
	recordVar temp = list;
	while(temp!=NULL){
		if(temp->rname !=NULL && lex!=NULL && strcmp(temp->rname,lex)==0) {
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}


recordVar findAndInsertRecordDefs(recordVar globalRecordDefList, treenode root, recordVar head){
	//t : declaration ==>  TK_INT, TK_ID, global_or_not.
	//OR , 			  ==>  TK_REAL, TK_ID, global_or_not

	treenode functions = root->children;
	treenode stmt, typeDefs;
	while(functions!=NULL){
		if(functions->children==NULL)
			{functions=functions->next;
			continue;}
		if(functions->next!=NULL){
			stmt = functions->children->next->next->next;
		}
		else{
			stmt = functions->children; 
		}
		
		typeDefs = stmt->children;		
		globalRecordDefList = addToRecordList(globalRecordDefList,typeDefs);
		head = globalRecordDefList;

		functions = functions->next;
	}
	return head;
}

symbolTableElement createFunction(treenode function, symbolTable stable, variable globalVarList, recordVar recordDefList){
	//printf("Creating Function %s\n", function->children->lexeme);
	offset = 0;
	symbolTableElement newFunction = (symbolTableElement) malloc(sizeof(struct symbolTable));
	newFunction->scope = (char*) malloc(sizeof(char)*30);
	strcpy(newFunction->scope, function->children->lexeme);

	newFunction->inputpars = NULL;

	//Adding input vars.
	treenode inputPars = function->children->next;
	//printTree(inputPars);
	treenode parameterList = inputPars->children;
	while(parameterList!=NULL){
		//printf("a\n");
		if(searchInGlobalList(newFunction->inputpars,parameterList->children->next->lexeme)==0 && searchInGlobalList(globalVarList,parameterList->children->next->lexeme)==0) {
			variable tempVar;
			if(parameterList->children->next->next !=NULL)
				//Record variable
				tempVar = createParVar(parameterList->children, parameterList->children->next ,newFunction->scope, recordDefList);
			else 
				//INT or REAL Variable
				tempVar = createParVar(parameterList->children, parameterList->children->next,newFunction->scope, recordDefList);

			newFunction->inputpars = addToVariableList(newFunction->inputpars,tempVar);
			//printVarList(newFunction->inputpars);
		}else{
			printf("ERROR: Variable %s already declared\n", parameterList->children->next->lexeme);
		}
		parameterList = parameterList->next;	
	}


	newFunction->outputpars = NULL;

	//Adding input vars.
	treenode outputPars = function->children->next->next;
	//printTree(inputPars);
	parameterList = outputPars->children;
	while(parameterList!=NULL){
		if(searchInGlobalList(newFunction->outputpars,parameterList->children->next->lexeme)==0 && searchInGlobalList(newFunction->inputpars,parameterList->children->next->lexeme)==0 && searchInGlobalList(globalVarList,parameterList->children->next->lexeme)==0) {
			variable tempVar;
			if(parameterList->children->next->next !=NULL)
				//Record variable
				tempVar = createParVar(parameterList->children, parameterList->children->next, newFunction->scope, recordDefList);
			else 
				//INT or REAL Variable
				tempVar = createParVar(parameterList->children, parameterList->children->next,newFunction->scope, recordDefList);

			newFunction->outputpars = addToVariableList(newFunction->outputpars,tempVar);
		}else{
			printf("ERROR: Variable %s already declared\n", parameterList->children->next->lexeme);
		}
		parameterList = parameterList->next;	
	}


	treenode stmt = function->children->next->next->next;
	treenode declarations = stmt->children->next;
	treenode declaration = declarations->children;

	while(declaration!=NULL){
		if(declaration->children->id == 22 || declaration->children->id == 23 || declaration->children->lexeme[0]=='#' ){
			//Var is of type int or real.
			if(declaration->children->next->next->children == NULL){ //if child of global_or_not is not NULL
				if(searchInGlobalList(globalVarList, declaration->children->next->lexeme)==1 
					|| searchInGlobalList(newFunction->outputpars, declaration->children->next->lexeme)==1
					|| searchInGlobalList(newFunction->inputpars, declaration->children->next->lexeme)==1 
					|| searchInGlobalList(newFunction->localvars, declaration->children->next->lexeme)==1  
					){
					printf("ERROR: Local Var %s already declared\n", declaration->children->next->lexeme);
				}
				else{
					newFunction->localvars = addToGlobalList(newFunction->localvars, declaration, newFunction->scope);
				}
			}
		}

		declaration = declaration -> next;
	}	
	newFunction->next = NULL;
	return newFunction;

}



symbolTableElement createMainFunction(treenode function, symbolTable stable, variable globalVarList, recordVar recordDefList){
	//printf("Creating Function main\n");
	offset = 0;
	symbolTableElement newFunction = (symbolTableElement) malloc(sizeof(struct symbolTable));
	newFunction->scope = (char*) malloc(sizeof(char)*30);
	strcpy(newFunction->scope, "main");

	newFunction->inputpars = NULL;
	newFunction->outputpars = NULL;

	treenode stmt = function->children;
	treenode declarations = stmt->children->next;
	treenode declaration = declarations->children;

	while(declaration!=NULL){
		if(declaration->children->id == 22 || declaration->children->id == 23 || declaration->children->lexeme[0]=='#' ){
			if(declaration->children->next->next->children == NULL){ //if child of global_or_not is not NULL
				if(searchInGlobalList(globalVarList, declaration->children->next->lexeme)==1 
					|| searchInGlobalList(newFunction->outputpars, declaration->children->next->lexeme)==1
					|| searchInGlobalList(newFunction->inputpars, declaration->children->next->lexeme)==1 
					|| searchInGlobalList(newFunction->localvars, declaration->children->next->lexeme)==1  
					){
					printf("ERROR: Local Var %s already declared\n", declaration->children->next->lexeme);
				}
				else{
					newFunction->localvars = addToGlobalList(newFunction->localvars, declaration, newFunction->scope);
				}
			}
		}

		declaration = declaration -> next;
	}	
	newFunction->next = NULL;
	return newFunction;

}


int SNUM =0;
symbolTable addInSTable(symbolTable stable, symbolTableElement sElement){
	stable[SNUM++] = sElement;
	return stable;
}

symbolTableElement findInSTable(symbolTable stable, char* fname){
	int i=0;
	for(i=0;i<SNUM; i++){
		if(stable[i]!=NULL && strcmp(stable[i]-> scope, fname) == 0){
			return stable[i];
		}
	}
	return NULL;
}



symbolTable addFunctions(treenode root, variable globalVarList, recordVar recordDefList){
	symbolTable stable = (symbolTable)malloc(sizeof(struct symbolTable*) * 100);

	treenode function = root->children;
	while(function->next!=NULL){
		if(findInSTable(stable, function->children->lexeme)==NULL){
			symbolTableElement fun = createFunction(function,stable, globalVarList, recordDefList);
			stable = addInSTable(stable, fun);
		}else{
			printf("ERROR: Function with name %s already defined\n", function->children->lexeme);
		}
		function = function->next;
	}

	if(findInSTable(stable, "main")==NULL){
		symbolTableElement fun = createMainFunction(function,stable, globalVarList, recordDefList);
		stable = addInSTable(stable, fun);
	}
	else{
		printf("ERROR: Function with name %s already defined\n", function->children->lexeme);
	}

	return stable;
}

void printVarList(variable head){
	while(head!=NULL){
		printf("%s,\t width: %d\t offset: %d\n",head->lexeme, head->width, head->offset);
		head = head->next;
	}
	printf("\n");
}

void printRecordDefList(recordVar head){
	while(head!=NULL){
		if(head!=NULL && head->rname !=NULL){
			printf("%s,",head->rname);
			recordField temp;

		}
		head = head->next;
	}
	printf("\n");
}

void printSymbolElement(symbolTableElement sElement ){

	printf("=======================================\n");
	printf("scope = %s\n", sElement->scope); 
	printf("Input Pars : \n");
	printVarList(sElement->inputpars);
	printf("Output Pars : \n");
	printVarList(sElement->outputpars);
	printf("Variables : \n");
	printVarList(sElement->localvars);
	printf("=======================================\n");
}

void printSymbolTable(symbolTable stable){
	int i=0;
	printf("Printing Symbol table\n");
	for(i=0;i<SNUM; i++){
		if(stable[i]!=NULL){
			printSymbolElement(stable[i]);
		}
	}
}

void addListOffset(variable head, recordVar recordDefList){
	recordDefList = recordDefList->next;

	while(head!=NULL){
		if(head!=NULL && head->recordName!=NULL && head->type==8){
			recordVar temp = findRecord(recordDefList,head->recordName);
			head->width = temp->width;
			head->offset = offset;
			offset += head->width;		

		}
		else{
			head->offset = offset;
			offset += head-> width;
 		}
		head = head->next;
	}
}


void addOffset(symbolTable stable, recordVar recordDefList){
	int i=0;
	for(i=0;i<SNUM; i++){
		offset = 0;
		if(stable[i]!=NULL){
			symbolTableElement sElement = stable[i];
			if(sElement!=NULL){
			addListOffset(sElement->inputpars, recordDefList);
			addListOffset(sElement->outputpars, recordDefList);
			addListOffset(sElement->localvars, recordDefList);
		}else printf("here1\n");
		}else printf("here2\n");

	}
}











































