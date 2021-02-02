typedef enum token{jagged, array, integer,real,boolean, size, variables, values,declare,list,of,COLON,SQOP,SQCP, PoP , PcL , BoP , BcL , SEMICOLON ,PLUS,MINUS,DIVIDE,MULTIPLY,OR,AND,EQUAL,static_constant,var} token;
typedef struct {
	 token token_name;
	 char lexeme[];
	 int line_number;
} tokenStream;

tyepedef struct tokenStreamNode{
	TokenStream values;
	struct tokenStreamNode* next;

} tokenStreamNode;


TokeniseSourceCode -> ,linkedlist ADD ,generate linkedlist,

linkedlist.h
linkedlist.c
createNode():

add(head,token_name,lexeme,line_number)
generateLinkedList

driverfunction:Readtextfile tokenise add()

token identify_token(char lexeme[])
{
	switch lexeme:
		case 'jagged': return jagged 
		case 'array'
}