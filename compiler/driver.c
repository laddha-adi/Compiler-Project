
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "lexer.h"
#include <time.h>

void printOptions(){
	printf("\n");
	printf("Select one of the following options:-\n");
	printf("Press 0 to exit the program.\n");
	printf("Press 1 to remove comments and print code on the console.\n");
	printf("Press 2 to print the token list\n");
	printf("Press 3 to check for syntactic correctness of the input source code\n");
	printf("Press 4 to print the total time taken by lexer and parser\n");
	printf("Select an option: ");
}

void printIntro(){

//	printf("\nFIRST and FOLLOW sets automated.\n");
	printf("Both lexical and syntax analyser moudles implemented.\n");
//	printf("Error handling done only for lexical analyser module.\n");
//	printf("Lexical errors, if any, would appear while printing tokens in option 2.\n");
//	printf("Files with syntactic errors would result in process termination.\n");
	printf("\n");

}



void printTokenList(char* fileName){

	FILE* fp=fopen(fileName,"r");
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
        printf("Line no. %d\t Value %d\t Lexeme %s\n", token.line, token.value, "getCorrespondingString()");
        token=getNextToken(fp,buffer,bsize);
    }
}


treenode runLexerAndParser(char* inputFile, char* parseTreeOutputFile){
    hashtable ht=createHashTable();
    node * gRules = readGrammar("Grammar.txt",ht);
    getFirst(ht,"First.txt");
    getFollow(ht,"Follow.txt");
    parseTable pTable = createParseTable(ht,gRules);
    FILE* fp=fopen(inputFile,"r");
    if (fp==NULL) 
        {
            fputs ("File error",stderr);
            exit (1);
        }
 	int bsize=1000;
	char *buffer=(char*)malloc(bsize*sizeof(char));
   	tokenInfo t;
   	t=getNextToken(fp,buffer,bsize);
   	treenode w = parseInputSourceCode(fp, pTable,gRules,t,buffer, bsize);
   	return w;
   //printTree(w);
}

int main (int argc, char* argv[]){
	int input;
	char inputFileName[50], outputFileName[50];
	if(argc != 3)
	{
		printf("Incorrect number of arguments passed. Exiting with return value 1\n");
		return 1;
	}
	else
	{
		strcpy(inputFileName,argv[1]);
		strcpy(outputFileName, argv[2]);
	}

	printIntro();

	while(1){
		printOptions();
	scanf("%d", &input);

	switch (input){
		case 0:
			exit(0);
			break;

		case 1: 
			printf("Removing Comments...\n");
			printRemoveComments(inputFileName, "cleanFile.txt");
			break;	
		
		case 2:
			printf("Printing token list...\n");
			printTokenList(inputFileName);
			break;

		case 3:
			printf("Parsing...\n");
			treenode tree = runLexerAndParser(inputFileName, outputFileName);
			printInorderTraversal(tree, outputFileName);
			break;	

		case 4: 
            /*clock_t    start_time, end_time;
            double total_CPU_time, total_CPU_time_in_seconds;
            start_time = clock();*/
                                                // invoke your lexer and parser here
			printf("Printing total time taken...\n");

			runLexerAndParser(inputFileName, outputFileName);

            /*end_time = clock();
            total_CPU_time  =  (double) (end_time - start_time);
            total_CPU_time_in_seconds =   total_CPU_time / CLOCKS_PER_SEC;
            printf("Total CPU time = %f \n Total CPU time in seconds %f\n",total_CPU_time, total_CPU_time_in_seconds);
			*/break;	

		default:
			printf("Invalid input\n");
			break;
	}
			
			
	}

	return 0;
}

