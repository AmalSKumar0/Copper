#include "include/AST.h"
#include <stdlib.h>

AST_T* init_ast(int type){
    AST_T* ast = calloc(1, sizeof(AST_T));
    ast->type = type;
    ast->variable_declaration_variable_name=NULL;
    ast->variable_definition_value=NULL;
    ast->variable_name=NULL;
    ast->variable_value=NULL;
    ast->function_name=NULL;
    ast->function_arguments=NULL;
    ast->function_arguments_size=0;
    ast->string_value=NULL;
    ast->compound_value=NULL;
    ast->compound_size=0;
    return ast;
}