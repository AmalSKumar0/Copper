#include "include/token.h"
#include <stdlib.h>
#include <string.h>

token_T* init_token(int type,char* value){
    token_T* token = calloc(1, sizeof(token_T));
    token->value = value;
    token->type = type;
    return token;
}