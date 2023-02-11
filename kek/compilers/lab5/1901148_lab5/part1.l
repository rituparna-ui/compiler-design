
%{
#include <stdio.h>
#include <string.h>
#include "AST.h"
#include "part1.tab.h"

void yyerror(char *);
%}



%%

[ \t]+              {}

\n          {
                return  *yytext;
            }

[0-9]+[.][0-9]+    {
                yylval.str = strdup(yytext);
                return  DOUBLE;
            }

[0-9]+       {
                yylval.str = strdup(yytext);
                return  INT;
            }

[a-zA-Z_][a-zA-Z_0-9]+        {
                yylval.str = strdup(yytext);
                return  ID;
            }

[-+*/()]	    {
                return  *yytext;
            }

.           {
                yyerror("invalid character");
            }


%%

void yyerror(char *s) {
    fprintf(stderr, "line %d: yytext = %s.  Error msg: %s.\n", yylineno, yytext, s);
}

int yywrap(void) {
   return 1;
}

