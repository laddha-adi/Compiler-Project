/*
GROUP NUMBER: 11
NIKKI GUPTA 2016A7PS0057P
SAHIL RANADIVE 2016A7PS0097P
ADITI AGARWAL 2016A7PS0095P
ADITYA LADDHA 2016A7PS0038P
*/

#include "semanticanalyzer.h"


variable checkifdeclared(char* var_name, symbolTableElement stentry, variable globalVarList){
	variable i = NULL;
		i=searchInListStr(stentry->inputpars, var_name);
		if(i==NULL){
			i=searchInListStr(stentry->outputpars, var_name);
			if(i==NULL){
				i=searchInListStr(stentry->localvars, var_name);
				if(i==NULL){
					i= searchInListStr(globalVarList, var_name);
				}	
			}
		}
	if(i==NULL){
		return NULL;
	}
	else
		return i;
}

void checkonefuncall(treenode funcallstmt, char* scope, symbolTable stable, variable globalVarList)
{
	char* fun_name= funcallstmt->children->next->lexeme;//function being called
	if(strcmp(fun_name, scope)==0)
	{
		printf("Line : %d ERROR : Function cannot be recursive \n", funcallstmt->line);
	}
	treenode outputpars=funcallstmt->children->children;
	treenode inputpars= funcallstmt->children->next->next->children;

	symbolTableElement selement =findInSTable(stable, fun_name);
	symbolTableElement selementscope =findInSTable(stable, scope);

	variable formalinput= selement->inputpars;
	variable formaloutput= selement->outputpars;

	while(outputpars!=NULL && formaloutput!=NULL) //checking output parameters list
	{
		char* var_name= outputpars->children->lexeme;
		variable var2=checkifdeclared(var_name, selementscope, globalVarList);
		if(var2==NULL)
		{
			// searchInList()
			printf("Line : %d ERROR : Variable %s not declared in function %s\n",funcallstmt->line, var_name, scope);
			outputpars=outputpars->next;
			formaloutput=formaloutput->next;
			continue;

		}
		if(var2->type!=formaloutput->type)
		{
			printf("Line : %d ERROR : Type mismatch actual output parameter: %s and formal output parameter: %s \n",funcallstmt->line, outputpars->children->lexeme, formaloutput->lexeme);
		}

		outputpars=outputpars->next;
		formaloutput=formaloutput->next;

	}

	//check if number is different
	if(outputpars!=NULL && formaloutput==NULL)
	{
		printf("Line : %d ERROR : Less number of formal output parameters for function %s\n",funcallstmt->line, fun_name);
	}
	else if(outputpars==NULL && formaloutput!=NULL)
	{
		printf("Line : %d ERROR : Insufficient actual output paramters for function %s\n",funcallstmt->line, fun_name);

	}


	while(inputpars!=NULL && formalinput!=NULL) //checking input parameters list
	{
		char* var_name= inputpars->children->lexeme;
		variable var2=checkifdeclared(var_name, selementscope, globalVarList);
		if(var2==NULL)
		{
			// searchInList()
			printf("Line : %d ERROR : Variable %s not declared in function %s\n",funcallstmt->line, var_name, scope);
			inputpars=inputpars->next;
			formalinput=formalinput->next;
			continue;

		}
		if(var2->type!=formalinput->type)
		{
			printf("Line : %d ERROR : Type mismatch actual input parameter: %s and formal output parameter: %s \n",funcallstmt->line, inputpars->children->lexeme, formalinput->lexeme);
		}

		inputpars=inputpars->next;
		formalinput=formalinput->next;

	}

	//check if number is different
	if(inputpars!=NULL && formalinput==NULL)
	{
		printf("Line : %d ERROR : Less number of formal input parameters for function %s\n",funcallstmt->line, fun_name);
	}
	else if(inputpars==NULL && formalinput!=NULL)
	{
		printf("Line :%d ERROR : Insufficient actual input paramters for function %s\n",funcallstmt->line, fun_name);

	}
}


int searchInFuncList(char** funlist, char* name, int num)
{
	for(int i=0; i<num; i++)
	{
		if(strcmp(funlist[i], name)==0)
		{
			return 1;
		}
	}
	return 0;
}


				
void checkIOstmt(treenode iostmt, char* scope, symbolTable stable,variable globalVarList,recordVar recList)
{
	if(iostmt->id==34)//read
		checkSingleorRec(iostmt->children, scope, stable, globalVarList,recList);
		else {
		if(iostmt->children->id!=5 && iostmt->children->id!=6){//If not num or rnum i.e is id or id.fieldid
			checkSingleorRec(iostmt, scope, stable, globalVarList,recList);
		}
	}	

}


void checkSingleorRec(treenode node, char* scope, symbolTable stable,variable globalVarList,recordVar recList){

	symbolTableElement stentry= findInSTable(stable, scope);

	if(node->children->next==NULL){//only id
		// printf("in if\n");
		if(stentry==NULL)
		{
			printf("1 Wrong Scope passed to function %s\n",scope);
			return;
		}
		variable i;
		i=searchInListStr(stentry->inputpars, node->children->lexeme);
		if(i==NULL){
			i=searchInListStr(stentry->outputpars, node->children->lexeme);
			if(i==NULL){
				i=searchInListStr(stentry->localvars, node->children->lexeme);
				if(i==NULL){
						i= searchInListStr(globalVarList, node->children->lexeme);
				}	
			}
		}
		// printf("lexeme %s\n",i->lexeme);
		if(i==NULL)
		{

			printf("Line : %d ERROR : Variable %s not previously declared\n",node->line, node->children->lexeme );
		}

	}

	else{// id.fieldid
		char* fieldid= node->children->next->next->lexeme;
		variable i;
		i=searchInListStr(stentry->inputpars, node->children->lexeme);
		if(i==NULL){
			i=searchInListStr(stentry->outputpars, node->children->lexeme);
			if(i==NULL){
				i=searchInListStr(stentry->localvars, node->children->lexeme);
				if(i==NULL){
						i= searchInListStr(globalVarList, node->children->lexeme);
						return;
				}	
			}
		}
		if(i==NULL){
			printf("Line : %d ERROR : Record Instance %s not previously declared\n",node->line, node->children->lexeme );
			return;
		}
		recordVar record= searchInRecList(recList, i->recordName);
		if(record==NULL)
			{printf("Line : %d ERROR : Record definition of %s  not previously declared\n", node->line, node->children->lexeme);
			return;}
		recordField recf= record->head;
		// printf("Inside condition if\n");
		while(recf!=NULL)
		{
			// printf("Inside recf while\n");
			if(strcmp(fieldid, recf->lexeme)==0)
				return;
			recf=recf->next;
		}
			printf("Line : %d ERROR : Record %s does not contain field %s\n", node->line, i->recordName, fieldid);
		return;
	}

}


void checkfuncallstmts(treenode root, symbolTable stable, variable globalVarList,recordVar recList)
{
	treenode functions = root->children;
	char* scope=(char*) malloc(sizeof(char)*50);
	char** funlist= (char**)malloc(sizeof(char *)*1000); 
	int num_func=0;
	if(functions->children==NULL)
		functions=functions->next;
	while(functions!=NULL)
	{
		treenode stmts = NULL;
		if(functions->next==NULL) //if main function 
		{
			stmts = functions->children->children->next->next; 
		}
		else{ // other functions
		stmts = functions->children->next->next->next->children->next->next;
		}

		if(functions->id==101)
			strcpy(scope,"main");
		else
			strcpy(scope,functions->children->lexeme);
		// printf("Inside function %s\n", scope);



		if(searchInFuncList(funlist, scope, num_func)!=0)//scope already exists
		{
			treenode stmt= stmts->children;
			printf("Line : %d ERROR : Function overloading not allowed for function: %s\n", stmt->line, scope);
		}
		else{
			funlist[num_func]=(char*)malloc(sizeof(char)*50);
			strcpy(funlist[num_func], scope);
			// printf("adding to funlist%s\n", funlist[num_func]);
			num_func++;
			treenode stmt= stmts->children;
			while(stmt!=NULL)
			{
				// printf("Inside while\n");
				if(stmt->children!=NULL  &&stmt->children->id==125)//funcallstmt
				{
					// printf("Inside if dude\n");
					if(searchInFuncList(funlist, stmt->children->children->next->lexeme, num_func)==0)
					{
						printf("Line : %d ERROR : Function called: %s not defined previously\n", stmt->line, stmt->children->children->next->lexeme);
					}
					else{

						checkonefuncall(stmt->children, scope, stable,globalVarList);

					}
				}
				else if(stmt->children!=NULL  &&(stmt->children->id==34 || stmt->children->id==35) )
				{
					checkIOstmt(stmt->children, scope, stable,globalVarList,recList);
				}
				stmt=stmt->next;
			}
		}	
		functions= functions->next;
	}
}



