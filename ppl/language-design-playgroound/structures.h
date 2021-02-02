#include "utils.h"

#define typeTableSize 500
typedef struct rule
{
	char* left;
	struct linkedList* right;
} rule;

typedef struct grammar
{
	struct rule** rules;
	int size;
} grammar;

typedef struct node
{
	char* data;
	struct node* next;
} node;

typedef struct linkedList
{
	struct node* head;
} linkedList;

typedef enum {terminal, non_terminal} Tag;
typedef struct parseTreeNode
{
	char* symbol;
	int num_children;
	struct parseTreeNode** children;
	Tag tag;
	char* lexeme;
	int line_number;
	//typeInfo add
	int depth;
	int rule_index;
}parseTreeNode;

typedef struct parseTree
{
	parseTreeNode* root;
} parseTree;


typedef struct stackNode 
{
	char* symbol;
	bool isTerminal;
	struct stackNode* next;
}stackNode;

typedef struct stack 
{
	stackNode* top;
	int count;
}stack;

typedef int token_idx;

typedef struct tokenStreamNode{
	token_idx id;
	char* lexeme;
	int line_number;
	struct tokenStreamNode* next;
}tokenStreamNode;

typedef struct tokenStream{
	int count;
	tokenStreamNode* head;
}tokenStream;


typedef struct
{
	char* lexeme;
	char* symbol;
}token;

typedef struct range_node{
  int low;
  int hi;
  struct range_node* next;
}rect_range_node;

typedef struct twoDNode
{
  int size_value;
  struct twoDNode* next;
}twoDNode;

typedef struct threeDNode
{
  int twoDSizes;
  struct twoDNode* threeDSizes;
  struct threeDNode* next;
}threeDNode;

typedef union
{
  twoDNode* head_2d;
  threeDNode* head_3d;
}range2;

typedef struct{
char* typeExp_type;
int dimensions;
int range1[2];
char* basicElementType;
range2 r2; //tagged with dimensions r2 is union type
}JaggedArrayTypeExp; //variant record tag: dimensions

typedef struct{
  char* typeExp_type;
  int dimensions;
  rect_range_node* head; //populate on fly all the dimension into a LinkedList
  char* basicElementType;//fixed
}RectArrayTypeExp; //fixed

typedef struct{
  char* basicElementType;
}PrimitiveTypeExp;

typedef union
{
  PrimitiveTypeExp p;
  RectArrayTypeExp r;
  JaggedArrayTypeExp j;
}typeExpression;

typedef struct{
  char* variable_name;
  enum {primitive,rectangular,jagged} t;
  enum {dyn,static_var,not_applicable} stat;
  typeExpression* te; //tagged with type
}typeExpressionTableEntry; //variant record tag: type

typedef struct typeExpressionTable
{
	typeExpressionTableEntry** entries;
	int size;
} typeExpressionTable;

//equality check
//print typeExpression
