small [a-z]
capital [A-Z]

%option noyywrap

%%
{small} printf("%s", yytext);
{capital} {printf("");}
%%

int main(){
yylex();
}
