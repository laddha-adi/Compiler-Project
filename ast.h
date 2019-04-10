#ifndef AST
#define AST

#include "lexer.h"
#include "parser.h"

void copynode(treenode currentnode,treenode temp);
treenode createAST(treenode parseTree);

#endif