%{
  #include<stdio.h>
%}

%option noyywrap

%%
\/\/(.*) ;
%%

int main(int k,char **argcv)
{
  yyin=fopen(argcv[1],"r");
  yyout=fopen("Mainx.java","w");
  yylex();
  return 0;
}


