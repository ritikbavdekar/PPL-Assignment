#include "utils.h"
#include "parsetree.h"
#include <strings.h>

int counter = 1;

parseTree* createEmptyParseTree()
{
	parseTree* t = (parseTree*)malloc(sizeof(parseTree));
	t->root = NULL;
	return t;
}

parseTreeNode* createNode(char* symbol,tokenStreamNode * t)
{
	parseTreeNode* temp = (parseTreeNode* )malloc(sizeof(parseTreeNode));
	temp->symbol = symbol;
	temp->tag=~isTerminal(symbol);
	temp->lexeme = t->lexeme;
	temp->line_number = t->line_number;
	temp->children=NULL;
	temp->num_children=0;
	// temp->type=NULL;
	temp->depth = 0;
	temp->rule_index = -1;
	return temp;
}

parseTreeNode* createDummyNode(char* symbol)
{
	parseTreeNode* temp = (parseTreeNode* )malloc(sizeof(parseTreeNode));
	temp->symbol = symbol;
	temp->tag=~isTerminal(symbol);
	temp->children=NULL;
	temp->num_children=0;
	// temp->type=NULL;
	temp->depth =         0;
	temp->rule_index = -1;
	temp->line_number=-1;
	temp->lexeme=(char *)(malloc(sizeof(char)*2));
	strcpy(temp->lexeme,"N");
	return temp;
}


void createChildren (parseTreeNode* n, int i,grammar* g)
{
	rule* r=getRules(g)[i];
	linkedList* ll=getRight(r);
	node* temp = ll->head;
	n->num_children=0;
	while(temp)
	{
		// parseTreeNode* child=createNode(temp->data);
		n->num_children++;
		temp = temp->next;
	}
	temp = ll->head;
	n->children=(parseTreeNode**)malloc(sizeof(parseTreeNode*) * (n->num_children));
	int index=0;
	while(temp)
	{
		parseTreeNode* child=createDummyNode(temp->data);
		child->depth=n->depth+1;
		n->children[index]=child;
		temp=temp->next;
		index++;
	}
	return ;
}

void deleteChildren(parseTreeNode* n)
{
	if(n==NULL) return;
	// n->children=NULL;
	// n->num_children=0;
	for(int i=0;i<(n->num_children);i++)
	{
		parseTreeNode* child= n->children[i];
		deleteChildren(child);
		free(child);
	}
	n->num_children=0;
	return;
}

void printParseTreeNode(parseTreeNode* n)
{
	printf("\n");
	printf("%-4d", counter);
	printf(" %-25s", n->symbol );


	if(isTerminal(n->symbol))
	{
		printf(" %-35s","terminal");
		printf(" %-30s", "#######");
		printf(" %-15s", n->lexeme);
		printf(" %8d", n->line_number);
		printf(" %10s", "#######");
	}

	else
	{
		//add type expression print functionality
		printf(" %-35s","non terminal");
		printf(" %-30s", "insert type expression.");
		printf(" %-15s", "#######");
		printf(" %8s", "#######");
		printf(" %10d", n->rule_index);
	}

	printf(" %8d\n", n->depth);
	return;
}


void printParsePrettyUtil(parseTreeNode* n,int space)
{
	if(n==NULL) return;
	for(int i=0;i<space;i++)
	{
		printf(" ");
	}
	printf("%s \n",n->symbol);

	for(int i=0;i<n->num_children;i++)
	{
		printParsePrettyUtil(n->children[i],space+4);
	}
	return ;
}


void printParseTreePretty(parseTree* tree)
{
	printParsePrettyUtil(tree->root,0);
	return ;
}

void printParseUtil(parseTreeNode* root)
{
	if(root==NULL) return;
	printParseTreeNode(root);
	counter++;
	for(int i=0;i<root->num_children;i++)
	{
		printParseUtil(root->children[i]);
	}
	return ;
}

void printParseTree(parseTree* tree) ///inorder traversal
{
	printf("%-4s %-25s %-35s %-30s %-15s %8s %10s %8s\n", "S.No","Symbol Name", "Terminal/Non-Terminal", "Type Expression", "Name of Lexeme", "Line No", "Grammar Rule", "Depth of node");
	printParseUtil(tree->root);
	printf("\n ------------------------------------------ \n ");
	return;
}

void PreOrderSuccessorUtil(parseTreeNode* node,int *flag,parseTreeNode** next)
{
	if(node==NULL) return;
	if(node->num_children==0 && !isTerminal(node->symbol) && *flag==0 && strcmp(node->symbol,"<epsilon>")!=0)
	{
		*flag=1;
		*next=node;
		return;
	}

	for(int i=0;i<node->num_children;i++)
	{
		PreOrderSuccessorUtil(node->children[i],flag,next);
	}
	return ;

}

parseTreeNode* PreOrderSuccessor(parseTree* tree,parseTreeNode* node)
{
	if(!isTerminal(node->symbol) && node->num_children!=0)
	{
		return node->children[0];
	}
	parseTreeNode* next=NULL;
	int flag=0;
	PreOrderSuccessorUtil(tree->root,&flag,&next);
	return next;
}

void printTest(parseTree* tree)
{

}


