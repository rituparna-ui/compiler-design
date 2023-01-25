%{
  #include<stdio.h>
%}

%option noyywrap 

%%

\/\*(.*\n)*.*\*\/ {fprintf(fopen("javadoc.txt","w"),"%s\n\n",yytext);}

\/\/(.*) ;
%%

int main(int k,char **argcv)
{
  yyin=fopen(argcv[1],"r");
  yyout=fopen("Mainx.java","w");
  yylex();
  return 0;
}
