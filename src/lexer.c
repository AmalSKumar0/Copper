#include "include/lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

lexer_T* init_lexer(char* contents){
    lexer_T* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
    lexer->contents = contents;
    lexer->i = 0;
    lexer->c = contents[lexer->i];
    return lexer;
}

void lexer_advance(lexer_T* lexer){
    if(lexer->c != '\0'){
        lexer->i += 1;
        lexer->c = lexer->contents[lexer->i];
    }
}

void lexer_skip_whitespace(lexer_T* lexer){
    while(lexer->c == ' ' || lexer->c == '\n' || lexer->c == '\t' || lexer->c == '\r') {
        lexer_advance(lexer);
    }
}

token_T* lexer_get_next_token(lexer_T* lexer){
    while(lexer->c != '\0' ){
        if(lexer->c == ' ' || lexer->c == 10){
            lexer_skip_whitespace(lexer);
            continue;
        }

        if(isalnum(lexer->c)){
            return lexer_collect_id(lexer);
        }   

        if(lexer->c == '"'){
            return lexer_collect_string(lexer);
        }

        switch(lexer->c){
            case '=':
                return lexer_advance_with_token(lexer,init_token(TOKEN_EQ, lexer_get_current_char_as_string(lexer))); 
            case ';':
                return lexer_advance_with_token(lexer,init_token(TOKEN_SEMI, lexer_get_current_char_as_string(lexer))); 
            case '(':
                return lexer_advance_with_token(lexer,init_token(TOKEN_LPAREN, lexer_get_current_char_as_string(lexer))); 
            case ')':
                return lexer_advance_with_token(lexer,init_token(TOKEN_RPAREN, lexer_get_current_char_as_string(lexer))); 
            default:
                if((lexer->c >= 'a' && lexer->c <= 'z') || (lexer->c >= 'A' && lexer->c <= 'Z') || lexer->c == '_'){
                    return lexer_collect_string(lexer);
                }
                break;
        }

        lexer_advance(lexer);
    }
    return NULL; 
}

token_T* lexer_advance_with_token(lexer_T* lexer, token_T* token){
    lexer_advance(lexer);
    return token;
}

token_T* lexer_collect_string(lexer_T* lexer){
    lexer_advance(lexer);
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';
    while(lexer->c != '"'){
        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1)*sizeof(char));
        strcat(value, s);
        lexer_advance(lexer);
    }
    lexer_advance(lexer);
    return init_token(TOKEN_STRING, value);
}

token_T* lexer_collect_id(lexer_T* lexer){
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';
    while(isalnum(lexer->c)){
        // printf("Char: %c\n", lexer->c);
        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1)*sizeof(char));
        strcat(value, s);
        lexer_advance(lexer);
    }
    return init_token(TOKEN_ID, value);
}

char* lexer_get_current_char_as_string(lexer_T* lexer){
    char* s = calloc(2, sizeof(char));
    s[0] = lexer->c;
    s[1] = '\0';
    return s;    
}
