#include "utils.h"
#include "grammar.h"

struct rule** getRules(struct grammar* g)
{
	return g->rules;
}

struct linkedList* getRight(struct rule* r)
{
	return r->right;
}

struct rule* createRule(char* line)
{
	// printf("createRule\n");
	struct rule* new_rule = (struct rule*)malloc(sizeof(struct rule));

	char* token = strtok(line, delimiter);
	new_rule->left = (char*)malloc((strlen(token)+1) * sizeof(char));
	strcpy(new_rule->left, token);

	token = strtok(NULL, delimiter);

	new_rule->right = createEmptyList();

	while(token)
	{
		insert(new_rule->right, token);
		token = strtok(NULL, delimiter);
	}

	return new_rule;
}

void readGrammar(char* filename, struct grammar** G)
{
	struct grammar* g = (struct grammar*)malloc(sizeof(struct grammar));

	int n = countLines(filename);
	g->size = n;

	g->rules = (struct rule**)malloc(n * sizeof(struct rule*));

	FILE* fp = fopen(filename, "r");
	char* line = (char*)malloc(200*sizeof(char));
	size_t len = 0;

	for(int i=0; i<n; i++)
	{
		getline(&line, &len, fp);

		//removing newline character
		int idx = strlen(line)-1;
		if(line[idx] == '\n')
			line[idx] = '\0';
		g->rules[i] = createRule(line);
		// printf("readGrammar\n");
	}

	*G = g;
	fclose(fp);
}

void printRule(struct rule* r)
{
	printf("%s ---> ", r->left);
	printList(r->right);
}

void printGrammar(struct grammar* g)
{
	for(int i=0; i<g->size; i++)
	{
		printRule(g->rules[i]);
		printf("\n");
	}
}
