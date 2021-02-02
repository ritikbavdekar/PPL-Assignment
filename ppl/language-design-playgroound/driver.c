#include "utils.h"
#include "lexer.h"
#include "stack.h"
#include "grammar.h"
#include "linkedlist.h"
#include "parsetree.h"
#include "typeinfo.h"
#include "parser.h"
#include "typeexpressiontable.h"

int main()
{
	createCache();
	printf("main");
	struct grammar* g;
	char grammar_file[] = "grammar.txt";
	readGrammar(grammar_file, &g);
	// printGrammar(g);

	cleanWhiteSpaces("testcases/t2.txt");
	tokenStream* s = createEmptyTokenStream();
	char source_file[] = "processed.txt";
	tokeniseSourcecode(source_file, s);

	// printf("main\n");
	// printTokenStream(s);

	parseTree* tree = createEmptyParseTree();
	// tree->root=createDummyNode("Hola");
	// createChildren (tree->root, 2, g);
	// printParseTreePretty(tree);
	// parseTreeNode** c=tree->root->children;
	// createChildren (c[0], 4, g);
	// createChildren(c[1],2,g);
	// printParseTreePretty(tree);
	// deleteChildren(tree->root);
	// printParseTreePretty(tree);



	createParseTree(tree, s, g);
	// printParseTree(tree);
	typeExpressionTable* table=createTable();
	// printf("%d",tree);
	populateTable(tree,table);
	printf("%d ",table->size);
	printTypeExpressionTable(*table);


}