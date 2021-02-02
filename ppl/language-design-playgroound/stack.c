#include "stack.h"
#include "utils.h"

#ifndef structures_h
#define structures_h
#include "structures.h"
#endif

stack* createStack()
{
	stack* newStack = (stack*) malloc(sizeof(stack));
	newStack->top = NULL;
	newStack->count = 0;
	return newStack;
}

stackNode* createStackNode(char* str)
{
	stackNode* newnode = (stackNode*) malloc (sizeof(stackNode));
	
	newnode->symbol = str;
	newnode->isTerminal = !(str[0] == '<');
	newnode->next = NULL;

	return newnode;
}

void push(stack* s, stackNode* n)
{
	n->next = s->top;
	s->top = n;
	s->count++;
}

stackNode* pop(stack* s)
{
	if(s->count == 0)
		return NULL;

	stackNode* temp = s->top;
	s->top = temp->next;
	s->count--;

	return temp;
}

void printStackNode(stackNode* node)
{
	printf("symbol: %s, isTerminal: %d \n", node->symbol, (int)node->isTerminal);
}

void printStack(stack* s)
{
	stackNode* temp = s->top;
	int count = 0;
	while(temp)
	{
		printf("stack element #%d:\n", count++);
		printStackNode(temp);
		temp = temp->next;
		printf("\n");
	}
}

stackNode* ruleReplace(stack* s, struct grammar* g, int i, int* count)
{
	stackNode* top = pop(s);

	node* temp = g->rules[i]->right->head;
	stack* buffer = createStack();

	while(temp)
	{
		stackNode* newnode = createStackNode(temp->data);
		push(buffer, newnode);
		temp = temp->next;
		(*count)++;
	}

	stackNode* curr = pop(buffer);

	while(curr)
	{
		push(s, curr);
		curr = pop(buffer);
	}

	return top;
}

void undoRuleReplace(stack* s, stackNode* n, int count)
{
	for(int i=0; i<count; i++)
		pop(s);
	push(s, n);
}