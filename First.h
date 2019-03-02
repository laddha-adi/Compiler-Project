#ifndef FIRST
#define FIRST

// #include "readGrammar.h"
#include "hash.h"
#include <string.h>

typedef dl grammarRules;

void addFirst(grammarRules gr, hashtable ht);
ll getFirst(element e, hashtable ht);
ll getRecursiveFirst(node n, hashtable ht, node self);
ll removeEps(ll l);
#endif