void PreOrderSuccessorUtil(parseTreeNode* node,int *flag,parseTreeNode** next)
{
	if(node==NULL) return;
	if(node->num_children==0 && !isTerminal(node->symbol) && flag==0)
	{
		flag=1;
		*next=node;
		return;
	}
	for(int i=0;i<node->num_children;i++)
	{
		PreOrderSuccessorUtil(node->children[i]);
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
	return next;
}