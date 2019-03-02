#include <stdio.h>

int MEM = 0;
int flag = 0;

void addMem(int mem, char* str){
	MEM += mem;
	if(flag ==1) {
		printf("Allocating %d bytes in %s \t Total Allocated Memory = %d \n", mem, str, MEM);
	}
}

void freeMem(int mem, char* str){
	MEM -= mem;
	if(flag ==1) {
		printf("Allocating %d bytes in %s \t Total Allocated Memory = %d \n", mem, str, MEM);
	}
}

void printMem(int a){
	flag = a;
}
