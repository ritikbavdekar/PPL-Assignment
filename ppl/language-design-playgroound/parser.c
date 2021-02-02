#include "parser.h"
#include "stack.h"
#include "utils.h"

void createParseTree(parseTree* t, tokenStream* s, grammar* g)
{

	stack* st = createStack();

	push(st, createStackNode("<program>"));

	tokenStreamNode* ptr = s->head;

	int k = 0;

	t->root = createDummyNode("<program>");
	// printf("*******inside createParseTree ***************\n");
	
	// printf("*******inside createParseTree ***************\n");

	// printf("inside createParseTree\n");

	buildParseTree(&ptr, t, t->root, st, g, &k);


}

bool buildParseTree(tokenStreamNode** ptr, parseTree* tree, parseTreeNode* root, stack* st, grammar*g, int* k)
{

	tokenStreamNode* buffer;

	if(*ptr == NULL && st->count == 0)
		return true;

	// printf("=====================================================\n");
	// printParseTreePretty(tree);
	// printf("k = %d\n", *k);
	// printStack(st);
	// printToken(*ptr);

	stackNode* top = st->top;
	// printf("%s\n", top->symbol);
	if(!(top->isTerminal) && 
		!(strcmp(top->symbol, "<var_name>") == 0)
		&& !(strcmp(top->symbol, "<const>") == 0))
	{
		// printf("working\n");
		int start, count;
		getNTCache(top->symbol, &start, &count);

		for(int i=start; i<start+count; i++)
		{
			buffer = *ptr;
			int c = 0;
			// printf("the top of the stack is:\n");
			// printStackNode(top);
			ruleReplace(st, g, i, &c);
			createChildren(root, i, g);
			// printf("top of stack is, %s\n", st->top->symbol);
			// printf("this non terminal was replaced with %d tokens.\n", c);

			if(buildParseTree(ptr, tree, PreOrderSuccessor(tree,root), st, g, &c))
				return true;

			deleteChildren(root);
			*ptr = buffer;
			undoRuleReplace(st, top, c);
		}

		return false;
	}

	else
	{
		// printf("terminal\n");
		int t;
		// printf("inside buildParseTree\n");
		identify_token((*ptr)->lexeme, &t);
		// printf("%s %s %d\n", (*ptr) -> lexeme, top->symbol, t);

		if(strcmp((*ptr)->lexeme, top->symbol) == 0 ||
			(t == 27 && strcmp(top->symbol, "<var_name>") == 0) ||
			(t == 28 && strcmp(top->symbol, "<const>") == 0))
		{
			buffer = *ptr;
			*ptr = (*ptr)->next;
			stackNode* temp = pop(st);
			(*k)--;
			// createChildren(root, i, g);
			if(t == 27 || t == 28)
			{

				root->children=(parseTreeNode**)(malloc(sizeof(parseTreeNode *)));
				root->children[0]=createDummyNode(buffer->lexeme);
				root->num_children=1;
				root=root->children[0];
				// root->lexeme=(*ptr)->lexeme;

			}

			if(buildParseTree(ptr, tree, PreOrderSuccessor(tree,root), st, g, k))
				return true;

			*ptr = buffer;

			push(st, temp);
			(*k)++;
			// deleteChildren(root);
			
			return false;
		}


		else 
		{
			// printf("%s \n", (*ptr)->lexeme);
			// printf("not matching\n");

			return false;
		}
	}
}








































// void createParseTree(parseTree* t, tokenStream* s, grammar* g)
// {

// 	stack* st = createStack();
// 	char start[] = "<program>";
// 	stackNode* n = createStackNode(start);
// 	push(st, n);

// 	// parseTreeNode* root = createParseTreeNode(start);
// 	// setRoot(t, root);

// 	tokenStreamNode* ptr = getHead(s);
// 	int k = 0;

// 	buildParseTree(ptr, st, g, &k)
// }

// bool buildParseTree(tokenStream* ptr, stack* st, grammar*g, int* k)
// {
// 	// <program> --> ....
// 	if(!ptr && !st)
// 		return true;

// 	if(!ptr || !st)
// 		return false;

// 	while(getCount(st) != 0)
// 	{
// 		char top[] = getTop(st);

// 		if(!getIsTerminal(top))
// 		{
// 			int start, count;
// 			getStartAndCount(top, &start, &count);

// 			for(int i=start; i<start+count; i++)
// 			{
// 				int num_children = 0;
// 				stackNode* buffer = ruleReplace(st, g, i, &num_children);

// 				// parseTreeNode* root = createParseTreeNode(buffer);
// 				createChildren(root, i, g);

// 				if (!(buildParseTree(pt,r st, g, &num_children)))
// 				{
// 					// deleteChildren(root);
// 					undoRuleReplace(st, buffer, num_children);
// 				}

// 			}
// 		}

// 		else
// 		{
// 			if(strcmp(top, getLexeme(ptr)) == 0)
// 			{
// 				pop(st);
// 				ptr = getNext(ptr);
// 				(*k)--;
// 			}	

// 			else
// 				return false;	
// 		}
// 	}

// }