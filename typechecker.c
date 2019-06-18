/*
GROUP NUMBER: 11
NIKKI GUPTA 2016A7PS0057P
SAHIL RANADIVE 2016A7PS0097P
ADITI AGARWAL 2016A7PS0095P
ADITYA LADDHA 2016A7PS0038P
*/


#include "symboltable.h"
#include "typechecker.h"



void typechecker(treenode root,symbolTable stable, variable globalVarList, recordVar recList){// 22- int, 23- real, 8- record, 0-error

	treenode functions = root->children;
	treenode stmts=NULL;
	treenode stmt=NULL;
	char* scope=(char*)malloc(sizeof(char)*50);
	while(functions!=NULL){
		if(functions->children==NULL)
		{
		functions=functions->next;
		continue;
		}
		if(functions->next!=NULL && functions->children!=NULL){
			strcpy(scope,functions->children->lexeme);
			stmts = functions->children->next->next->next->children->next->next;
		}
		else{
			strcpy(scope,"main");
			stmts = functions->children->children->next->next; 
		}

		stmt=stmts->children;

		while(stmt!=NULL){
			int check;

			if(stmt->children==NULL)
				{
					printf("stmt NULL\n" );
					// break;
				}
			switch(stmt->children->id){
				case 122://assignstmt
					check=checkassignstmt(stmt->children,scope,stable,globalVarList,recList);
					if(check==0)
						printf("Line : %d ERROR: Type Mismatch Error\n",stmt->children->line );
					break;
				case 128: //itersmt
				
					checkiterstmt(stmt->children,scope,stable,globalVarList,recList);
					break;
				case 129://condstmt
					checkcondstmt(stmt->children,scope,stable,globalVarList,recList);
					break;
			}
			stmt=stmt->next;
		}

		functions=functions->next;
		
	}
}

int checkassignstmt(treenode stmt,char* scope,symbolTable stable, variable globalVarList, recordVar recList){

	int type1=typeOfArithmetic(stmt->children->next,scope,stable,globalVarList,recList);
	int type2=typeOfSingleRec(stmt->children,scope,stable,globalVarList,recList);
	if(type2==-1 || type1==-1)
		return -1;
	if(type1!=type2 || type1==0 || type2==0){
		return 0;
	}

	return type1;
}

void checkiterstmt(treenode stmt,char* scope,symbolTable stable, variable globalVarList, recordVar recList){

	int boolcheck= checkBoolExp(stmt->children,scope,stable,globalVarList,recList);
	if(boolcheck==0)
		printf("Line : %d ERROR: Type Mismatch Error\n",stmt->line );

	stmt=stmt->children->next;

	while(stmt!=NULL){
			int check;
			switch(stmt->children->id){
				case 122://assignstmt
					check=checkassignstmt(stmt->children,scope,stable,globalVarList,recList);
					if(check==0)
						printf("Line : %d ERROR: Type Mismatch Error\n",stmt->children->line );
					break;
				case 128: //itersmt
					checkiterstmt(stmt->children,scope,stable,globalVarList,recList);
					break;
				case 129://condstmt
					checkcondstmt(stmt->children,scope,stable,globalVarList,recList);
					break;
			}
			stmt=stmt->next;
		}	
}

void checkcondstmt(treenode stmt,char* scope,symbolTable stable, variable globalVarList, recordVar recList){

	int boolcheck= checkBoolExp(stmt->children,scope,stable,globalVarList,recList);
	if(boolcheck==0)
		printf("Line : %d ERROR: Type Mismatch Error\n",stmt->line );
	stmt=stmt->children->next;
	while(stmt->next!=NULL){
			int check;
			switch(stmt->children->id){
				case 122://assignstmt
					check=checkassignstmt(stmt->children,scope,stable,globalVarList,recList);
					if(check==0)
						printf("Line : %d ERROR: Type Mismatch Error\n",stmt->children->line );
					break;
				case 128: //itersmt
					checkiterstmt(stmt->children,scope,stable,globalVarList,recList);
					// printf("iter stmt done\n");
					break;
				case 129://condstmt
					checkcondstmt(stmt->children,scope,stable,globalVarList,recList);
					break;
			}
			stmt=stmt->next;
		}


	treenode elsepartstmts=stmt->children;
	while(stmt!=NULL){
			int check;
			switch(stmt->children->id){
				case 122://assignstmt
					check=checkassignstmt(stmt->children,scope,stable,globalVarList,recList);
					if(check==0)
						printf("Line : %d ERROR: Type Mismatch Error\n",stmt->children->line );
					break;
				case 128: //itersmt
					checkiterstmt(stmt->children,scope,stable,globalVarList,recList);
					break;
				case 129://condstmt
					checkcondstmt(stmt->children,scope,stable,globalVarList,recList);
					break;
			}
			stmt=stmt->next;
		}

	
}


recordVar searchInRecList(recordVar list, char* lex){
	recordVar temp = list;
	while(temp!=NULL){
		if(temp->rname !=NULL && lex!=NULL && strcmp(temp->rname,lex)==0) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}


int typeOfSingleRec(treenode node,char* scope,symbolTable stable, variable globalVarList, recordVar recList){
	symbolTableElement stentry= findInSTable(stable, scope);
	if(node->children->next==NULL){//only id
		if(stentry==NULL)
		{
			printf("Wrong Scope passed to function %s\n",scope);
			return 0;
		}
		variable i;
		i=searchInListStr(stentry->inputpars, node->children->lexeme);
		if(i!=NULL)
			return i->type;
		i=searchInListStr(stentry->outputpars, node->children->lexeme);
		if(i!=NULL)
			return i->type;
		i=searchInListStr(stentry->localvars, node->children->lexeme);
		if(i!=NULL)
			return i->type;
		i= searchInListStr(globalVarList, node->children->lexeme);
			if(i!=NULL)
			return i->type;
		printf("Line : %d ERROR: Variable %s not previously declared\n",node->line,node->children->lexeme);
		return -1;

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
				}	
			}
		}
		if(i==NULL){
			printf("Line : %d ERROR: Record Instance not previously declared\n",node->line);
			return -1;
		}
		recordVar record= searchInRecList(recList, i->recordName);
		if(record==NULL)
			printf("Line : %d ERROR: Record not previously declared\n", node->line);
			return -1;
		recordField recf= record->head;
		while(recf!=NULL)
		{
			if(strcmp(fieldid, recf->lexeme)==0)
				return recf->type;
			recf=recf->next;
		}
			printf("Line : %d ERROR: Record %s does not contain field %s\n", node->line, i->recordName, fieldid);
		return -1;
	}
	
}


int typeOfArithmetic(treenode node,char* scope,symbolTable stable, variable globalVarList, recordVar recList){

	if(node->id==140){//all

		
		switch(node->children->id){
			case 4:
				return typeOfSingleRec(node,scope,stable,globalVarList,recList);
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

		int type1=typeOfArithmetic(node->children->next,scope,stable,globalVarList,recList);
		int type2=typeOfArithmetic(node->children,scope,stable,globalVarList,recList);
		if(type1==-1||type2==-1)
			return -1;
		if(type1!=type2 || type1==0 || type2==0){
		return 0;
		}
		else
			return type1;
		
	}	
	
	
}



int checkBoolExp(treenode node ,char* scope,symbolTable stable, variable globalVarList, recordVar recList){
	int typeofvar1, typeofvar2;
	if(node->children->id==47){//boolexp->not boolexp
		return checkBoolExp(node->children->next,scope,stable,globalVarList,recList);
	}


	else if(node->children->id==4||node->children->id==5||node->children->id==6)//boolexp->var relop var
	{
		switch(node->children->id){
			case 4:
				;
				symbolTableElement stentry;
				stentry= findInSTable(stable, scope);
				if(stentry==NULL)
				{
					printf("Wrong Scope passed to function %s\n",scope);
					return 0;
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
				if(i==NULL){
				printf("Line : %d ERROR: Variable %s not previously declared\n", node->children->line,node->children->lexeme);
				typeofvar1= -1;}
				else
				{
					typeofvar1= i->type;
					// printf("var 1%d\n",typeofvar1 );
				}
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
				;
				symbolTableElement stentry= findInSTable(stable, scope);
				if(stentry==NULL)
				{
					printf("Wrong Scope passed to function %s\n",scope);
					return 0;
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
				if(i==NULL && strcmp(node->children->next->lexeme, node->children->lexeme)!=0){
				printf("Line : %d ERROR: Variable %s not previously declared\n", node->children->line,node->children->lexeme);
				typeofvar2= -1;}
				else
				{
					typeofvar2= i->type;
				}
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
		typeofvar1= checkBoolExp(node->children ,scope,stable,globalVarList,recList);
		typeofvar2= checkBoolExp(node->children->next ,scope,stable,globalVarList,recList);
		}

	if(typeofvar1==-1 || typeofvar2==-1)
		return -1;
	if(typeofvar1!=typeofvar2 || typeofvar1==0 || typeofvar2==0)
	{
		return 0;
	}

	else 
		return typeofvar1;

}

