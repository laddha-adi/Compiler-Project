output: driver.o 
	gcc -w -O3 driver.o -o compiler

lexer.o: lexer.h lexer.c 
	gcc -w -c -g lexer.c

parser.o: parser.h parser.c 
	gcc -w -c -g parser.c

driver.o: driver.c
	gcc -w -c -g driver.c
clean:
	rm *.o