#include <stdio.h>
#include "include/lexer.h"
#include "include/parser.h"
#include "include/AST.h"

int main(int arg, char* argv[]){
    lexer_T* lexer = init_lexer(
        "var name = \"Amal s kumar\";\n"
        "print(name);"
    );

    parser_T* parser = init_parser(lexer);
    AST_T* ast = parser_parse(parser);

    printf("%d\n", ast->type); // should print AST_COMPOUND which is 4
    printf("%d\n", ast->compound_size);
    return 0;
}