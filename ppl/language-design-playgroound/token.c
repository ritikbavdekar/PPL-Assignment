#include "utils.h"
#include "token.h"

int numtokens = 29;

token tokens[29] = { { "<op_or>", "|||"},
                    { "<op_and>", "&&&"},
                    { "<op_mul>", "*"},
                    { "<op_div>", "/"},
                    { "<op_plus>", "+"},
                    { "<op_minus>", "-"},
                    { "<op_equal>", "="},
                    { "<par_open>" ,"("},
                    { "<par_close>", ")"},
                    { "<curl_open>" ,"{"},
                    { "<curl_close>", "}"},
                    { "<sq_open>" ,"["},
                    { "<sq_close>", "]"},
                    { "<colon>", ":"},
                    { "<semicolon>", ";"},
                    { "<k_program>" ,"program"},
                    { "<k_integer>" ,"integer"},
                    { "<k_boolean>" ,"boolean"},
                    { "<k_real>" ,"real"},
                    { "<k_declare>" ,"declare"},
                    { "<k_variables>", "variables"},
                    { "<k_list>", "list"},
                    { "<k_of>", "of"},
                    { "<k_jagged>", "jagged"},
                    { "<k_size>", "size"},
                    { "<k_array>", "array"},
                    { "<k_values>", "values"},
                    { "<var_name>", " "},
                    { "<const>", " "} } ;

                    
void identify_token(char* lexeme, int* index)
{
    for(int i=0; i<numtokens; i++)
    {
        if(strcmp(lexeme, tokens[i].symbol) == 0)
        {
            *index = i;
            return;
        }
    }

    char c1[] = "<var_name>";
    char c2[] = "<const>";

    if(isdigit(lexeme[0]))
        *index = numtokens-1;

    else
        *index = numtokens-2;
}



