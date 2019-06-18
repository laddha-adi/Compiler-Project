/*
GROUP NUMBER: 11
NIKKI GUPTA 2016A7PS0057P
SAHIL RANADIVE 2016A7PS0097P
ADITI AGARWAL 2016A7PS0095P
ADITYA LADDHA 2016A7PS0038P
*/



#include "symboltable.h"

int offset = 0;

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


variable searchInListStr(variable list, char* lexeme){

	while(list!=NULL){
		if(strcmp(list->lexeme,lexeme)==0)
			return list;
		list = list->next;
	}

	return NULL;
}

recordVar findRecord(recordVar list, char* lex){
	recordVar temp = list;
	while(temp!=NULL){
		if(temp->rname !=NULL && lex!=NULL && strcmp(temp->rname,lex)==0) {
			return temp;
		}
		temp = temp->next;
	}
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
			temp -> recordName = (char*)malloc(sizeof(char)*50); 
			strcpy(temp->recordName,"int");
		}else if(temp->type == 23){
			temp->width = 4;
			temp->offset = offset;
			offset = offset+ temp->width;
			temp -> recordName = (char*)malloc(sizeof(char)*50); 
			strcpy(temp->recordName,"real");
		}
		else{

		}
	temp->lineno = declaration->line;
	//printf("Creating %s variable of type %d\n", temp->lexeme, temp->type);
	return temp;
}


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
			//printf("yahan..\n");
			recordVar this_record_type = findRecord(list,temp->recordName);
			//			printf("yahan..2\n");

			if(this_record_type!=NULL){
			//				printf("yahan..3\n");

				temp->width = this_record_type->width;
				temp->offset = offset;
				offset+=temp->width;
			}else{
				printf("Line : %d ERROR: Variable %s is not declared\n", temp->lineno ,temp->recordName);
				return NULL;
			}
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
	//newVar->recordName =  
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

variable findAndInsertGVariables( treenode root, recordVar globalRecordDefList){
	//t : declaration ==>  TK_INT, TK_ID, global_or_not.
	//OR , 			  ==>  TK_REAL, TK_ID, global_or_not
	variable globalVarList=NULL;
	treenode functions = root->children;
	treenode stmt, declarations;
	stmt = NULL;
	declarations = NULL;

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
						printf("Line : %d ERROR: Global Variable %s cannot be declared again.\n", declaration->children->next->line,declaration->children->next->lexeme);
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
							printf("Line : %d ERROR: Global Variable %s cannot be declared again.\n", declaration->children->next->line,declaration->children->next->lexeme);
						}
						else
							globalVarList = addToGlobalList(globalVarList, declaration, "global");
					}
				}else{
					printf("Line : %d ERROR: Record Definition of type %s not found\n", declaration->children->line,declaration->children->lexeme);
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
					printf("Line : %d ERROR: Global Variable %s already declared\n",declaration->children->next->line ,declaration->children->next->lexeme);
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
	//printTree(typeDefs);
	recordVar head = list;

	while(typeDef!=NULL){
		
		if(searchInRecordList(list, typeDef->children->lexeme)==1){
			printf("Line : %d ERROR: Record Def %s already declared\n", typeDef->children->line ,typeDef->children->lexeme);
			typeDef = typeDef->next;
			continue;
		}
		else{
			recordVar newVar = createRecordVar(typeDef);
			recordVar temp = head;
			if(temp==NULL){
				head = newVar;
			}
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


recordVar findAndInsertRecordDefs(treenode root){
	//t : declaration ==>  TK_INT, TK_ID, global_or_not.
	//OR , 			  ==>  TK_REAL, TK_ID, global_or_not
	//printf("Entry\n");
	recordVar head = NULL;
	treenode functions = root->children;
	treenode stmt, typeDefs;
	while(functions!=NULL){
		if(functions->children==NULL){
				functions=functions->next;
			continue;}
		if(functions->next!=NULL){
			stmt = functions->children->next->next->next;
		}
		else{
			stmt = functions->children; 
		}
		
		typeDefs = stmt->children;	
		head = addToRecordList(head,typeDefs);
		functions = functions->next;
	}
	return head;
}

symbolTableElement createFunction(treenode function, symbolTable stable, variable globalVarList, recordVar recordDefList){
	//printf("Creating Function %s\n", function->children->lexeme);
	offset = 0;
	symbolTableElement newFunction = (symbolTableElement) malloc(sizeof(struct symbolTable));
	if(newFunction==NULL){
		printf("memory not given...breaking\n");
		exit(0);
	}
	newFunction->scope = (char*) malloc(sizeof(char)*30);
	if(newFunction->scope==NULL){
		printf("memory not given...breaking\n");
		exit(0);
	}
	strcpy(newFunction->scope, function->children->lexeme);

	newFunction->inputpars = NULL;

	//Adding input vars.
	treenode inputPars = function->children->next;
	//printTree(inputPars);

	treenode parameterList = inputPars->children;
	while(parameterList!=NULL){
		//printf("a\n");
		if(searchInGlobalList(newFunction->inputpars,parameterList->children->next->lexeme)==0 && searchInGlobalList(globalVarList,parameterList->children->next->lexeme)==0) {
			variable tempVar = NULL;
			if(parameterList->children->next->next !=NULL){
				//Record variable
				//if(isValidRecordInstance())
				tempVar = createParVar(parameterList->children, parameterList->children->next ,newFunction->scope, recordDefList);
			}
			else 
				//INT or REAL Variable
				tempVar = createParVar(parameterList->children, parameterList->children->next,newFunction->scope, recordDefList);

			newFunction->inputpars = addToVariableList(newFunction->inputpars,tempVar);
			//printVarList(newFunction->inputpars);
		}else{
			printf("Line : %d ERROR: Variable %s already declared\n", parameterList->children->next->line,parameterList->children->next->lexeme);
		}
		parameterList = parameterList->next;	
	}

	newFunction->outputpars = NULL;

	//Adding input vars.
	treenode outputPars = function->children->next->next;
	//printTree(outputPars);
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
			printf("Line : %d ERROR: Variable %s already declared\n", parameterList->children->next->line ,parameterList->children->next->lexeme);
		}
		parameterList = parameterList->next;	
	}

	newFunction -> localvars = NULL;

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
					printf("Line : %d ERROR: Variable %s already declared\n", declaration->children->next->line,declaration->children->next->lexeme);
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
	if(newFunction==NULL){
		printf("memory not given...breaking\n");
		exit(0);
	}
	newFunction->scope = (char*) malloc(sizeof(char)*30);
	if(newFunction->scope==NULL){
		printf("memory not given...breaking\n");
		exit(0);
	}
	strcpy(newFunction->scope, "main");

	newFunction->inputpars = NULL;
	newFunction->outputpars = NULL;
	newFunction->localvars  = NULL;
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
					printf("Line : %d ERROR: Variable %s already declared\n", declaration->children->next->line,declaration->children->next->lexeme);
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
	symbolTable stable = (symbolTable)malloc(sizeof(struct symbolTable*) * 20);
	if(stable==NULL){
		printf("memory not given...breaking\n");
		exit(0);
	}

	treenode function = root->children;
	if(function->children==NULL) {
		function = function->next;
	}
	while(function->next!=NULL){
 		if(findInSTable(stable, function->children->lexeme)==NULL){
 			symbolTableElement fun = createFunction(function,stable, globalVarList, recordDefList);
 			stable = addInSTable(stable, fun);
		}else{

		printf("Line : %d ERROR: Function with name %s already defined\n", function->children->line,function->children->lexeme);
		}
 		function = function->next;
	}

	if(findInSTable(stable, "main")==NULL){
		symbolTableElement fun = createMainFunction(function,stable, globalVarList, recordDefList);
		stable = addInSTable(stable, fun);
	}
	else{
		printf("Line : %d ERROR: Function with name %s already defined\n", function->children->line,function->children->lexeme);
	}
 	return stable;
}


void printVarList(variable head, recordVar list){
	while(head!=NULL){
		printf("%s\t\t",head->lexeme);
		
		if(head->type==22){
			printf("int\t\t");
		}else if(head->type==23){
			printf("real");
		}
		else{
			recordVar temp = findRecord(list, head->recordName);
			if(temp!=NULL) printRecordDef(temp);
			else printf("\t\t\t");
		}
		if(strcmp(head->scope, "main")==0) printf("_%s\t\t",head->scope);
		else printf("%s\t\t",head->scope);
		printf("%d\n",head->offset);

		head = head->next;
	}
	//printf("\n");
}

void printGlobalVarList(variable head){
	int offset = 0;
	while(head!=NULL){
		printf("Variable name: %s\t type: %s\t offset: %d\n",head->lexeme, head->recordName, offset);
		offset += head->width;
		head = head->next;
	}
	//printf("\n");
}


void printRecordDefList(recordVar head){
	while(head!=NULL){
		if(head!=NULL && head->rname !=NULL){
			printf("%s\t\t",head->rname);
			recordField temp;

		}
		recordField tempField = head->head;
		int offset = 0;
		while(tempField->next!=NULL){
			int type = tempField->type;
			if(type==22)	{printf("int,"); offset+=2;}
			if(type==23)	{printf("real,"); offset+=4;}
			tempField = tempField->next;
		}
		int type = tempField->type;
			if(type==22)	{printf("int"); offset+=2;}
			if(type==23)	{printf("real"); offset+=4;}
		head = head->next;
		printf("\t\t%d\n", offset);
	}
}


void printRecordDef(recordVar head){
	recordField tempField = head->head;
	while(tempField->next!=NULL){
		int type = tempField->type;
		if(type==22)	{printf("int x ");}
		if(type==23)	{printf("real x ");}
			tempField = tempField->next;
	}
		int type = tempField->type;
		if(type==22)	{printf("int\t");}
		if(type==23)	{printf("real\t");}	
}


void printSymbolElement(symbolTableElement sElement, recordVar list){
	printVarList(sElement->inputpars,list);
	printVarList(sElement->outputpars,list);
	printVarList(sElement->localvars, list);
}

void printSymbolTable(symbolTable stable, recordVar list){
	int i=0;
	printf("Lexeme\t\ttype\t\t\tscope\t\toffset\n");
	for(i=0;i<SNUM; i++){
		if(stable[i]!=NULL){
			printSymbolElement(stable[i], list);
		}
	}
}

void addListOffset(variable head, recordVar recordDefList){
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
			//	printf("1\n");
			addListOffset(sElement->inputpars, recordDefList);
			//printf("2\n");
			addListOffset(sElement->outputpars, recordDefList);
			//printf("3\n");
			addListOffset(sElement->localvars, recordDefList);

			sElement->offset = offset;
		}else printf("here1\n");
		}else printf("here2\n");
		
	}
}

void printFunctionOffset(symbolTable stable){
	int i=0;
	for(i=0;i<SNUM; i++){
		if(stable[i]!=NULL){
			printf("%s\t\t%d\n", stable[i]->scope, stable[i]->offset);
		}
	}
}

void cleanVars(){
	SNUM =0;
	offset = 0;
}






































