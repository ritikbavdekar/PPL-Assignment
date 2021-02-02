#include "utils.h"
#include "lexer.h"

#define MAXCHAR 1000 

void tokeniseSourcecode(char* filename, tokenStream* s)
{
	FILE* FILEIN = fopen(filename, "r");
	// char[1000] line;
	// fscanf(fptr, "%[^\n]", line);
	// char *token = strtok(string, " ");
	char line[MAXCHAR];
	int lineNumber=1;

	while (fgets(line,MAXCHAR,FILEIN))
	{
	// printf("tokeniseSourcecodee\n");
		int idx = strlen(line)-1;
		if(line[idx] == '\n')
			line[idx] = '\0';

		if(!line)
			continue;
		
		char *lexeme = strtok(line, " ");
		strip(lexeme);
		
		// removeSpaces(lexeme);

		while(lexeme != NULL) {

			int id;
			identify_token(lexeme, &id);
			tokenStreamNode* node = createTokenStreamNode(id, lexeme, lineNumber);
			addToken(s, node);
		// printf("%s\n", lexeme);
      		lexeme = strtok(NULL, " "); //next token
      	}

      	lineNumber++;
	}

	fclose(FILEIN);
}



