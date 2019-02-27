#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

typedef dl grammarRules;
typedef ll singleRule;

dl readFile(char * fileName, hashtable* ht);
grammarRules insertRule(grammarRules gRules, singleRule sRule);
hashtable* insertAllRulesInHash(grammarRules gr, hashtable* ht);


