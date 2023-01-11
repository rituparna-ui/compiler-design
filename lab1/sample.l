words [a-zA-Z]+
%option noyywrap
%%
{words} printf("%s <- Word\n", yytext);
%%

int main(){
yylex();
}
