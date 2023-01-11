%{
#include<stdio.h>
%}

%option noyywrap

%%
a |
an |
the { printf("article => %s\n",yytext);}

eat |
drink |
sleep |
go { printf("Verb detected => %s\n", yytext); }

[a-zA-z]+ {printf("");}
%%

int main(){
  yylex();
}