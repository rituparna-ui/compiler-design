%{
  #include<stdio.h>
 
%}
%%


[a-zA-Z_][a-zA-Z0-9_]* {printf("i\n");}
[1-9][0-9]* {printf("n\n");}
[(] {printf("%s\n",yytext);}
[)] {printf("%s\n",yytext);}
[+*/-]  {printf("%s\n",yytext);}
.\n {;}
. {printf("error\n");}







%%
int yywrap() {}
int main(){

    
    yylex();


    
}
