%{
  #include<stdio.h>
  #include<string.h>
  #include "parser.tab.h"
 
 
%}
%%



[a-z]+ {yylval.str=strdup(yytext) ;return STRING;}
Reverse {return REVERSE;}
[A-Za-z0-9]+ {yyerror("invalid string\n");}
"#" {return HASH;}

"(" {return BRO;}
")" {return BRC;}
.\n {return EOL;}
[ \t]+  ;
. {yyerror("invalid character");} 





%%
int yywrap() {}


yyerror(char* s){
    fprintf(stderr,"ERROR  :  %s \n",s);   

    return 0;
}

