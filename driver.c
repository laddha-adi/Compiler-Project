/*
GROUP NUMBER: 11
NIKKI GUPTA 2016A7PS0057P
SAHIL RANADIVE 2016A7PS0097P
ADITI AGARWAL 2016A7PS0095P
ADITYA LADDHA 2016A7PS0038P
*/


#include "parser.h"
#include "lexer.h"
#include <time.h>
#include "ast.h"
#include "symboltable.h"
#include "semanticanalyzer.h"
#include "codegen.h"

void printOptions(){
	printf("\n");
	printf("Select one of the following options:-\n");
	printf("Press 0 to exit the program.\n");
	printf("Press 1 to print the token list.\n");
	printf("Press 2 to check for syntactic correctness of the input source code and produce parse tree.\n");
	printf("Press 3 to print the Abstract Syntax tree.\n");
	printf("Press 4 to display the amount of allocated memory and number of nodes to the parse tree and abstract syntax tree.\n");
	printf("Press 5 to print the Symbol table.\n");
	printf("Press 6 to print the list of global variables.\n");
	printf("Press 7 to print the total memory requirement for each function.\n");
	printf("Press 8 to print the type expressions and width of global visible record definitions.\n");
	printf("Press 9 to check for syntactic and semantic correctness of the input source code.\n");
	printf("Press 10 to produce assembly code.\n\n");
	printf("Select an option: ");
}

void printIntro(){

//	printf("\nFIRST and FOLLOW sets automated.\n")
	printf("LEVEL 3:Lexer,Parser,AST,SymbolTable,TypeChecker,Semantic Analyzer,Code Generation WORKING\n\n");
//	printf("Error handling done only for lexical analyser module.\n");
//	printf("Lexical errors, if any, would appear while printing tokens in option 2.\n");
//	printf("Files with syntactic errors would result in process termination.\n");
	printf("\n");

}



void printTokenList(FILE* fp){
    
    int bsize=300;
    char *buffer=(char*)malloc(bsize*sizeof(char));
    tokenInfo token;
    token=getNextToken(fp,buffer,bsize);

    while(token.tokenId!=54){
        printf("Line no. %d\t Lexeme %s\t Token %s\n", token.line, token.value, getCorrespondingString(token.tokenId));
        token=getNextToken(fp,buffer,bsize);
    }
    rewind(fp);
    lineNo=1;
}


void printRemoveComments(FILE* fp, FILE* cleanfile){
	
	removeComments(fp);
	rewind(fp);
	rewind(cleanfile);
	lineNo=1;
	return;
}

treenode runLexerAndParser(FILE* fp, node* gRules, hashtable ht, parseTable pTable){
	
    if(ht==NULL) ht=createHashTable();
   
    if(gRules==NULL)  gRules = readGrammar("Grammar.txt",ht);
    
    int	error=0;
 	int bsize=300;
	char *buffer=(char*)malloc(bsize*sizeof(char));
   	tokenInfo t;
   	t=getNextToken(fp,buffer,bsize);
   	treenode w = parseInputSourceCode(fp, pTable,gRules,t,buffer, bsize,ht,&error);
   	
   	rewind(fp);
   	//rewind(parseTreeOutputFile);
   	lineNo=1;
   	return w;
   //printTree(w);
}

int main (int argc, char* argv[]){
	int input;
	lineNo=1;
	char inputFileName[50], outputFileName[50];
	FILE* fp ;
		FILE* asmOutputFile ;

	if(argc != 3)
	{
		printf("Incorrect number of arguments passed. Exiting with return value 1\n");
		return 1;
	}
	else
	{
		strcpy(inputFileName,argv[1]);
		strcpy(outputFileName, argv[2]);

		fp = fopen(argv[1], "r");
		asmOutputFile = fopen(argv[2], "w");
		//cleanfile = fopen("cleanfile.txt", "w");
	}
	hashtable ht = createHashTable();
	node* gRules = readGrammar("Grammar.txt", ht); 
	// printf("Grammar Created!\n");


    getFirst(ht,"First.txt");
    getFollow(ht,"Follow.txt");
    
    parseTable pt = createParseTable(ht,gRules);
    // printf("ParseTable Created");
	printIntro();

	char str[20]; 
	while(1){
		printOptions();
	scanf("%s", str);
	if(str[0]=='1' && strlen(str)==2 && str[1]=='0') input = 10;
	else input = (int)str[0]-'0';

	if(input>=0 && input<=10){
	switch (input){
		case 0:
			exit(0);
			break;

		case 1: 
			printf("Printing token list...\n");
			lineNo=1;
			printTokenList(fp);
			break;	

		case 2:
			printf("Parsing...\n");
			if(fp==NULL) printf("file pointer error");
			treenode tree = runLexerAndParser(fp, gRules, ht,pt);
			 
			printParseTree(tree);
			printf("Parse tree has ben printed in inorder fashion, that is, left child->parent->remaining children\n ");
			if(getLexerErrors() != 0 || getParsingErrors()!=0) {
				printf("The code has Lexical and Syntax error(s).\n");
				break;
			}
			else
				printf("Input Source Code is Syntactically Correct\n");

			break;	

		case 3:
			printf("Printing AST...\n");
			if(fp==NULL) printf("file pointer error");
			treenode asttree= runLexerAndParser(fp, gRules, ht,pt); 
			if(getLexerErrors() != 0 || getParsingErrors()!=0) {
				printf("The code has Lexical and Syntax error(s).\n");
				break;
			}
			asttree=createAST(asttree);
			printParseTree(asttree);
			if(getLexerErrors() != 0 || getParsingErrors()!=0) {
				printf("The code has Lexical and Syntax error(s).\n");
				break;
			}
			else
				printf("Input Source Code is Syntactically Correct\n");
			printf("AST has ben printed in inorder fashion, that is, left child->parent->remaining children\n ");
			break;

		case 4:
			//printf("Printing AST...\n");
			if(fp==NULL) printf("file pointer error");
			treenode asttree2= runLexerAndParser(fp, gRules, ht,pt); 
			if(getLexerErrors() != 0 || getParsingErrors()!=0) {
				printf("The code has Lexical and Syntax error(s).\n");
				break;
			}

			asttree2=createAST(asttree2);
			//printTree(asttree2);
			int psize = getPTreeSize();
			int astSize = countNodes(asttree2);

			int num_nodes = psize/sizeof(struct TreeNode);

			printf("Parse tree: number of nodes = %d\t\t Allocated Memory = %d Bytes\n",num_nodes,psize);
			printf("Abstract syntax tree: number of nodes = %d\t\t Allocated Memory = %d Bytes\n",astSize,astSize*(int)sizeof(struct TreeNode));
			float f = ((float)num_nodes-(float)astSize)/(float)num_nodes;
			f = f*100;
			printf("Compression factor = %f %c \n",f,37);
			break;

		case 5:
			//printf("Printing AST...\n");
			if(fp==NULL) printf("file pointer error");
			treenode asttree3= runLexerAndParser(fp, gRules, ht,pt);
			if(getLexerErrors() != 0 || getParsingErrors()!=0) {
				printf("The code has Lexical and Syntax error(s).\n");
				break;
			} 
			asttree3=createAST(asttree3);
			variable globalList, globalVarHead;
			globalList=NULL;
			globalVarHead =NULL;
			
			recordVar globalRecordDefList, head;
			globalRecordDefList = NULL;
			head = NULL;
			head = findAndInsertRecordDefs(asttree3);
 			globalVarHead = findAndInsertGVariables(asttree3, head);
 			symbolTable stable = (symbolTable)malloc(sizeof(struct symbolTable*)*100);
			 for(int j = 0; j < 100; j++){
				 stable[j]=NULL;
			 }
 			stable = addFunctions(asttree3,globalVarHead,head);
			addOffset(stable, head);			
			printSymbolTable(stable, head);
			cleanVars();
			break;


		case 6:
			//printf("Printing AST...\n");
			if(fp==NULL) printf("file pointer error");
			treenode asttree4= runLexerAndParser(fp, gRules, ht,pt);
			if(getLexerErrors() != 0 || getParsingErrors()!=0) {
				printf("The code has Lexical and Syntax error(s).\n");
				break;
			} 
			asttree4=createAST(asttree4);
			variable globalList2, globalVarHead2;
			globalList2 = NULL;
			globalVarHead2 = NULL;
			
			recordVar globalRecordDefList2, head2;
			globalRecordDefList2 = NULL;
			head2 = NULL;
			head2 = findAndInsertRecordDefs(asttree4);
 			globalVarHead2 = findAndInsertGVariables(asttree4, head2);
 			if(globalVarHead2!=NULL)
 				printGlobalVarList(globalVarHead2);
 			else
 				printf("No global variables\n");
			cleanVars();
			break;

		case 7:
			//printf("Printing AST...\n");
			if(fp==NULL) printf("file pointer error");
			treenode tree7= runLexerAndParser(fp, gRules, ht,pt);
			if(getLexerErrors() != 0 || getParsingErrors()!=0) {
				printf("The code has Lexical and Syntax error(s).\n");
				break;
			} 
			tree7=createAST(tree7);
			variable globalList7, globalVarHead7;
			globalList7 = NULL;
			globalVarHead7 = NULL;
			
			recordVar globalRecordDefList7, head7;
			globalRecordDefList7 = NULL;
			head7 = NULL;
			head7 = findAndInsertRecordDefs(tree7);
 			globalVarHead7 = findAndInsertGVariables(tree7, head7);
 			symbolTable stable7 = (symbolTable)malloc(sizeof(struct symbolTable*)*100);
			 for(int j = 0; j < 100; j++){
				 stable7[j]=NULL;
			 }
 			stable7 = addFunctions(tree7,globalVarHead7,head7);
 			addOffset(stable7, head7);
 			printf("Function Name \t\t Total Width\n");
  			printFunctionOffset(stable7);

			cleanVars();
			break;

		case 8:
			//printf("Printing AST...\n");
			if(fp==NULL) printf("file pointer error");
			treenode tree8= runLexerAndParser(fp, gRules, ht,pt);
			if(getLexerErrors() != 0 || getParsingErrors()!=0) {
				printf("The code has Lexical and Syntax error(s).\n");
				break;
			} 
			tree8=createAST(tree8);
			variable globalList8, globalVarHead8;
			globalList8 = NULL;
			globalVarHead8 = NULL;
			
			recordVar globalRecordDefList8, head8;
			globalRecordDefList8 = NULL;
			head8 = NULL;
			head8 = findAndInsertRecordDefs(tree8);
 			//globalVarHead8 = findAndInsertGVariables(tree8, head8);
 			if(head8!=NULL)
 				printRecordDefList(head8);
 			else{
 				printf("No Record Definitions\n");
 			}
			cleanVars();
			break;



		case 9:
		; 
            clock_t start_time=0, end_time=0;
            double total_CPU_time, total_CPU_time_in_seconds;
            start_time = clock();
                                                // invoke your lexer and parser here
			printf("Printing total time taken...\n");

			treenode tree9= runLexerAndParser(fp, gRules, ht,pt); 
			if(getLexerErrors() != 0 || getParsingErrors()!=0) {
				printf("The code has Lexical and Syntax error(s).\n");
				break;
			}
			else{
				printf("Input Source Code is Syntactically Correct\n");
			}
			tree9=createAST(tree9);
			variable globalList9, globalVarHead9;
			globalList9 = NULL;
			globalVarHead9 = NULL;
			
			recordVar globalRecordDefList9, head9;
			globalRecordDefList9 = NULL;
			head9 = NULL;
			head9 = findAndInsertRecordDefs(tree9);
 			globalVarHead9 = findAndInsertGVariables(tree9, head9);
 			symbolTable stable9 = (symbolTable)malloc(sizeof(struct symbolTable*)*100);
			 for(int j = 0; j < 100; j++){
				 stable9[j]=NULL;
			 }
 			stable9 = addFunctions(tree9,globalVarHead9,head9);
 			addOffset(stable9, head9);
  			//printFunctionOffset(stable9);
  			typechecker(tree9,stable9,globalVarHead9, head9);
 			checkfuncallstmts(tree9, stable9,  globalVarHead9, head9);
			cleanVars();

            end_time = clock();
            total_CPU_time  =  (double) (end_time - start_time);
            total_CPU_time_in_seconds =   total_CPU_time / CLOCKS_PER_SEC;
            printf("Total CPU time = %f \nTotal CPU time in seconds %f\n",total_CPU_time, total_CPU_time_in_seconds);
			break;	




		case 10:
			if(fp==NULL) printf("file pointer error");
			treenode tree10= runLexerAndParser(fp, gRules, ht,pt); 
			if(getLexerErrors() != 0 || getParsingErrors()!=0) {
				printf("The code has Lexical and Syntax error(s).\n");
				break;
			}
			tree10=createAST(tree10);
			variable globalList10, globalVarHead10;
			globalList10 = NULL;
			globalVarHead10 = NULL;
			
			recordVar globalRecordDefList10, head10;
			globalRecordDefList10 = NULL;
			head10 = NULL;
			head10 = findAndInsertRecordDefs(tree10);
 			globalVarHead10 = findAndInsertGVariables(tree10, head10);
 			symbolTable stable10 = (symbolTable)malloc(sizeof(struct symbolTable*)*100);
			 for(int j = 0; j < 100; j++){
				 stable10[j]=NULL;
			 }
 			stable10 = addFunctions(tree10,globalVarHead10,head10);
 			addOffset(stable10, head10);
 			CodeGeneration(tree10,stable10,globalVarHead10,head10, outputFileName);
 			printf("NASM code successfully generated\n");
			cleanVars();

			
			clearvars();
			break;
			
		default:
			printf("Invalid input\n");
			break;
	}

	resetLexError();
	resetParserError();

	}		
	else
	{
		printf("Invalid input\n");
	}		
	}
	fclose(fp);
	return 0;
}



