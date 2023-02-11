%{
  #include<stdio.h>
  #include<string.h>
  #include "prob2.tab.h"
  #include<math.h>
 
 
%}
%%

regular {return REGULAR;}

simple  {printf("simple");return SIMPLE;}
simpl  {printf("simple");return SIMPLE;}
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

[0-9]+[0-9]* {yylval.num=atoi(yytext) ;return NUM;}

"("      {return BRO;}
")"     { return BRC;}
","      { return COM;}

[ \t]+  ;

.            {yyerror("invalid character");} 




%%
int yywrap() {}


yyerror(char* s){
    fprintf(stderr,"ERROR  :  %s \n",s);   

    return 0;
}

