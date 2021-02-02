#include "utils.h"
#include "tokenstream.h"

tokenStream* createEmptyTokenStream()
{
	tokenStream* s= (tokenStream*) malloc(sizeof(tokenStream));
	s->head=NULL;
	s->count=0;
	return s;
}


tokenStreamNode* createTokenStreamNode(token_idx i, char* lexeme, int line_number)
{
	tokenStreamNode* t = (tokenStreamNode*) malloc(sizeof(tokenStreamNode));

	t->id = i;
	t->lexeme = (char*)malloc(strlen(lexeme) * sizeof(char));
	strcpy(t->lexeme, lexeme);
	t->line_number = line_number;
	t->next = NULL;

	return t;
}

void addToken(tokenStream* t, tokenStreamNode* node)
{
	if(t->count==0)
	{
		t->head = node;
		t->count++;
		return;
	}
	// printToken(node);

	tokenStreamNode* temp = t->head;

	while(temp->next)
	{
		temp=temp->next;
	}

	temp->next = node;
	t->count++;
}

void printToken(tokenStreamNode* node)
{
	printf("Lexeme: %s, Token id: %d, Line number: %d\n", node->lexeme, node->id, node->line_number);
}

void printTokenStream(tokenStream* t)
{
	tokenStreamNode* temp = t->head;
	// int n = 0;
	while(temp)
	{
		// n++;
		// printf("printtokenstream %d\n", n);
		printToken(temp);
		temp = temp->next;
	}
}

