#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

typedef dl grammarRules;
typedef ll singleRule;

dl readFile(char * fileName, hashtable* ht);
grammarRules insertRule(grammarRules gRules, singleRule sRule);
hashtable* insertAllRulesInHash(grammarRules gr, hashtable* ht);
void addGrammarRule(element e, ll l);
void addFirst(grammarRules gr, hashtable* ht);
ll getFirst(element e, hashtable* ht);