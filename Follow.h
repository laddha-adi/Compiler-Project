#ifndef FOLLOW
#define FOLLOW

#include "hash.h"
#include "First.h"
typedef dl grammarRules;
typedef ll singleRule;

void addFollow(grammarRules gr, hashtable ht);
void readFollow(char* fileName, grammarRules gr, hashtable ht);

#endif
