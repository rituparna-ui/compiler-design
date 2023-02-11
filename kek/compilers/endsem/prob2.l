%{
  #include<stdio.h>
  #include<string.h>
  #include "prob2.tab.h"
  
 
 
%}
%%

regular {printf("Token : %s; Lexeme: %s","regular \n",yytext);}

simple  {return SIMPLE;}
simp    {return SIMPLE;}
sim     {return SIMPLE;}
si      {return SIMPLE;}
s       {return SIMPLE;}

compound {return COMPOUND;}
compoun  {return COMPOUND;}
compou   {return COMPOUND;}
compo    {return COMPOUND;}
comp     {return COMPOUND;}
com      {return COMPOUND;}
co       {return COMPOUND;}
c        {return COMPOUND;}

[()]      
[1-9]+[0-9]* {yylval.num=atoi(yytext) ;return NUM;}
[ \t]+  ;
.\n          {return EOL;}
.            {printf("Token and Lexeme :%s",yytext);} 




%%
int yywrap() {}


yyerror(char* s){
    fprintf(stderr,"ERROR  :  %s \n",s);   

    return 0;
}

