#include <stdio.h>
#include "tokenlinkedlist.h"
#include <stdlib.h>


linkedlist* GenereateTokenLinkedList()
{
	linkedlist* ll= (linkedlist*) malloc(sizeof(linkedlist));
	ll->head=NULL;
	ll->count=0;
	return ll;
}


tokenStreamNode* genereateNode(token t_name,char lexeme[],int line_number)
{
	tokenStreamNode* t= (tokenStreamNode*) malloc(sizeof(tokenStreamNode));
	t->token_name=t_name;
	t->lexeme=lexeme;
	t->line_number=line_number;
	t->next=NULL;
	return t;
}

void addTokenLinkedList(linkedlist* ll,token t_name,char lexeme[],int line_number)
{
	tokenStreamNode* FinalNode=genereateNode(t_name,lexeme,line_number);
	if(ll->count==0)
	{
		ll->head=FinalNode;
		return ll;
	}
	tokenStreamNode* temp=ll->head;
	while(temp->next)
	{
		temp=temp->next;
	}
	temp->next=FinalNode;
	ll->count++;
	return;
}