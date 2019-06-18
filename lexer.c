/*
GROUP NUMBER: 11
NIKKI GUPTA 2016A7PS0057P
SAHIL RANADIVE 2016A7PS0097P
ADITI AGARWAL 2016A7PS0095P
ADITYA LADDHA 2016A7PS0038P
*/


#include  "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lex_error = 0;


hashTableEntry** hashTable;

FILE *getStream(FILE* fp,char* buffer,int bsize)
{
	int count;
	if(!feof(fp))
		count=fread(buffer,1,bsize,fp);

	if(count<bsize)
	buffer[count] = '\0';

	return fp;

}

int getLexerErrors(){
  return lex_error;
}

void resetLexError(){
  lex_error = 0;
}


void createLexerHashTable(){
	const int m=1e2+9;

	hashTable=(hashTableEntry**)malloc(m*sizeof(hashTableEntry));
	
	char keywords[23][15]={"with","parameters","end","while","type","global",
	"parameter","list","input","output","int","real","endwhile","if","then","endif",
	"read","write","return","call","record","endrecord","else"}; 

	int tokenids[23]={9,10,11,12,13,15,16,17,20,21,22,23,28,31,32,33,34,35,36,41,42,43,44};

	for(int j=0;j<23;j++){
		hashTable[hashFunc(keywords[j])]=(hashTableEntry*)malloc(sizeof(hashTableEntry));
		hashTable[hashFunc(keywords[j])]->keyword=(char*)malloc(15*sizeof(char));
		strcpy(hashTable[hashFunc(keywords[j])]->keyword,keywords[j]);
		hashTable[hashFunc(keywords[j])]->tokenId=tokenids[j];
		//printf("%s %d \n",hashTable[hashFunc(keywords[j])]->keyword,hashTable[hashFunc(keywords[j])]->tokenId);
	}

}

int lookup(char* lexeme){

	int in=hashFunc(lexeme);
	if(hashTable[in]!=NULL && !strcmp(hashTable[in]->keyword,lexeme)){

		return hashTable[in]->tokenId;
	}
	return -1;

}

long long hashFunc(char* string){
	const int p=31;
	const int m=1e2+9;
	long long hashValue=0;
	long long power=1;
	for(int i=0;i<strlen(string);i++){
		hashValue+=(string[i]*power)%m;
		power*=p;
	}
	return hashValue%m;
}

tokenInfo getNextToken(FILE *fp, char* buffer,int bsize)
{
	if(ftell(fp)==0){
		createLexerHashTable();
	}

	state = 1;
	char* lexeme = (char*) malloc(bsize*sizeof(char));
	memset(lexeme, 0, bsize);
	int i = 0;
	tokenInfo token;
	token.value = (char*) malloc(bsize*sizeof(char));
	token.tokenId=0;

	int error = 0;

	while(1){
		if (offset == bsize || buffer[offset] == '\0'|| strlen(buffer)==0 ){
			if(feof(fp)){
				
				if(strlen(lexeme)!=0){
					if(token.tokenId==0){
						printf("Line no: %d : Error: Unknown pattern <%s>\n",lineNo, lexeme);
						lex_error++;
						error=1;
						lexicalerror=1;
						state=1;

					}
					else{
						strcpy(token.value,lexeme);
						token.line=lineNo;
						if(token.tokenId==3){
							if(lookup(token.value)!=-1){
								token.tokenId=lookup(token.value);
							}
						}
						return token;
					}
				}
				else{
					token.tokenId = 54;
					token.value = "$";
					token.line = lineNo;
					return token;
				}
			}
			memset(buffer, 0, sizeof(buffer));
			fp = getStream(fp, buffer, bsize);
			offset = 0;


		}

		switch(state){
			
			case 1:
				switch(buffer[offset])
				{
					case ' ':
						state=1;
						offset++;
						break;
					case '\t':
						state=1;
						offset++;
						break;
					case '\r':
						state = 1;
						offset++;
						break;
					case '\n':
						state=1;
						lineNo++;
						offset++;
						break;
					case '%':
						state=2;
						token.tokenId=2;
						lexeme[i++]=buffer[offset++];
						break;
					case 'a':
					case 'e':
					case 'f':
					case 'g':
					case 'h':
					case 'i':
					case 'j':
					case 'k':
					case 'l':
					case 'm':
					case 'n':
					case 'o':
					case 'p':
					case 'q':
					case 'r':
					case 's':
					case 't':
					case 'u':
					case 'v':
					case 'w':
					case 'x':
					case 'y':
					case 'z':
						state = 9;
						token.tokenId=3;
						lexeme[i++]=buffer[offset++];
						break;
					case 'b':
					case 'c':
					case 'd':
						state = 6;
						token.tokenId=3;
						lexeme[i++]=buffer[offset++];
						break;
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						state = 3;
						token.tokenId=5;
						lexeme[i++] = buffer[offset++];
						break;
					case '_':
						state = 10;
						lexeme[i++] = buffer[offset++];
						break;
					case '#':
						state = 13;
						lexeme[i++] = buffer[offset++];
						break;
					case '@':
						state = 15;
						lexeme[i++] = buffer[offset++];
						break;
					case '&':
						state = 17;
						lexeme[i++] = buffer[offset++];
						break;
					case '<':
						state = 19;
						token.tokenId=48;
						lexeme[i++] = buffer[offset++];
						break;
					case '>':
						state = 20;
						token.tokenId=51;
						lexeme[i++] = buffer[offset++];						
						break;
					case '!':
						state = 21;
						lexeme[i++] = buffer[offset++];
						break;
					case '=':
						state = 22;
						lexeme[i++] = buffer[offset++];
						break;
					case '[':
						offset++;
						token.tokenId = 18;
						token.line = lineNo;
						token.value = "[";
						return token;
					case ']':
						offset++;
						token.tokenId = 19;
						token.line = lineNo;
						token.value = "]";
						return token;
					case ',':
						offset++;
						token.tokenId = 24;
						token.line = lineNo;
						token.value = ",";
						return token;
					case ';':
						offset++;
						token.tokenId = 25;
						token.line = lineNo;
						token.value = ";";
						return token;
					case ':':
						offset++;
						token.tokenId = 26;
						token.line = lineNo;
						token.value = ":";
						return token;
					case '.':
						offset++;
						token.tokenId = 27;
						token.line = lineNo;
						token.value = ".";
						return token;
					case '(':
						offset++;
						token.tokenId = 29;
						token.line = lineNo;
						token.value = "(";
						return token;
					case ')':
						offset++;
						token.tokenId = 30;
						token.line = lineNo;
						token.value = ")";
						return token;
					case '+':
						offset++;
						token.tokenId = 37;
						token.line = lineNo;
						token.value = "+";
						return token;
					case '-':
						offset++;
						token.tokenId = 38;
						token.line = lineNo;
						token.value = "-";
						return token;
					case '*':
						offset++;
						token.tokenId = 39;
						token.line = lineNo;
						token.value = "*";
						return token;
					case '/':
						offset++;
						token.tokenId = 40;
						token.line = lineNo;
						token.value = "/";
						return token;
					case '~':
						offset++;
						token.tokenId = 47;
						token.line = lineNo;
						token.value = "~";
						return token;
					case '\0':
						// printf("Scanning Complete!\n");
						if(feof(fp)){
							token.tokenId = 54;
							token.value = "$";
							token.line = lineNo;
							return token;
						}
						else
							break;
					default:
					lexicalerror = 1;
						printf("Line No %d : Error: Unknown Symbol <%c>\n",lineNo, buffer[offset]);
						lex_error++;
						offset++;
						error = 1;
						state=1;
						break;						
					}
					break;
			case 2:
				if(buffer[offset++]=='\n')
				{
				token.tokenId = 2;
				token.line = lineNo;
				token.value = "%";
				lineNo++;
				return token;
				}
				else{

					state=2;
					break;
				}

			case 3:
				//integer number that may become rnum
				if( buffer[offset]>=48 && buffer[offset]<=57){
					lexeme[i++] = buffer[offset++];
					state=3;
					break;
				}
				if(buffer[offset] != '\0' && offset != bsize && buffer[offset] == '.'){
					state = 4;
					token.tokenId=0;
					lexeme[i++] = buffer[offset++];
					break;
				}
				token.tokenId = 5;
				strcpy(token.value, lexeme);
				token.line = lineNo;
				//memset(lexeme, 0, sizeof(lexeme));
				return token;

			case 4:
				if( buffer[offset]>=48 && buffer[offset]<=57){
					state=5;
					lexeme[i++]=buffer[offset++];
				}
				else{
						printf("Line no: %d : Error: Unknown pattern <%s>\n",lineNo, lexeme);
						lex_error++;
						error = 1;
						lexicalerror=1;
						state=1;
				}
				break;

			case 5:
				if( buffer[offset]>=48 && buffer[offset]<=57){
					lexeme[i++] = buffer[offset++];
					token.tokenId = 6;
					strcpy(token.value, lexeme);
					token.line=lineNo;
					return token;
				}
				else{
						printf("Line no: %d : Error: Unknown pattern <%s>\n",lineNo, lexeme);
						lex_error++;
						error = 1;
						lexicalerror=1;
						state=1;
				}
				break;

			case 6:
				if( buffer[offset]>=50 && buffer[offset]<=55){
					state=7;
					lexeme[i++] = buffer[offset++];
					token.tokenId = 4;
				}
				else if(buffer[offset]>=97 && buffer[offset]<=122){
					state=9;
					lexeme[i++] = buffer[offset++];
					token.tokenId = 3;
				}
				else{
					strcpy(token.value,lexeme);
					token.tokenId=3;
					token.line=lineNo;
					int key=lookup(lexeme);
					if(key!=-1){
						token.tokenId=key;
					}
					return token;
				}
				break;
			case 7:
				if( buffer[offset]>=50 && buffer[offset]<=55){
					state=8;
					lexeme[i++] = buffer[offset++];
					token.tokenId = 4;
				}
				else if(buffer[offset]>=98 && buffer[offset]<=100){
					state=7;
					lexeme[i++] = buffer[offset++];
					token.tokenId = 4;
				}
				else{
					strcpy(token.value,lexeme);
					token.tokenId=4;
					token.line=lineNo;
					if(strlen(lexeme)>20){
						printf("Line No %d: Error: Variable Identifier is longer than the prescribed length of 20 characters.\n", lineNo);
						lex_error++;
						error = 1;
						lexicalerror=1;
						state=1;
						break;
					}
					return token;
				}
				break;
			case 8:
				if( buffer[offset]>=50 && buffer[offset]<=55){
					state=8;
					lexeme[i++] = buffer[offset++];
					token.tokenId = 4;
				}
				else{
					strcpy(token.value,lexeme);
					token.tokenId=4;
					token.line=lineNo;
					if(strlen(lexeme)>20){
						printf("Line No %d: Error :Variable Identifier is longer than the prescribed length of 20 characters.\n", lineNo);
						error = 1;
						lex_error++;
						lexicalerror=1;
						state=1;
						break;
					}
					return token;
				}
				break;
			case 9:
				if(buffer[offset]>=97 && buffer[offset]<=122){
					state=9;
					lexeme[i++] = buffer[offset++];
					token.tokenId = 3;
				}
				else{
					strcpy(token.value,lexeme);
					token.tokenId=3;
					token.line=lineNo;
					int key=lookup(lexeme);
					if(key!=-1){
						token.tokenId=key;
					}
					return token;
				}
				break;
			case 10:
				if((65 <=buffer[offset] && buffer[offset] <= 90) || (97 <=buffer[offset] && buffer[offset] <= 122)){
					state=11;
					token.tokenId=7;
					lexeme[i++] = buffer[offset++];
				}
				else{
						printf("Line no: %d : Error: Unknown pattern <%s>\n",lineNo, lexeme);
						lex_error++;
						error = 1;
						lexicalerror=1;
						state=1;
				}
				break;
			case 11:
				if((65 <=buffer[offset] && buffer[offset] <= 90) || (97 <=buffer[offset] && buffer[offset] <= 122)){
					state=11;
					token.tokenId=7;
					lexeme[i++] = buffer[offset++];
				}
				else if(buffer[offset]>=48 && buffer[offset]<=57){
					state=12;
					token.tokenId=7;
					lexeme[i++] = buffer[offset++];
				}
				else{
					//const char* keyword="_main";
					if(!strcmp("_main",lexeme)){
						token.tokenId=14;
						token.value=lexeme;

					}
					
					strcpy(token.value,lexeme);
					token.line=lineNo;
					if(strlen(lexeme)>30){
						printf("Line No %d: Error :Function Identifier is longer than the prescribed length of 30 characters.\n", lineNo);
						lex_error++;
						error = 1;
						lexicalerror=1;
						state=1;
						break;
					}
					return token;

				}
				break;
			case 12:
				if(buffer[offset]>=48 && buffer[offset]<=57){
					state=12;
					token.tokenId=7;
					lexeme[i++] = buffer[offset++];
				}
				else{
					token.tokenId=7;
					token.line=lineNo;
					strcpy(token.value,lexeme);
					if(strlen(lexeme)>30){
						printf("Line No %d: Error :Function Identifier is longer than the prescribed length of 30 characters.\n", lineNo);
						lex_error++;
						error = 1;
						lexicalerror=1;
						state=1;
						break;
					}
					return token;

				}
				break;

			case 13:
				if(buffer[offset]>=97 && buffer[offset]<=122){
					state=14;
					token.tokenId=8;
					lexeme[i++] = buffer[offset++];

				}
				else{
						printf("Line no: %d : Error: Unknown pattern <%s>\n",lineNo, lexeme);
						lex_error++;
						error = 1;
						lexicalerror=1;
						state=1;
				}
				break;
			case 14:
				if(buffer[offset]>=97 && buffer[offset]<=122){
					state=14;
					token.tokenId=8;
					lexeme[i++] = buffer[offset++];

				}

				else{
					token.tokenId=8;
					token.line=lineNo;
					strcpy(token.value,lexeme);
					return token;
				}
				break;
			case 15:
				if(buffer[offset]=='@'){
					state=16;
					token.tokenId=0;
					lexeme[i++] = buffer[offset++];

				}

				else{
						printf("Line no: %d : Error: Unknown pattern <%s>\n",lineNo, lexeme);
						lex_error++;
						error = 1;
						lexicalerror=1;
						state=1;
				}
				break;

			case 16:
				if(buffer[offset]=='@'){
					lexeme[i++] = buffer[offset++];
					token.tokenId=46;
					strcpy(token.value,lexeme);
					token.line=lineNo;
					return token;

				}

				else{
						printf("Line no: %d : Error: Unknown pattern <%s>\n",lineNo, lexeme);
						lex_error++;
						error = 1;
						lexicalerror=1;
						state=1;
				}
				break;
			case 17:
				if(buffer[offset]=='&'){
					state=18;
					token.tokenId=0;
					lexeme[i++] = buffer[offset++];

				}

				else{
						printf("Line no: %d : Error: Unknown pattern <%s>\n",lineNo, lexeme);
						lex_error++;
						error = 1;
						lexicalerror=1;
						state=1;
				}
				break;

			case 18:
				if(buffer[offset]=='&'){
					lexeme[i++] = buffer[offset++];
					token.tokenId=45;
					strcpy(token.value,lexeme);
					token.line=lineNo;
					return token;

				}

				else{
						printf("Line no: %d : Error: Unknown pattern <%s>\n",lineNo, lexeme);
						lex_error++;
						error = 1;
						lexicalerror=1;
						state=1;
				}
				break;
			case 19:
				if(buffer[offset]=='='){
					lexeme[i++] = buffer[offset++];
					token.tokenId=49;
					strcpy(token.value,lexeme);
					token.line=lineNo;
					return token;
				}
				else if(buffer[offset]=='-'){
					token.tokenId=0;
					lexeme[i++] = buffer[offset++];
					state=23;
				}
				else{
					token.tokenId=48;
					strcpy(token.value,lexeme);
					token.line=lineNo;
					return token;
				}
			break;
			case 20:
				if(buffer[offset]=='='){
					lexeme[i++] = buffer[offset++];
					token.tokenId=52;
					strcpy(token.value,lexeme);
					token.line=lineNo;
					return token;
				}
				else{
					token.tokenId=51;
					strcpy(token.value,lexeme);
					token.line=lineNo;
					return token;
				}
			case 21:
				if(buffer[offset]=='='){
					lexeme[i++] = buffer[offset++];
					token.tokenId=53;
					strcpy(token.value,lexeme);
					token.line=lineNo;
					return token;
				}
				else{
					printf("Line No %d: Error : Unknown Symbol <%c>\n",lineNo, buffer[offset-1]);
					lex_error++;
					error = 1;
					lexicalerror=1;
				}
				break;
			case 22:
				if(buffer[offset]=='='){
					lexeme[i++] = buffer[offset++];
					token.tokenId=50;
					strcpy(token.value,lexeme);
					token.line=lineNo;
					return token;
				}
				else{
					printf("Line No %d: Error : Unknown Symbol <%c>\n",lineNo, buffer[offset-1]);
					lex_error++;
					error = 1;
					lexicalerror=1;
				}
				break;
			case 23:
				if(buffer[offset]=='-'){
					state=24;
					token.tokenId=0;
					lexeme[i++] = buffer[offset++];

				}

				else{
						printf("Line no: %d : Error: Unknown pattern <%s>\n",lineNo, lexeme);
						lex_error++;
						error = 1;
						lexicalerror=1;
				}
				break;

			case 24:
				if(buffer[offset]=='-'){
					lexeme[i++] = buffer[offset++];
					token.tokenId=1;
					strcpy(token.value,lexeme);
					token.line=lineNo;
					return token;

				}

				else{
						printf("Line no: %d : Error: Unknown pattern <%s>\n",lineNo, lexeme);
						lex_error++;
						error = 1;
						lexicalerror=1;
				}
				break;
			default:
				printf("Illegal state %d reached! How?", state);
				error = 1;
				break;
		}//end of switch
		if(error==1){
				error = 0;
				state = 1;
				i = 0;
				memset(lexeme, 0, sizeof(lexeme));
		}
	}
	
}

void removeComments(FILE* testfile){
	char c=getc(testfile);

	while(c!=EOF){
		if(c=='%'){
			while(c!='\n'){
				c=getc(testfile);
			}
		}
		//printf("%c", c);
		//fputc(c,cleanfile);
		c=getc(testfile);
	}
	rewind(testfile);
	//rewind(cleanfile);
}

