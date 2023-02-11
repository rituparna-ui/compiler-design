%{
  #include<stdio.h>
  #include<string.h>
  
 
 
%}
%%

regular {printf("Token : %s; Lexeme: %s\n","regular ",yytext);}

simple  {printf("Token : %s; Lexeme: %s \n","simple",yytext);}
simpl  {printf("Token : %s; Lexeme: %s \n","simple",yytext);}
simp    {printf("Token : %s; Lexeme: %s \n","simple",yytext);}
sim     {printf("Token : %s; Lexeme: %s \n","simple",yytext);}
si      {printf("Token : %s; Lexeme: %s \n","simple",yytext);}
s       {printf("Token : %s; Lexeme: %s \n","simple",yytext);}

compound {printf("Token : %s; Lexeme: %s \n","compound",yytext);}
compoun  {printf("Token : %s; Lexeme: %s \n","compound",yytext);}
compou   {printf("Token : %s; Lexeme: %s \n","compound ",yytext);}
compo    {printf("Token : %s; Lexeme: %s \n","compound",yytext);}
comp     {printf("Token : %s; Lexeme: %s \n","compound",yytext);}
com      {printf("Token : %s; Lexeme: %s \n","compound",yytext);}
co       {printf("Token : %s; Lexeme: %s \n","compound",yytext);}
c        {printf("Token : %s; Lexeme: %s \n","compound",yytext);}

[(){}]      {printf("Token : %s; Lexeme: %s\n",yytext,yytext);}
[1-9]+[0-9]* {printf("Token : %s; Lexeme: %s\n","NUM",yytext);}

[ \t]+  ;
.\n          {printf("Token and Lexeme :%s","<newline>");}
.            {printf("Token and Lexeme :%s",yytext);} 




%%
int yywrap() {}


yyerror(char* s){
    fprintf(stderr,"ERROR  :  %s \n",s);   

    return 0;
}

