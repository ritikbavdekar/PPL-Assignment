#include "utils.h"
#include "token.h"

#ifndef structures_h
#define structures_h
#include "structures.h"
#endif

tokenStream* createEmptyTokenStream();
tokenStreamNode* createTokenStreamNode(token_idx i, char* lexeme, int line_number);
void addToken(tokenStream* t, tokenStreamNode* node);
void printToken(tokenStreamNode* node);
void printTokenStream(tokenStream* t);

