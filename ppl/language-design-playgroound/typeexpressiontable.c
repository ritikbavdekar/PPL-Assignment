#include "typeexpressiontable.h"

#ifndef structures_h
#define structures_h
#include "structures.h"
#endif
#include <string.h>
#include <stdlib.h>


typeExpressionTable* createTable()
{
	typeExpressionTable* temp_table=(typeExpressionTable *)malloc(sizeof(typeExpressionTable));
	temp_table->size=0;
	return temp_table;
}

void addTableEntry(typeExpressionTable* table,parseTreeNode* var)
{
	typeExpressionTableEntry* entry = (typeExpressionTableEntry*)malloc(sizeof(typeExpressionTableEntry));
	entry->variable_name=var->symbol;  ///need to allocate memory. Not sure :(
	entry->te=NULL;
	(table->entries)[table->size-1]=entry;
	return ;
}

void find_variables(parseTreeNode* root,typeExpressionTable* table)
{
	if(root==NULL) return;
	if(strcmp(root->symbol,"<var_name>")==0)
	{
		table->size++;
		addTableEntry(table,root->children[0]);
		return;
	}
	for(int i=0;i<root->num_children;i++)
	{
		find_variables(root->children[i],table);
	}
	return ;

}


void fillEntryJagged(typeExpressionTableEntry* entry, parseTreeNode* root)
{
	entry->te->j.typeExp_type=(char *)malloc(sizeof("jaggedArray"));
	entry->te->j.typeExp_type="jaggedArray";
	root=root->children[1];//move from <dec_jagged> to <decs_jagged>
	root=root->children[(root->num_children)-1]; // move to <jagged_array>
	parseTreeNode* temp=root->children[1]; //move to <jagged_array_B>
	temp=temp->children[0]; //move to <jagged_dim>
	temp=temp->children[0] ;// move to <2d> or <3d>
	if(strcmp(temp->symbol,"<2d>")==0)
	{
		entry->te->j.dimensions=2;
	}
	else
	{
		entry->te->j.dimensions=3;
	}
	temp=root; //<jagged_array>
	temp=root->children[0]; //<jagged_array_A>
	parseTreeNode* temp1=temp->children[3];
	temp1=temp1->children[0];
	parseTreeNode* temp_iterator;
	if(isdigit((temp1->symbol[0])))
	{
		entry->te->j.range1[0]=atoi(temp1->symbol);
	}
	else
	{
		entry->te->j.range1[0]=-1;
	}
	temp1=temp->children[5];
	temp1=temp1->children[0];
	// printf("%s",temp1->symbol);
	if(isdigit((temp1->symbol[0])))
	{
		entry->te->j.range1[1]=atoi(temp1->symbol);
	}
	else
	{
		entry->te->j.range1[1]=-1;
	}
	entry->te->j.basicElementType=(char *)malloc(sizeof("integer"));
	entry->te->j.basicElementType="integer";
	if(entry->te->j.dimensions==2)             ///need to still populate 2d head
	{
		entry->te->j.r2.head_2d=(twoDNode*)malloc(sizeof(twoDNode));
		entry->te->j.r2.head_2d->next=NULL;
		temp=root->children[1];  //to <jagged_array_B>;
		temp=temp->children[4];  //<sub_dim_list>
		temp_iterator=temp->children[1];
		temp=temp->children[0]; //<sub_dim>
		twoDNode* twoNodePointer=entry->te->j.r2.head_2d;
		int counter=entry->te->j.range1[1]-entry->te->j.range1[0];
		// printf("%s",temp_iterator->symbol);
		while(strcmp(temp_iterator->symbol,"<epsilon>")!=0)
		{
			temp=temp->children[0]; ///<sub_dim_A>
			temp=temp->children[6] ;//<const>
			int size=atoi((temp->children[0])->symbol);
			twoNodePointer->size_value=size;
			if(counter) 
				{twoNodePointer->next= (twoDNode*) malloc(sizeof(twoDNode));
					counter--;
				}
			else
			{
				twoNodePointer->next=NULL;
			}
			twoNodePointer=twoNodePointer->next;
			temp=temp_iterator->children[0];
			temp_iterator=temp_iterator->children[(temp_iterator->num_children)-1];
		}

		// entry->te->j.range2.head_2d

	}
	else
	{
		// entry->te->j.range2.head_3d              ///need to still populate 3d head

	}

	return;



}

void fillEntryRect(typeExpressionTableEntry* entry, parseTreeNode* root,int * isStat)//root is <nonjaggedtype>
{
	entry->te->r.typeExp_type=(char *)malloc(sizeof("rectangularArray"));
	entry->te->r.typeExp_type="rectangularArray";
	root=root->children[0];
	parseTreeNode* temp=root->children[1]; //<dimnesions>
	int count=0;
	// printf("%s",temp->symbol);
	while(temp->num_children >1)
	{
		count++;
		temp=temp->children[temp->num_children - 1];
	}
	entry->te->r.dimensions=count;
	entry->te->r.basicElementType=(char *)malloc(sizeof("integer"));
	entry->te->r.basicElementType="integer";
	entry->te->r.head=(rect_range_node*)malloc(sizeof(rect_range_node));
	rect_range_node* rectPointer=entry->te->r.head;
	count=count-1;
	temp=root->children[1];//<dimensions>
	while(temp->num_children>1)
	{
		parseTreeNode* index_low=temp->children[1];
		index_low=index_low->children[0];
		if(strcmp(index_low->symbol,"<var_name>")==0)
		{
			*isStat=0;
			rectPointer->low=-1;
		}
		else
		{
			rectPointer->low=atoi(index_low->children[0]->symbol);
		}
		parseTreeNode* index_high=temp->children[3];
		index_high=index_high->children[0];
		if(strcmp(index_high->symbol,"<var_name>")==0)
		{
			*isStat=0;
			rectPointer->hi=-1;
		}
		else
		{
			rectPointer->hi=atoi(index_high->children[0]->symbol);
		}
		if(count>0)
		{	rectPointer->next=(rect_range_node*)malloc(sizeof(rect_range_node));
			count--;
		}
		else
		{
			rectPointer->next=NULL;
		}
		rectPointer=rectPointer->next;
		temp=temp->children[temp->num_children - 1 ];
	}
	return ;

}


void updateTableExpression(int tag,typeExpressionTable* table,parseTreeNode* root)
{
	for(int i=0;i<(table->size);i++)
	{
		typeExpressionTableEntry* entry = table->entries[i];
		if(entry->te!=NULL) continue;
		else
		{
			if(tag==0)
			{
				entry->t=jagged;
				entry->stat=static_var;
				entry->te=(typeExpression *)malloc(sizeof(typeExpression));
				fillEntryJagged(entry,root);
			}
			else if(tag==1)
			{
				entry->t=primitive;
				entry->stat=static_var;
				entry->te=(typeExpression *)malloc(sizeof(typeExpression));
				entry->te->p.basicElementType=(char *)malloc(sizeof("integer"));
				entry->te->p.basicElementType="integer";
			}
			else if(tag==2)
			{
				entry->t=primitive;
				entry->stat=static_var;
				entry->te=(typeExpression *)malloc(sizeof(typeExpression));
				entry->te->p.basicElementType=(char *)malloc(sizeof("boolean"));
				entry->te->p.basicElementType="boolean";
			}
			else if(tag==3)
			{
				entry->t=primitive;
				entry->stat=static_var;
				entry->te=(typeExpression *)malloc(sizeof(typeExpression));
				entry->te->p.basicElementType=(char *)malloc(sizeof("real"));
				entry->te->p.basicElementType="real";
			}
			else
			{
				entry->t=rectangular;
				entry->stat=static_var;
				entry->te=(typeExpression *)malloc(sizeof(typeExpression));
				int isStat=1;
				fillEntryRect(entry, root,&isStat);
				if(isStat!=1)
				{
					entry->stat=dyn;

				}
			}
		}
			// printf("variable name : %s variable_type : %d tag: %d \n",entry->variable_name,entry->t,tag);
		
	}
	return ;


}

void findVariableType(parseTreeNode* root,typeExpressionTable* table)
{
	int temp_tag=-1;
	if(strcmp(root->children[0]->symbol,"<dec_jagged>")==0)
	{
		temp_tag=0; ///tag=0 for jagged array                
		updateTableExpression(temp_tag,table,root->children[0]);
	}
	else
	{
		root=root->children[0]; //reaching <dec_nonjagged>
		root=root->children[1]; // reaching <decs_nonjagged>
		int index=0;
		while(strcmp(root->children[index]->symbol,"<non_jagged_type>")!=0)
		{
			index++;
		}
		root=root->children[index]; //reaching <non_jagged_type>
		if(strcmp(root->children[0]->symbol,"<k_integer>")==0)
		{
			temp_tag=1;
			updateTableExpression(temp_tag,table,root->children[0]);

		}
		else if(strcmp(root->children[0]->symbol,"<k_boolean>")==0)
		{
			temp_tag=2;
			updateTableExpression(temp_tag,table,root->children[0]);

		}
		else if(strcmp(root->children[0]->symbol,"<k_real>")==0)
		{
			temp_tag=3;
			updateTableExpression(temp_tag,table,root->children[0]);

		}
		else
		{
			temp_tag=4; //rectangular array
			updateTableExpression(temp_tag,table,root);
		}
	}
	return;

}



void traverse_tree(parseTreeNode* root,typeExpressionTable* table)
{
	if(root==NULL) return;
	if(strcmp(root->symbol,"<dec>")==0)
	{
		find_variables(root,table);
		findVariableType(root,table);
		return;
	}
	for(int i=0;i<root->num_children;i++)
	{
		traverse_tree(root->children[i],table);
	}
	return ;
}

void count_subtree_vars(parseTreeNode* root,int* count)
{
	if(root==NULL) return;
	if(strcmp(root->symbol,"<var_name>")==0)
	{

		(*count)++;
		return ;
	}
	for(int i=0;i<root->num_children;i++)
	{
		count_subtree_vars(root->children[i],count);
	}
	return ;

}

void count_variables(parseTreeNode* root,int* count)
{
	if(root==NULL) return;
	if(strcmp(root->symbol,"<dec>")==0)
	{
		count_subtree_vars(root,count);
		return ;
	}
	for(int i=0;i<root->num_children;i++)
	{
		count_variables(root->children[i],count);
	}
	return ;
}

void populateTable(parseTree* tree, typeExpressionTable* table)
{
	int num_variables=0;
	count_variables(tree->root,&num_variables);
	table->entries = (typeExpressionTableEntry**) malloc(sizeof(typeExpressionTableEntry*) * num_variables);
    traverse_tree(tree->root,table);
    return ;

}

void TypeExpressionToString(typeExpressionTableEntry* node)
{
  if(node->t==primitive)
  {
    char* type1=(node->te)->p.basicElementType;
    printf("<type=%s>",type1);
  }
  else if(node->t==rectangular)
  {
    //<type=rectangularArray, dimensions=2, range_R1= (2, 5), range_R2 = (3, 6), basicElementType = integer>
    printf("<");
    printf("type=rectangularArray, ");
    printf("dimensions=%d, ",(node->te)->r.dimensions);
    int count=1;
    rect_range_node* root=((node->te)->r).head;
    while(root!=NULL)
    {
      printf("range_R%d=(%d,%d), ",count++,root->low,root->hi);
      root=root->next;
    }
    printf("basicElementType=%s",(node->te)->r.basicElementType);
    printf(">");
  }
  else
  {
    printf("<");
    printf("type=jaggedArray, ");
    printf("dimensions=%d, ",(node->te)->j.dimensions);
    printf("range_R1=(%d,%d), ",(node->te)->j.range1[0],(node->te)->j.range1[1]);
    //
    if((node->te)->j.dimensions==2)
    {
      //<type =jaggedArray, dimensions=2, range_R1=(3, 8), range_R2 = (3, 6, 2, 4, 1, 5), basicElementType = integer>
      printf("range_R2=(");
      twoDNode* root=(node->te)->j.r2.head_2d;
      while(root && root->next)
      {
        printf("%d, ",root->size_value);
        root=root->next;
      }
      printf("%d",root->size_value);
      printf("), ");
    }
    else
    {
      //range_R2 = (3 [ 5, 3, 5] , 2 [ 3, 5], 3 [ 5, 4, 3] ,4 [ 2, 5,4, 4] ), basicElementType = integer>
      printf("range_R2=(");
      threeDNode* root=(node->te)->j.r2.head_3d;
      // int twoDSizes;
      // struct twoDNode* threeDSizes;
      // struct threeDNode* next;
      while(root && root->next)
      {
        printf("%d",root->twoDSizes);
        twoDNode* root2=root->threeDSizes;
        printf("[");
        while(root2 && root2->next)
        {
          printf("%d,",root2->size_value);
          root2=root2->next;
        }
        printf("%d",root2->size_value);
        printf("],");
        root=root->next;
      }
      printf("%d",root->twoDSizes);
      twoDNode* root2=root->threeDSizes;
      printf("[");
      while(root2 && root2->next)
      {
        printf("%d,",root2->size_value);
        root2=root2->next;
      }
      printf("%d",root2->size_value);
      printf("] ");
      printf("), ");
    }
    printf("basicElementType=%s",(node->te)->j.basicElementType);
    printf(">");
}
}

void printTypeExpressionTable(typeExpressionTable T)
{
  for(int i=0;i<T.size;i++)
  {
      typeExpressionTableEntry* tet=T.entries[i];
      printf("Variable Name:%s\t\t",tet->variable_name);
      if(tet->t==primitive)
      {
        printf("Type: primitive");
      }
      else if(tet->t==rectangular)
      {
        printf("Type: Rectangular Array");
      }
      else
      {
        printf("Type: Jagged Array");
      }
      printf("\t\t");
      if(tet->stat==dyn)
      {
        printf("isStatic: Dynamic");
      }
      else if(tet->stat==static_var)
      {
        printf("isStatic: Static");
      }
      else
      {
        printf("%30s","isStatic: Not_Applicable");
      }
      printf("\t\t");
      TypeExpressionToString(tet);
      printf("\n");
  }
}