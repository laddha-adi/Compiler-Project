#include "symboltable.h"

symboltable stable;
variable globalVarList;
recordVar recList;

void typechecker(treenode root, symboltable stable, variable globalVarList, recordVar recList){// 22- int, 23- real, 8- record, 0-error

	treenode functions = root->children;
	treenode stmts, stmt;
	char* scope=(char*)malloc(sizeof(char)*50);
	while(functions!=NULL){
		if(functions->children==NULL)
			{functions=functions->next;
			continue;}
		if(functions->next!=NULL && functions->children!=NULL){
			//Function is otherFunctions here.
					//printf("0\n");
			strcpy(scope,functions->lexeme);
			stmts = functions->children->next->next->next;
		}
		else{

			//Function is main here.
			//printf("%d\n", functions->id);
			strcpy(scope,"main");
			stmts = functions->children; 
		}

		stmt=stmts->children;
		while(stmt!=NULL){
			int check;
			switch(stmt->children->id){
				case 122://assignstmt
					check=checkassignstmt(stmt->children,scope);
					break;
				case 128://itersmt
					checkiterstmt(stmt->children,scope);
					break;
				case 129://condstmt
					checkcondstmt(stmt->children,scope);
					break;
			}
			if(check==0)
				printf("ERROR at line %d: Type Mismatch Error\n",stmt->line );
			stmt=stmt->next;
		}

		
		
	}
}

int checkassignstmt(treenode stmt,char* scope){

	int type1=typeOfArithmetic(stmt->children->next,scope);
	int type2=typeOfSingleRec(stmt->children,scope);
	if(type1!=type2 || type1==0 || type2==0){
		// printf("ERROR at line %d: Type Mismatch Error\n",stmt->line );
		return 0;
	}

	return type1;
}

void checkiterstmt(treenode stmt,char* scope){

	int boolcheck= checkBoolExp(stmt->children,scope);
	if(boolcheck==0)
		printf("ERROR at line %d: Type Mismatch Error\n",stmt->line );
	stmt=stmt->children->next;
	while(stmt!=NULL){
			int check;
			switch(stmt->children->id){
				case 122://assignstmt
					check=checkassignstmt(stmt->children,scope);
					break;
				case 128://itersmt
					checkiterstmt(stmt->children,scope);
					break;
				case 129://condstmt
					checkcondstmt(stmt->children,scope);
					break;
			}
			if(check==0)
				printf("ERROR at line %d: Type Mismatch Error\n",stmt->line );
			stmt=stmt->next;
		}	
}

void checkcondstmt(treenode stmt,char* scope){

	int boolcheck= checkBoolExp(stmt->children,scope);
	if(boolcheck==0)
		printf("ERROR at line %d: Type Mismatch Error\n",stmt->line );
	stmt=stmt->children->next;
	while(stmt->next!=NULL){
			int check;
			switch(stmt->children->id){
				case 122://assignstmt
					check=checkassignstmt(stmt->children,scope);
					break;
				case 128://itersmt
					checkiterstmt(stmt->children,scope);
					break;
				case 129://condstmt
					checkcondstmt(stmt->children,scope);
					break;
			}
			if(check==0)
				printf("ERROR at line %d: Type Mismatch Error\n",stmt->line );
			stmt=stmt->next;
		}


	treenode elsepartstmts=stmt->children;
	while(stmt!=NULL){
			int check;
			switch(stmt->children->id){
				case 122://assignstmt
					check=checkassignstmt(stmt->children,scope);
					break;
				case 128://itersmt
					checkiterstmt(stmt->children,scope);
					break;
				case 129://condstmt
					checkcondstmt(stmt->children,scope);
					break;
			}
			if(check==0)
				printf("ERROR at line %d: Type Mismatch Error\n",stmt->line );
			stmt=stmt->next;
		}

	
}



variable searchInlist(variable varlist, char* var_name)
{
	variable temp=varlist;
	while(temp!=NULL)
	{
		if(strcmp(temp->lexeme, var_name)==0)
			return temp ;
		temp=temp->next;
	}

	return NULL;
}

recordVar searchInRecList(recordVar list, char* lex){
	//printf("Searching %s in RecordDef List: ", lex);
	recordVar temp = list;
	while(temp!=NULL){
		if(temp->rname !=NULL && lex!=NULL && strcmp(temp->rname,lex)==0) {
			//printf("Found\n"); 
			return temp;
		}
		temp = temp->next;
	}
	//printf("Not found\n");
	return NULL;
}


int typeOfSingleRec(treenode node,char* scope){

	if(node->children->next==NULL){//only id
		variable stentry= findInSTable(stable, scope);
		if(stentry==NULL)
		{
			printf("Wrong Scope passed to function\n");
			return 0;
		}
		variable i;
		i=searchInlist(stentry->inputpars, node->children->lexeme);
		if(i!=NULL)
			return i->type;
		i=searchInlist(stentry->outputpars, node->children->lexeme);
		if(i!=NULL)
			return i->type;
		i=searchInlist(stentry->localvars, node->children->lexeme);
		if(i!=NULL)
			return i->type;
		i= searchInlist(globalVarList, node->children->lexeme);
			if(i!=NULL)
			return i->type;
		printf("ERROR in line %d:Variable not previously declared\n",node->line);
		return 0;

	}

	else{// id.fieldid
		char* fieldid= node->children->next->next;
		variable i;
		i=searchInlist(stentry->inputpars, node->children->lexeme);
		if(i==NULL){
			i=searchInlist(stentry->outputpars, node->children->lexeme);
			if(i==NULL){
				i=searchInlist(stentry->localvars, node->children->lexeme);
				if(i==NULL){
						i= searchInlist(globalVarList, node->children->lexeme);
				}	
			}
		}
		if(i==NULL){
			printf("ERROR in line %d:Record Instance not previously declared\n",node->line);
			return 0;
		}
		recordVar record= searchInRecList(recList, i->recordName);
		if(record==NULL)
			printf("ERROR in line %d:Record not previously declared\n", node->line);
			return 0;
		recordField recf= record->head;
		while(recf!=NULL)
		{
			if(strcmp(fieldid, recf->lexeme)==0)
				return recf->type;
			recf=recf->next;
		}
		return 0;
	}
	
}


int typeOfArithmetic(treenode node,char* scope){

	if(node->id==140){//all

		
		switch(node->children->id){
			case 4:
				return typeOfSingleRec(node,scope);
				break;
			case 5:
				return 22;
				break;
			case 6:
				return 23;
				break;
			}
		}

	else{//hops and lops

		int type1=typeOfArithmetic(node->children->next,scope);
		int type2=typeOfArithmetic(stmt->children,scope);
		if(type1!=type2 || type1==0 || type2==0){
		// printf("ERROR at line %d: Type Mismatch Error\n",node->line );
		return 0;
		}
		else
			return type1;
		
	}	
	
	
}



int checkBoolExp(treenode node ,char* scope){

	if(node->children->id==47){//boolexp->not boolexp
		return checkBoolExp(node->children->next,scope);
	}


	// char* typeofvar1=(char*)malloc(sizeof(char)*50);
	// char* typeofvar2=(char*)malloc(sizeof(char)*50);

	else if(node->children->id==4||node->children->id==5||node->children->id==6)//boolexp->var relop var
	{
		switch(node->children->id){
			case 4:
				//copy somewhere
				variable stentry= findInSTable(stable, scope);
				if(stentry==NULL)
				{
					printf("Wrong Scope passed to function\n");
					return 0;
				}
				variable i;
				i=searchInlist(stentry->inputpars, node->children->lexeme);
				if(i!=NULL)
					return i->type;
				i=searchInlist(stentry->outputpars, node->children->lexeme);
				if(i!=NULL)
					return i->type;
				i=searchInlist(stentry->localvars, node->children->lexeme);
				if(i!=NULL)
					return i->type;
				i= searchInlist(globalVarList, node->children->lexeme);
					if(i!=NULL)
					return i->type;
				printf("Variable not previously declared\n");
				return 0;
				break;

			case 5:
				typeofvar1=22;
				break;
			case 6:
				typeofvar1=23;
				break;
		}

		switch(node->children->next->id){
			case 4:
				//copy somewhere
				variable stentry= findInSTable(stable, scope);
				if(stentry==NULL)
				{
					printf("Wrong Scope passed to function\n");
					return 0;
				}
				variable i;
				i=searchInlist(stentry->inputpars, node->children->lexeme);
				if(i!=NULL)
					return i->type;
				i=searchInlist(stentry->outputpars, node->children->lexeme);
				if(i!=NULL)
					return i->type;
				i=searchInlist(stentry->localvars, node->children->lexeme);
				if(i!=NULL)
					return i->type;
				i= searchInlist(globalVarList, node->children->lexeme);
					if(i!=NULL)
					return i->type;
				printf("Variable not previously declared\n");
				return 0;
				break;
			case 5:
				typeofvar2=22;
				break;
			case 6:
				typeofvar2=23;
				break;
		}


	}
	else{//boolexp->boolexp logicop boolexp
		typeofvar1= checkBoolExp(node->children ,scope);
		typeofvar1= checkBoolExp(node->children->next ,scope);
		}

	if(typeofvar1!=typeofvar2 || typeofvar1==0 || typeofva2==0)
	{
		// printf("ERROR at line %d: Type Mismatch Error\n",node->line );
		return 0;
	}

	else 
		return typeofvar1;

}