#include "tokenstream.h"
#include "parsetree.h"
#include "stack.h"
#include "grammar.h"
#include "utils.h"
#ifndef structures_h
#define structures_h
#include "structures.h"
#endif

void createParseTree(parseTree* t, tokenStream* s, grammar* g);
bool buildParseTree(tokenStreamNode** ptr, parseTree* tree, parseTreeNode* root, stack* st, grammar*g, int* k);

