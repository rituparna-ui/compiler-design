%{
  #include<stdio.h>
  #include<stdlib.h>
%}

%token NUMBER ID
%left '+' '-'
%left '*' '/'

%%
expr  : expr '+' expr
      | expr '-' expr
      | expr '*' expr
      | expr '/' expr
      | '-'NUMBER
      | '-'ID
      | NUMBER
      | ID
      ;
%%


int main(){
  yyparse();
  printf("Valid Expression");
  return 0;
}

int yyerror(char *s){
  printf("Invalid Expression");
  exit(0);
}