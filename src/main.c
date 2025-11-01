#include <stdio.h>
#include "include/lexer.h"

int main(int arg, char* argv[]){
    lexer_T* lexer = init_lexer(
        "name = \"Amal s kumar\";\n"
        "print(name);"
    );

    token_T* token;
    while((token = lexer_get_next_token(lexer)) != NULL){
        printf("Token: %d, Value: %s\n", token->type, token->value);
    }
    return 0;
}