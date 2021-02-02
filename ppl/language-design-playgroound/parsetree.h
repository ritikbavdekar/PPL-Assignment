#include "typeinfo.h"
#include "grammar.h"
#include "linkedlist.h"

#ifndef structures_h
#define structures_h
#include "structures.h"
#endif

parseTree* createEmptyParseTree();

parseTreeNode* createNode(char* symbol,tokenStreamNode* t);

void createChildren (parseTreeNode* n, int i,grammar* g);

void deleteChildren(parseTreeNode* n);

void printParsePrettyUtil(parseTreeNode* n,int space);

void printParseTreePretty(parseTree* tree);

void printParseTree(parseTree* tree);
void printParseUtil(parseTreeNode* root);

void printParseTreeNode(parseTreeNode* n);
parseTreeNode* PreOrderSuccessor(parseTree* tree,parseTreeNode* node);
void PreOrderSuccessorUtil(parseTreeNode* node,int *flag,parseTreeNode** next);

parseTreeNode* createDummyNode(char* symbol);