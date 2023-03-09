%{
#include<stdio.h>
%}

%token ARTICLE NOUN VERB

%%
sentence: 
  noun_phrase verb_phrase '.' { printf("Valid sentence\n"); }
  ;

noun_phrase: 
  ARTICLE noun { }
  ;

verb_phrase: 
  verb noun_phrase { }
  ;

noun: 
  NOUN { }
  ;

verb: 
  VERB { }
  ;

%%

void yyerror(const char *msg)
{
  printf("Error: %s\n", msg);
}

int main()
{
  yyparse();
  return 0;
}