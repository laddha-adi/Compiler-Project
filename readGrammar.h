#ifndef READ_GRAMMAR
#define READ_GRAMMAR

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "First.h"
#include "Follow.h"

typedef dl grammarRules;
typedef ll singleRule;

dl readFile(char * fileName, hashtable* ht);
grammarRules insertRule(grammarRules gRules, singleRule sRule);
void insertAllRulesInHash(grammarRules gr);
void addGrammarRule(element e, ll l);
//void addFirst(grammarRules gr, hashtable* ht);
//ll getFirst(element e, hashtable* ht);

#endif