#include <stdio.h>
#include "include/lexer.h"
#include "include/parser.h"
#include "include/AST.h"
#include "include/visitor.h"
#include "include/io.h"

int main(int arg, char* argv[]){
    lexer_T* lexer = init_lexer(
        get_file_contents(argv[1])
    );

    parser_T* parser = init_parser(lexer);
    AST_T* root = parser_parse(parser);
    visitor_T* visitor = visitor_init();
    visitor_visit(visitor, root);
    return 0;
}