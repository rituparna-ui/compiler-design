%{
  #include<stdio.h>
 
%}
%%

[r] {printf("%s",yytext);}
[g] {printf("%s",yytext);}
"woof" {printf("w");}







%%
int yywrap() {}
int main(){

    
    yylex();


    
}
