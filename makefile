
# GROUP NUMBER: 11
# NIKKI GUPTA 2016A7PS0057P
# SAHIL RANADIVE 2016A7PS0097P
# ADITI AGARWAL 2016A7PS0095P
# ADITYA LADDHA 2016A7PS0038P

CC=gcc

compiler: driver.c parser.c lexer.c ast.c symboltable.c typechecker.c semanticanalyzer.c codegen.c
	gcc -o compiler -g driver.c parser.c lexer.c ast.c symboltable.c typechecker.c semanticanalyzer.c codegen.c
