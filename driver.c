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
	printf("Both lexical and syntax analyser modules implemented.\n");
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
	
	removeComments(fp,cleanfile);
	rewind(fp);
	rewind(cleanfile);
	lineNo=1;
	return;
}

treenode runLexerAndParser(FILE* fp, FILE* parseTreeOutputFile, node* gRules, hashtable ht, parseTable pTable){
	
    if(ht==NULL) ht=createHashTable();
   
    if(gRules==NULL)  gRules = readGrammar("Grammar.txt",ht);
    
    int	error=0;
 	int bsize=300;
	char *buffer=(char*)malloc(bsize*sizeof(char));
   	tokenInfo t;
   	t=getNextToken(fp,buffer,bsize);
   	treenode w = parseInputSourceCode(fp, pTable,gRules,t,buffer, bsize,ht,&error);
   	if(error==0){
   		printf("Input Source Code is syntactically correct....\n");
   	}
   	rewind(fp);
   	rewind(parseTreeOutputFile);
   	lineNo=1;
   	return w;
   //printTree(w);
}

int main (int argc, char* argv[]){
	int input;
	lineNo=1;
	char inputFileName[50], outputFileName[50];
	FILE* fp ;
		FILE* parseTreeOutputFile ;
		FILE* cleanfile ;

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
		parseTreeOutputFile = fopen(argv[2], "w");
		cleanfile = fopen("cleanfile.txt", "w");
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
	
	input = (int)str[0]-'0';

	if(input>=0 && input<=4){
	switch (input){
		case 0:
			exit(0);
			break;

		case 1: 
			printf("Removing Comments...\n");
			printRemoveComments(fp, cleanfile);
			break;	
		
		case 2:
			printf("Printing token list...\n");
			printTokenList(fp);
			break;

		case 3:
			printf("Parsing...\n");
			if(fp==NULL) printf("file pointer error");
			treenode tree = runLexerAndParser(fp, parseTreeOutputFile, gRules, ht,pt); 
			// printInorderTraversal(tree, parseTreeOutputFile);
			fprintf(parseTreeOutputFile,"%15s %6s %19s %15s %25s %8s %18s\n", "lexeme", "Line", "Token","Value","Parent","isLeaf","Node Symbol" );

			printParseTree(tree, parseTreeOutputFile);
			break;	

		case 4:
		; 
            clock_t start_time=0, end_time=0;
            double total_CPU_time, total_CPU_time_in_seconds;
            start_time = clock();
                                                // invoke your lexer and parser here
			printf("Printing total time taken...\n");

			runLexerAndParser(fp, parseTreeOutputFile, gRules, ht,pt);

            end_time = clock();
            total_CPU_time  =  (double) (end_time - start_time);
            total_CPU_time_in_seconds =   total_CPU_time / CLOCKS_PER_SEC;
            printf("Total CPU time = %f \nTotal CPU time in seconds %f\n",total_CPU_time, total_CPU_time_in_seconds);
			break;	 

		default:
			printf("Invalid input\n");
			break;
	}
	}		
	else
	{
		printf("Invalid input\n");
	}		
	}
	fclose(fp);
	fclose(parseTreeOutputFile);
	fclose(cleanfile);
	return 0;
}

