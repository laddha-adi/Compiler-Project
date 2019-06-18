/*
GROUP NUMBER: 11
NIKKI GUPTA 2016A7PS0057P
SAHIL RANADIVE 2016A7PS0097P
ADITI AGARWAL 2016A7PS0095P
ADITYA LADDHA 2016A7PS0038P
*/


#include "ast.h"
#include "lexer.h"
#include "parser.h"

void copynode(treenode currentnode,treenode temp){
	if(currentnode==NULL||temp==NULL)printf("Null nodes here..\n");
	temp->id = currentnode->id;
	temp->line=currentnode->line;
	strcpy(temp->lexeme, currentnode->lexeme);
}

treenode createAST(treenode parseTree){
	treenode currentnode = parseTree;
	treenode temp=NULL;
	treenode sibling = NULL;
	treenode child=NULL;
	treenode parent=NULL;
	if(currentnode==NULL){
		printf("Empty node. How?\n" );
	}


	if(currentnode->children==NULL && currentnode->next==NULL){
		//printf("cond1\n");
		switch(currentnode->id){
			case 4://id
					temp = currentnode;
					while(temp->id != 143){//var
						temp = temp->parent;
					}
					copynode(currentnode,temp);
					break;
			// case 5://num
			// case 6://rnum
			// 		temp = currentnode;
			// 		while(temp->id != 143 || temp->id != 132 || temp->id != 140){//allvar,all,var
			// 			temp = temp->parent;
			// 		}
			// 		copynode(currentnode,temp);
			// 		break;
			case 22://int
			case 23://real
					temp = currentnode;
					while(temp->id != 108){//primdatatype
						temp = temp->parent;
					}
					copynode(currentnode,temp);
					break;

			case 8://recordid
					temp = currentnode;
					while(temp->id != 109){//constructeddatatype
						temp = temp->parent;
					}
					copynode(currentnode,temp);
					break;

			case 134: //exprime
					
					if(currentnode->parent->id==133){   //first exprime of the arithmetic tree just collapse exprime
						temp=currentnode->parent->parent;//assignstmt
						//printf("id of temp is %d\n",temp->id);
						parent=currentnode->parent;//arthexp
						child=temp->children;
						//printf("id of child is %d\n",child->id);
						if(child->id==133)//arthexp has been called by term
						{
							temp->children=parent->children;
							temp->children->parent=temp;
							temp->children->next=parent->next;
							free(parent);

						}
						else{//arthexp has been called by assignstmt

							while(child->next->id!=133){
							child=child->next;
							}
							child->next=parent->children;
							parent->children->next=NULL;
							//printf("id of temp is %d\n",temp->id);
							parent->children->parent=temp;
							
							free(parent);
						}
						
						// free(currentnode);
					}
					else{ // exprime being collapsed is not the first exprime
					parent= currentnode->parent->parent;
					temp=currentnode->parent;
					child= parent->children;
					//printf("parent of termprime is %d\n", child->id);
					// printTree(parent);

					while(child->next->id!= 37&&child->next->id!= 38)
					{
						child=child->next;
					}
					child->next= temp->children;

					while(child->next->next!=NULL)
					{

						child->parent = parent;
						child=child->next;
					}
					child->parent=parent;
					child->next=NULL;
					
					free(temp);
					// free(currentnode);
					}
					break;

			case 136://termprime

					parent= currentnode->parent->parent;
					temp=currentnode->parent;
					child= parent->children;
					//printf("befor whule\n");
					// printTree(parent);
					if(child->id==123&&temp->next==NULL&&parent->id==122){//b<---3;
						child->next=temp->children;
						temp->children->next=NULL;
						temp->children->parent=parent;
						free(temp);
						// free(currentnode);




					}
					else if(child->id==135&&temp->next!=NULL){//b<--4+6

					parent->children=temp->children;
					parent->children->next=temp->next;
					parent->children->parent=parent;
					free(temp);
					// free(currentnode);
						
					}
					else if(child->id==135&&temp->next==NULL){

						child->next=temp->children;
						child=child->next;
						child->parent=parent;
						child->next=NULL;
						free(temp);
						// free(currentnode);
						break;


					}

					else{
						while(child->next->id!= 39 && child->next->id!= 40&&child->next->id!= 37&&child->next->id!= 38)
					{
						child=child->next;
					}
					child->next= currentnode->parent->children;

					while(child->next->next!=NULL)
					{

						child->parent = parent;
						child=child->next;
					}
					child->parent=parent;
					child->next=NULL;
					
					free(temp);
					// free(currentnode);
					}
					
					
					
					break;
			case 45://and
			case 46://or
			case 48://lt
			case 49://le
			case 50://eq
			case 51://ge
			case 52://gt
			case 53://ne
					temp = currentnode; //double collapse the above into booleanexp
					parent= currentnode->parent;
					while(temp->id != 142)
						temp = temp->parent;
					copynode(currentnode,temp);

					child=temp->children;
					while(child->next->id!=145&&child->next->id!=144){
						child=child->next;

					}

					sibling=child->next->next;
					child->next=sibling;
					// free(currentnode);
					free(parent);
					break;
		}
		//deleting the leaf nodes
		//Except INT, REAL, STRING, MATRIX, ID, NUM, RNUM, STR
		switch(currentnode->id){
			case 11: //end
			case 25://;
			case 19://]
			case 30://)
			case 33://endif
			case 37://+
			case 38://-
			case 39://*
			case 40:// div
			case 45:// and
			case 46:// or
			case 22://int
			case 23://real
			case 8://recordid
			case  1://===
			case 28://endwhile
			case 149://moreids
			case 147://optret
			case 141: //temp
			case 134://expprime
			case 150://newallvar
			case 126://outparam
			case 120://otherstmts
			case 119://glbalornot
			case 117://declarations
			case 116://morefields
			case 112://typedefs
			case 110://remlist
			case 105://outputpar
			case 102://otherfuncs
			case 151://allnew
			case 124://new_24
					parent = currentnode->parent;  //make the current node NULL
					if(parent->children->next == NULL)//current node is only child
						parent->children = NULL;
					else{
						child = parent->children;
						while(child->next->next != NULL){

							child = child->next;
							// printf(" checking for newallvar %d\n",child->id );
						}
						// printf("deleting the node\n");
						child->next = NULL;
					}
					free(currentnode);
		}

	}
	else if(currentnode->children!=NULL && currentnode->next==NULL){
			//printf("cond2\n");

			// if(currentnode->parent!=NULL)
			// printf("%d\n",currentnode->parent->id );
			switch(currentnode->id){
			case 101://mainfunc   --
			case 106://paramlist --
			case 146://retstmt  --
			case 122://assngnstmt   --
			case 128://iterative  --
			case 129://conditional  --
			case 131://iostmt  --
			case 125://funcallstmt --
			case 134://exprime  --
			case 130://elsepart --
			case 148://idlist  --
					createAST(currentnode->children);
					break;
			case 102://otherfunc  ----
					temp = currentnode->parent;
					while(temp->id!=100){
						temp = temp->parent;
					}
					child = temp->children;
					while(child->next->id!=101)
						child = child->next;
					currentnode->next=child->next;
					child->next = currentnode;
					currentnode->parent = temp;
					child = child->children;
					while(child->next->id!=102)
						child=child->next;
					child->next = NULL;
					createAST(currentnode->children);
					break;

			case 110://remlist   : collapse this special case
					temp = currentnode->children;
					while(temp->id!=106){
						temp = temp->next;
					}
					parent = currentnode->parent;
					child = parent->children;
					temp->next = parent->next;
					temp->parent = parent->parent;
					parent->next = temp;
					while(child->next->id!=110){
						child = child->next;
					}
					child->next = NULL;
					createAST(temp);
					break;

			case 108://primdataype  : copy in parent
			case 109://constructeddatatype :copy in parent
					temp = currentnode;

					while(temp->id != 107){//datatype
						temp = temp->parent;
					}
					copynode(currentnode,temp);

					parent=currentnode->parent;
					child=currentnode->children;
					parent->children=child;
					while(child!=NULL){

						child->parent=parent;
						child=child->next;
					}


					temp=currentnode->children;
					free(currentnode);
					createAST(temp);
					break;

			case 144://logicalop
			case 145://relationalop
				
					createAST(currentnode->children);
					break;
			case 124://new24   : collapse
			case 150://newallvar  :collapse
			case 151://allnew  : collapse
			case 143://var  : collapse
			case 141://temp  : collapse
					parent = currentnode->parent;
					child = parent->children;
					if(parent->children->id==currentnode->id) //only child condition
					{
						parent->children=currentnode->children;
					}
					else{  // has siblings to left
					while(child->next->id!=currentnode->id){
						child = child->next;
					}

					child->next = currentnode->children;}
					child = currentnode->children;  //adjusting parent pointers
					while(child!=NULL){
						child->parent = parent;
						child=child->next;
					}
					if(currentnode->id==151)
						createAST(currentnode->children);
					free(currentnode);
					break;

			case 112://typedefs
			case 116://morefields
			case 117://declarations
			case 120://otherstmts
					parent = currentnode->parent;
					child = parent->children;

					while(child->next->id!=112 && child->next->id!=116 && child->next->id!=117 && child->next->id!=120)
						child = child->next;
					// printf("before while1 \n");
					child->next = currentnode->children;
					temp = currentnode->children;

					// printf("before while2 \n");
					while(temp!=NULL){
						temp->parent = parent;
						temp = temp->next;
					}
					free(currentnode);
					//child = parent->children;
					//printf("%d\n",child->next->id );
					createAST(child->next);
					break;


			case 136://termprime
			case 140://all : we will look at this after we deal with factor
					createAST(currentnode->children);
					break;
			case 149://moreids
					 temp = currentnode->children;
					while(temp->id!=148){
						temp = temp->next;
					}
					parent = currentnode->parent;
					child = parent->children;
					temp->next = parent->next;
					temp->parent = parent->parent;
					parent->next = temp;
					while(child->next->id!=149){
						child = child->next;
					}
					child->next = NULL;
					createAST(temp);
					break;
			case 100://program
					createAST(currentnode->children);
					break;




		}
	}
	else if(currentnode->children==NULL && currentnode->next!=NULL){
		//printf("cond3\n");
		switch(currentnode->id){
			case 20://input h
			case 16://parameter h
			case 17:// list h
			case 18://sql h
			case 21://output h
			case 14://tkmain h
			case 42://record h
			case 24://comma h
			case 13://type h
			case 26://colon h
			case 1://assignop h
			case 41://call h
			case 9://with h
			case 10://parameters h
			case 12://while h
			case 19://sqr h
			case 29://op h
			case 30://cl h
			case 31://if
			case 44://else
			case 32://then
			case 36://return
			case 43://endrecord
			case 25://sem

					parent=currentnode->parent;
					temp=currentnode->next;

					child=parent->children;
					//printf("%d\n",child->next->id);
					if(child->id==currentnode->id){ //if its the first child of parent
						// printf("first child\n");
						parent->children=currentnode->next;
						free(currentnode);
						createAST(parent->children);
						break;

					}
					else{
						while(child->next->id!=currentnode->id){
							child=child->next;
							//printf("%d\n",child->next->id);
						}
						child->next=currentnode->next;
					}

					free(currentnode);

					createAST(child->next);
					break;
			case 7://funid copy
				if(currentnode->parent->id==125){
					createAST(currentnode->next);
				}
				else{
					currentnode ->parent ->parent->children = currentnode;
					temp = currentnode->parent;
					currentnode->parent = currentnode ->parent ->parent;
					free(temp);
					createAST(currentnode->next);
				}
				
				
				break;

			case 34://read copy to iostmt
			case 35://write   copy to iostmt
			case 47://not copy to boolexp

					temp=currentnode->next;
					parent=currentnode->parent;
					copynode(currentnode,parent);
					parent->children=temp;
					free(currentnode);
					createAST(temp);
					break;

			case 4://id
			case 8://recordid
			case 3://fieldid
			case 27://dot
			case 126://outputparameters
			case 119://globalornot
			case 112://typedefs
			case 105://outputpar
			case 117://declarations

			case 147://optreturn
			case 102://otherfunction
				temp=currentnode->next;
				// free(currentnode);
				createAST(temp);
				break;
			case 120://otherstmts
				temp=currentnode->next;
				parent=currentnode->parent;
				child=parent->children;
				while(child->next->id!=120){
					child=child->next;
				}
				child->next=temp;
				free(currentnode);
				createAST(temp);
				break;


		}

	}
	else if(currentnode->children!=NULL && currentnode->next!=NULL){
		//printf("cond4\n");
		switch(currentnode->id){
			case 102://otherfunc
			case 111://stmts
			case 103://function
			case 104://inputpar
			case 105://outputpar
			case 106://paralist
			case 107://datatype
			case 108://primdatatype
			case 112://typedefs
			case 117: //declarations

			case 113://typedefn
			case 114://fielddefns
			case 115://fielddef
			case 118://declaration
			case 119://globalornot

			case 123://singleorRecId
			case 133://arthexp
			case 126://outputparameters
			case 127://inputparameters
			case 148://idlist
			case 142://boolexp
			case 135://term
			case 144://logicalop
			case 145://relationalop
					// printf("%d\n",currentnode->next->id );
				// printf("calling child of boolean expression %s\n",getCorrespondingString(currentnode->children->id));
					createAST(currentnode->next);

					createAST(currentnode->children);
					break;
			case 121://stmt

					createAST(currentnode->next);
					createAST(currentnode->children);
					break;

			case 132://allvar
					parent=currentnode->parent;
					child=currentnode->children;
					parent->children=child;
					while(child->next!=NULL){
						
						child=child->next;
						child->parent=parent;
					}
					child->parent=parent;
					child->next=currentnode->next;
					free(currentnode);
					createAST(child->next);
					createAST(parent->children);
					break;

			case 137://factor
						parent=currentnode->parent;
						child=currentnode->children;
						parent->children=child;
						while(child->next!=NULL){
							child->parent=parent;
							child=child->next;
						}
						child->parent=parent;
						child->next=currentnode->next;
						free(currentnode);
						createAST(parent->children);
						break;
				case 140: //all
					 createAST(currentnode->next);
					 createAST(currentnode->children);
 					 break;
 				case 138://lowprecedenceOperators
				case 139: //highPrecedenceOperators
						copynode(currentnode->children, currentnode->parent);
					  	copynode(currentnode->children, currentnode->parent->parent);
						// free(currentnode->children);
						parent= currentnode->parent;
						currentnode->parent->children= currentnode->next;
						free(currentnode);
						createAST(parent->children);
						break;

			case 120://otherstmts
					if(currentnode->next->id!=146){

					


					parent=currentnode->parent;
					child=parent->children;
					while(child->next->id!=120){
						child=child->next;
					}
					sibling=child;
					temp=currentnode->children;
					sibling->next=temp;
					while(temp->next!=NULL){
						temp->parent=parent;
						temp=temp->next;

					}
					temp->parent=parent;
					temp->next=currentnode->next;

					free(currentnode);
					createAST(sibling->next);
					}
					else{
						createAST(currentnode->next);
						createAST(currentnode->children);
					}
					break;

			case 143://var
					parent=currentnode->parent; //collapse
					child=currentnode->children;
					parent->children=child;
					child->parent=parent;
					child->next=currentnode->next;
					free(currentnode);
					createAST(child->next);
					break;
			case 147://optionalreturn
					parent=currentnode->parent; //collapse
					child=currentnode->children;
					parent->children=child;
					while(child->next!=NULL){
						child->parent=parent;
						child=child->next;
					}

					child->parent=parent;
					child->next=currentnode->next;
					free(currentnode);
					createAST(parent->children);
					break;
			}
	}
	return(parseTree);
}


