#include "include/AST.h"
#include "include/visitor.h"
#include <stdio.h>
#include <string.h>

static AST_T* printfunction(visitor_T* visitor,AST_T** args, int args_size){
     for (int i = 0; i < args_size; i++) {
            AST_T* arg = visitor_visit(visitor,args[i]);

            switch(arg->type){
                case AST_STRING:
                    printf("%s\n", arg->string_value);
                    break;
                default:
                    printf("Error: Unsupported argument type in print function: %d\n", arg->type);
            }
    }
    return init_ast(AST_NOOP);
}

visitor_T* visitor_init(){
    visitor_T* visitor = calloc(1, sizeof(struct VISITOR_STRUCT));
    visitor->variable_definitions =  NULL;
    visitor->variable_definitions_size = 0;
    return visitor;
}

AST_T* visitor_visit_variable_declaration(visitor_T* visitor, AST_T* node){
    if(visitor->variable_definitions ==  NULL){
        visitor->variable_definitions =  calloc(1, sizeof(AST_T*));
        visitor->variable_definitions[0] = node;
        visitor->variable_definitions_size += 1;
    }
    else{
        visitor->variable_definitions_size +=  1;
        visitor->variable_definitions =  realloc(visitor->variable_definitions, (visitor->variable_definitions_size) * sizeof(AST_T*));
        visitor->variable_definitions[visitor->variable_definitions_size-1] = node;
    }
    return node;
}

AST_T* visitor_visit_variable(visitor_T* visitor, AST_T* node){
    for(int i=0;i<visitor->variable_definitions_size;i++){
        AST_T* var_def = visitor->variable_definitions[i];
        if(strcmp(var_def->variable_declaration_variable_name, node->variable_name) == 0){
            return visitor_visit(visitor, var_def->variable_definition_value);
        }
    }
    printf("undefined variable: %s\n", node->variable_name);
    return node;
}

AST_T* visitor_visit_function_call(visitor_T* visitor, AST_T* node){
    if(strcmp(node->function_name, "print") == 0){
        return printfunction(visitor,node->function_arguments, node->function_arguments_size);
    }
    printf("undefined function: %s\n", node->function_name);
    exit(1);
}

AST_T* visitor_visit_string(visitor_T* visitor, AST_T* node){
    return node;
}

AST_T* visitor_visit_compound(visitor_T* visitor, AST_T* node){
    for (int i = 0; i < node->compound_size; i++) {
        visitor_visit(visitor, node->compound_value[i]);
    }
    return init_ast(AST_NOOP);
}

AST_T* visitor_visit(visitor_T* visitor, AST_T* node){
    switch(node->type){
        case AST_VARIABLE_DECLARATION:
            return visitor_visit_variable_declaration(visitor, node);
        case AST_VARIABLE:
            return visitor_visit_variable(visitor, node);
        case AST_FUNCTION_CALL:
            return visitor_visit_function_call(visitor, node);
        case AST_STRING:
            return visitor_visit_string(visitor, node);
        case AST_COMPOUND:
            return visitor_visit_compound(visitor, node);
        case AST_NOOP:
            return init_ast(AST_NOOP);
    }
    printf("Error: Unknown AST node type in visitor: %d\n", node->type);
    exit(1);
}