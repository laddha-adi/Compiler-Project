
int MEM = 0;
int printMEM = 0;

void addMem(int mem, char* str){
	MEM += mem;
	if(printMEM ==1) {
		printf("Allocating %d bytes in %s\n \t Total Allocated Memory = %d", mem, str, MEM);
	}
}

void freeMem(int mem, char* str){
	MEM -= mem;
	if(printMEM ==1) {
		printf("Allocating %d bytes in %s\n \t Total Allocated Memory = %d", mem, str, MEM);
	}
}