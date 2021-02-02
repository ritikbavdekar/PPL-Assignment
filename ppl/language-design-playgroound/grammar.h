#include "linkedlist.h"

#ifndef structures_h
#define structures_h
#include "structures.h"
#endif


struct linkedList* getRight(struct rule* r);
struct rule** getRules(struct grammar* g);
struct rule* createRule(char* line);
void readGrammar(char* filename, struct grammar** G);
void printRule(struct rule* r);
void printGrammar(struct grammar* g);
