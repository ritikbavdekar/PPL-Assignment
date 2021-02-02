#include <stdio.h>
#include "token.h"
typedef struct tokenStreamNode{
	token token_name;
	 char lexeme[];
	 int line_number;
	struct tokenStreamNode* next;
}tokenStreamNode;

typedef struct linkedlist{
	int count;
	tokenStreamNode* head;
}linkedlist;

void addTokenLinkedList(linkedlist* ll,token t_name,char lexeme[],int line_number);
linkedlist* GenereateTokenLinkedList();
