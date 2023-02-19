%{
#include <stdio.h>
#include <stdlib.h>
extern int yylex(void);
%}



%token LPAREN RPAREN
%token END

%%

input: expression END
     | END
     ;

expression: LPAREN
          | LPAREN expression RPAREN
          | expression expression
          ;

%%

int main() {
    yyparse();
    return 0;
}

int yyerror(char* s) {
    printf("Error: %s\n", s);
    return 0;
}

int yylex() {
    int c;
    while ((c = getchar()) != EOF) {
        if (isspace(c)) {
            // skip whitespace
            continue;
        } else if (c == '(') {
            return LPAREN;
        } else if (c == ')') {
            return RPAREN;
        } else {
            // invalid character
            return -1;
        }
    }
    return END;
}