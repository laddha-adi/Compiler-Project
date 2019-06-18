/*
GROUP NUMBER: 11
NIKKI GUPTA 2016A7PS0057P
SAHIL RANADIVE 2016A7PS0097P
ADITI AGARWAL 2016A7PS0095P
ADITYA LADDHA 2016A7PS0038P
*/

#include <stdio.h>
#include <stdlib.h>
#include "codegen.h"


int counter_used = 0, globalcount=0;

char registers[14][100] = {"temp1", "temp2", "temp3", "temp4", "temp5", "temp6", "temp7", "temp8", "temp9", "temp10", "temp11", "temp12", "temp13", "temp14"};

void readem(char* what, FILE* f)
{
    fprintf(f, "\n\tmov esi, %s\n\tmov edi, numberin_form\n\tmov al, 0\n\tcall scanf\n\n", what);
}

void writem(char* what, FILE* f)
{

fprintf(f, "\n\tmov edi, numberout_form\n\tmov esi, [%s]\n\tmov al, 0\n\tcall printf\n", what);   
}

void move(char* one, char* two, FILE* f)
{
    fprintf(f, "\n\tmov eax, [%s]", two);
    fprintf(f, "\n\tmov [%s], eax\n", one);
}

variable findIfDeclared(symbolTable stable,char* scope, char* lexeme,variable globalVarList){
     //printf("%s, %s\n",scope,lexeme);
    symbolTableElement stentry=findInSTable(stable, scope);
    variable i=NULL;
    if(stentry==NULL) printf("Error here...");
                
                    i=searchInListStr(stentry->inputpars, lexeme);
                if(i==NULL){
                        i=searchInListStr(stentry->outputpars, lexeme);
                    if(i==NULL){
                        
                            i=searchInListStr(stentry->localvars,lexeme);
                        if(i==NULL){
                                i= searchInListStr(globalVarList,lexeme);
                        }   
                    }
                }
                if(i==NULL)
                    return NULL;

    return i;
}





void handleIOstmt(treenode ionode, FILE* f, symbolTable stable, variable globalVarList,recordVar recList)
{
    if (ionode->children->id == 34) // read command
    {
        // TODO handle record here
        //printf("%s,\n",ionode->children->children->children->lexeme);
        variable var=findIfDeclared(stable,"main",ionode->children->children->children->lexeme,globalVarList);

        if (var==NULL)
        {
            printf("UNEXPECTED ERROR, Program seems to have semantic errors, cannot compile\n");
        }
        else
        {
            if (var->type == 22 ||var->type == 23)//int or real
                readem(ionode->children->children->children->lexeme, f);
            else
            {
                char *big = (char*) malloc(100);

                if (ionode->children->children->children->next!= NULL)
                { //tkid dot record
                    // particular record field to be read/written
                    strcpy(big, ionode->children->children->children->lexeme);
                    strcat(big, ionode->children->children->children->next->next->lexeme);
                    readem(big, f);
                }
                else
                {  //tkid is record
                    recordField recfields=findRecord(recList,var->recordName)->head;

                    while (recfields !=  NULL)
                    {
                        strcpy(big, ionode->children->children->children->lexeme);
                        strcat(big, recfields->lexeme);
                        readem(big, f);

                        recfields = recfields->next;
                    }
                }
            }
        }

    }
    else // write command
    {       
        if (ionode->children->children->id != 4)//not tkid i.e, num rnum

       {
        // printf("%s\n", ionode->children->children->lexeme); 
          writem(ionode->children->children->lexeme,f);
            }
        else
        {
            variable var=findIfDeclared(stable,"main",ionode->children->children->lexeme,globalVarList);

            if (var==NULL)
            {
                printf("UNEXPECTED ERROR, Program seems to have semantic errors, cannot compile\n");
            }

            else
            {
                if (var->type == 22 ||var->type == 23)
                    writem(ionode->children->children->lexeme, f);
                else
                {
                    char *big = (char*) malloc(100);

                    if (ionode->children->children->next!= NULL)
                    {
                        // particular record field to be read/written
                        strcpy(big, ionode->children->children->lexeme);
                        strcat(big, ionode->children->children->next->next->lexeme);
                        writem(big, f);
                    }
                    else
                    {
                            recordField recfields=findRecord(recList,var->recordName)->head;
                    while (recfields !=  NULL)
                    {
                        strcpy(big, ionode->children->children->lexeme);
                        strcat(big, recfields->lexeme);
                        writem(big, f);

                        recfields = recfields->next;
                    }
                    }
                }
            }
        }
    }
}


void handleDeclarations(treenode decnode, FILE* f, symbolTable stable, variable globalVarList,recordVar recList)
{
    // add static "section .bss to file"
    char sec_bss[] = "section .bss\n";
    fprintf(f, "%s\n", sec_bss);

    while(decnode != NULL)
    {
        // add a check here for "TK_INT" or "TK_REAL"

        // add comments to asm code0
        // record case:
        if (decnode->children->id == 8)
        {
            // record must be found
            recordVar rec=findRecord(recList,decnode->children->lexeme); 

            if (rec == NULL)
            {
                printf("Enexpected error, record type definition not found\n");
            }
            else
            {
                recordField fieldhead = rec->head;

                while (fieldhead != NULL)
                {
                    // declaring a new variable for each field




                    // printf("\t%s%s:\tresd\t1\n", decnode->children->next->lexeme, fieldhead->lexeme);
                    fprintf(f, "\t%s%s:\tresd\t1\n", decnode->children->next->lexeme, fieldhead->lexeme);

                    fieldhead = fieldhead->next;
                }
            }

        }
        else{




             // printf( "\t%s:\tresd\t1\n", decnode->children->next->lexeme);
            fprintf(f, "\t%s:\tresd\t1\n", decnode->children->next->lexeme);
        }
           

        decnode = decnode->next;
    }

    int i = 0;

    for (i = 0; i < 14; i++)
    {
        // printf("\t%s:\tresd\t1\n", registers[i]);
        fprintf(f, "\t%s:\tresd\t1\n", registers[i]);
    }
}




int handleArithmetic(treenode arithexp, FILE* f, symbolTable stable, variable globalVarList,recordVar recList)
{

    int newtemp,lefttemp,righttemp;
    newtemp=counter_used;
    
    if(arithexp->id==140){
        counter_used=++counter_used%14;
        if (arithexp->children->next != NULL)
            {//record1.field=record2.field+record3.field;  or record1.field=record2.field+3
                char* var_name=(char*)malloc(sizeof(char)*50);

                strcpy(var_name,arithexp->children->lexeme);
                strcat(var_name,arithexp->children->next->next->lexeme);
                fprintf(f, "\n\tmov eax, [%s]", var_name);
                // fprintf(f, "\n\t%s eax, [%s]", operation, registers[righttemp]);
                fprintf(f, "\n\tmov [%s], eax\n", registers[newtemp]);
            }
            else
            {//c=b+3
               if(arithexp->children->id==5 || arithexp->children->id==6)
                    fprintf(f, "\n\tmov eax, %s", arithexp->children->lexeme);
                else
                     fprintf(f, "\n\tmov eax, [%s]", arithexp->children->lexeme);
                // fprintf(f, "\n\t%s eax, [%s]", operation, registers[righttemp]);
                fprintf(f, "\n\tmov [%s], eax\n", registers[newtemp]);
                
            }
        return newtemp;
        
    }
    char* operation=(char*)malloc(sizeof(char)*50);

    if (arithexp->id == 37)
            strcpy(operation,"add");
    else if(arithexp->id == 38)
            strcpy(operation,"sub");
    else if(arithexp->id == 39)
            strcpy(operation,"mul");
    else if(arithexp->id == 40)
            strcpy(operation,"div");

    // fprintf(f, "\n\tmov eax, [%s%s]", record1->lexeme, recfields->lexeme);
    lefttemp= handleArithmetic(arithexp->children, f,stable,globalVarList,recList);
    righttemp= handleArithmetic(arithexp->children->next, f,stable,globalVarList,recList);
    // printf("\n\t%s %s, %s", operation, registers[lefttemp], registers[righttemp]);
    // fprintf(f, "\n\t%s [%s], [%s]", operation, registers[lefttemp], registers[righttemp]);

    fprintf(f, "\n\tmov eax, [%s]", registers[lefttemp]);
    fprintf(f, "\n\t%s eax, [%s]", operation, registers[righttemp]);
    fprintf(f, "\n\tmov [%s], eax\n", registers[lefttemp]);
    // fprintf(f, "\n\tmov [%s%s], eax\n", assign_record->lexeme, recfields->lexeme);
    return lefttemp;



}




void handleAssignmentStmt(treenode assstmt, FILE* f, symbolTable stable, variable globalVarList,recordVar recList)
{
    // printf("Missing Feature: assign stmt code generation is not yet supported\n");
    treenode singlerec=assstmt->children;
    treenode arithexp=assstmt->children->next;
    // treenode arith = curr->firstKid->siblings;

     variable var=findIfDeclared(stable,"main",singlerec->children->lexeme,globalVarList);

    if (var==NULL)
    {
        printf("UNEXPECTED ERROR, Program seems to have semantic errors, cannot compile\n");
    }


    else
    {
        if (var->type == 22 ||var->type == 23 || singlerec->children->next != NULL)
        {            //record1.field=record2.field+record3.field;  or record1.field=record2.field+3 or c=b+3
            counter_used = 0;

            int ans = handleArithmetic(arithexp, f,stable,globalVarList,recList);
            // int ans=0;

            // reinitialize counter to 0
            counter_used = 0;

            // handling recordname.fieldname here
            if (singlerec->children->next != NULL)
            {//record1.field=record2.field+record3.field;  or record1.field=record2.field+3
                char* lhs=(char*)malloc(sizeof(char)*50);

                strcpy(lhs,singlerec->children->lexeme);
                strcat(lhs,singlerec->children->next->next->lexeme);

                move(lhs, registers[ans], f);
            }
            else
            {//c=b+3

                move(singlerec->children->lexeme, registers[ans], f);
            }
        }
        else
        {   //record1=record2+record3
            // as of now, it handles adding two records

            treenode record1 = arithexp->children->children;
            treenode assign_record = assstmt->children->children;
            treenode record2 = arithexp->children->next->children;

            char *operation;
            operation = (char *) malloc(10* sizeof(char));

            if (arithexp->id == 37)
                strcpy(operation,"add");
            else
                strcpy(operation,"sub");


            variable var=findIfDeclared(stable,"main",assign_record->lexeme,globalVarList);
            recordField recfields=findRecord(recList,var->recordName)->head;
                    while (recfields !=  NULL)
                    {
                        fprintf(f, "\n\tmov eax, [%s%s]", record1->lexeme, recfields->lexeme);
                        fprintf(f, "\n\t%s eax, [%s%s]", operation, record2->lexeme, recfields->lexeme);
                        fprintf(f, "\n\tmov [%s%s], eax\n", assign_record->lexeme, recfields->lexeme);

                        recfields = recfields->next;
                    }

        }
    }

}

void handleBoolean(treenode boolexp, FILE* f, int reverse){
    // printf("%d\n", pt->firstKid->id);
    int boolcount =globalcount;

    if(boolexp->children != NULL && (boolexp->children->id == 4 || boolexp->children->id == 5 || boolexp->children->id == 6)){ //boolexp->var relationalop var
        // pt = pt->firstKid;

        if(boolexp->children->id == 4){//tkid for var1
            fprintf(f, "\tmov eax, [%s]\n", boolexp->children->lexeme);
        }
        else{// num rnum
            fprintf(f, "\tmov eax, %s\n", boolexp->children->lexeme);
        }


        if(boolexp->children->next->id == 4){//for var2
            fprintf(f, "\tmov ebx, [%s]\n", boolexp->children->next->lexeme);
        }
        else{
            fprintf(f, "\tmov ebx, %s\n", boolexp->children->next->lexeme);
        }



        fprintf(f, "\tcmp eax, ebx\n\n");

        treenode relationalOp = boolexp;

        // printf("%d\t%d\n", relationalOp->id, reverse);
        // lt -> jge
        if(relationalOp->id == 48 && reverse == 0){
            fprintf(f, "\tjge else%d\n", boolcount);
        }
        else if (relationalOp->id == 48 && reverse == 1){
            fprintf(f, "\tjl else%d\n", boolcount);
        }
        else if (relationalOp->id == 48 && reverse == 2){
            fprintf(f, "\tjl then%d\n", boolcount);
        }
        else if(relationalOp->id == 48 && reverse == 3){
            fprintf(f, "\tjge then%d\n", boolcount);
        }


        // le ->jg
        else if(relationalOp->id == 49 && reverse == 0){
            fprintf(f, "\tjg else%d\n", boolcount);
        }
        else if (relationalOp->id == 49 && reverse == 1){
            fprintf(f, "\tjle else%d\n", boolcount);
        }
        else if (relationalOp->id == 49 && reverse == 2){
            fprintf(f, "\tjle then%d\n", boolcount);
        }
        else if(relationalOp->id == 49 && reverse == 3){
            fprintf(f, "\tjg then%d\n", boolcount);
        }

        //eq -> jne
        else if(relationalOp->id == 50 && reverse == 0){
            fprintf(f, "\tjne else%d\n", boolcount);
        }
        else if (relationalOp->id == 50 && reverse == 1){
            fprintf(f, "\tje else%d\n", boolcount);
        }
        else if (relationalOp->id == 50 && reverse ==2){
            fprintf(f, "\tje then%d\n", boolcount);
        }
        else if(relationalOp->id == 50 && reverse == 3){
            fprintf(f, "\tjne then%d\n", boolcount);
        }


        // gt -> jle
        else if(relationalOp->id == 51 && reverse == 0){
            fprintf(f, "\tjle else%d\n", boolcount);
        }
        else if (relationalOp->id == 51 && reverse == 1){
            fprintf(f, "\tjg else%d\n", boolcount);
        }
        else if (relationalOp->id == 51 && reverse == 2){
            fprintf(f, "\tjg then%d\n", boolcount);
        }
        else if(relationalOp->id == 51 && reverse == 4){
            fprintf(f, "\tjle then%d\n", boolcount);
        }

        // ge -> jl
        else if(relationalOp->id == 52 && reverse == 0){
            fprintf(f, "\tjl else%d\n", boolcount);
        }
        else if (relationalOp->id == 52 && reverse == 1){
            fprintf(f, "\tjge else%d\n", boolcount);
        }
        else if (relationalOp->id == 52 && reverse == 2){
            fprintf(f, "\tjge then%d\n", boolcount);
        }
        else if (relationalOp->id == 52 && reverse == 3){
            fprintf(f, "\tjge then%d\n", boolcount);
        }

        //ne -> je
        else if(relationalOp->id == 53 && reverse == 0){
            fprintf(f, "\tje else%d\n", boolcount);
        }
        else if (relationalOp->id == 53 && reverse == 1){
            fprintf(f, "\tjne else%d\n", boolcount);
        }
        else if (relationalOp->id == 53 && reverse == 2){
            fprintf(f, "\tjne then%d\n", boolcount);
        }
        else if(relationalOp->id == 53 && reverse == 3){
            fprintf(f, "\tje then%d\n", boolcount);
        }


    }

    else if(boolexp->id == 47){//boolexp->not boolexp 
        boolexp=boolexp->children;
        if (reverse == 2)
            handleBoolean(boolexp, f, 3);
        else
            handleBoolean(boolexp, f, 1);
    }
    else {//boolexp->boolexp logicalop boolexp
        treenode bool1 = boolexp->children;
        treenode logop = boolexp;
        treenode bool2 = bool1->next;


        if(logop->id == 45){
            handleBoolean(bool1, f, 0);
            handleBoolean(bool2, f, 0);
        }
        else{
            handleBoolean(bool1, f, 2);
            handleBoolean(bool2, f, 0);
        }

    }

}

void handleIterativeStmt(treenode iterstmt, FILE* f, symbolTable stable, variable globalVarList,recordVar recList)
{   
    globalcount+=1;
    int while_count = globalcount;
    
    // treenode tk_while = curr->firstKid;
    treenode boolexp = iterstmt->children;
    treenode stmts = iterstmt->children->next;

    fprintf(f, "\tparent%d:\n", while_count);


    handleBoolean(boolexp, f, 0);

    handleStmt(stmts ,f, stable, globalVarList, recList);

    fprintf(f, "\tjmp parent%d\n", while_count);

    fprintf(f, "\telse%d:\n", while_count);
}



void handleConditionalStmt(treenode condstmt, FILE* f, symbolTable stable, variable globalVarList,recordVar recList)
{
    globalcount +=1;

    int boolcount = globalcount;

    treenode booleanExp = condstmt->children;

    treenode stmt = booleanExp->next;

    treenode elsepart=stmt;

    while(elsepart->next!=NULL){
        elsepart=elsepart->next;
    }


    handleBoolean(booleanExp, f, 0);

    fprintf(f, "\tthen%d:\n", boolcount);

    handleStmt(stmt, f, stable,globalVarList,recList);

    fprintf(f, "\tjmp end%d\n", boolcount);


    if(elsepart->children ==NULL){//no else stmts

        fprintf(f, "\telse%d:\n", boolcount);
    }
    else{

        fprintf(f, "\telse%d:\n", boolcount);
        stmt = elsepart->children;
        handleStmt(stmt, f, stable,globalVarList,recList);
    }

    fprintf(f, "\tend%d:\n\n",boolcount);


}




// TODO ask user to report unexpected errors to compiler developers
void handleStmt(treenode stmt, FILE* f, symbolTable stable, variable globalVarList,recordVar recList)
{
    while( stmt!= NULL&&stmt->id!=130)
    {

        if (stmt->children->id == 35 || stmt->children->id == 34){ // io statement
            handleIOstmt(stmt, f, stable,globalVarList,recList);
        }
        else if (stmt->children->id == 122) // assignment statement
            handleAssignmentStmt(stmt->children, f, stable,globalVarList,recList);
        else if(stmt->children->id == 128) // iterative statement: (while) might have to recursively call the  handleStmts functions while handling iterative statments
            handleIterativeStmt(stmt->children, f, stable,globalVarList,recList);
        else  if (stmt->children->id == 129) // conditional statement
            handleConditionalStmt(stmt->children, f, stable,globalVarList,recList);

        stmt = stmt->next;
    }
}




void CodeGeneration(treenode ast,symbolTable stable,variable globalVarList,recordVar recList, char* fname)
{
    // Opening file for writing in the assembly code
    FILE *output = fopen(fname, "wb");

    // given that code files will only have one function: the _main function

    treenode main = ast->children->next;
    // printf("mf id: %d\n", mf->id);

    treenode typedefinitions = main->children->children;

    // TODO <psdh> handle type definitions here

    treenode decl = typedefinitions->next;


    char data_section[] = "\nsection .data\n\tnumberin_form:\tdb \"%d\",0\n\n\tnumberout_form:\tdb \"%d\",10,0\n";
    fprintf(output, "%s", data_section);


    handleDeclarations(decl->children,output,stable,globalVarList,recList);

    char global_start[] = "section .text\n\tglobal main\n\textern scanf\n\textern printf";
    fprintf(output, "%s", global_start);

    fprintf(output, "\nmain:");
// handling stmt's  now
    handleStmt(decl->next->children, output,stable,globalVarList,recList);
    rewind(output);
    fclose(output);
}

void clearvars(){
    counter_used = 0, globalcount=0;
}

//nasm -f elf64 code.asm
//gcc code.o -o code
// ./code
