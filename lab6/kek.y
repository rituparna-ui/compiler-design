%{
#include <stdio.h>

void yyerror (const char *str) {
	fprintf(stderr, "error: %s\n", str);
}

int yywrap() {
	return 1;
}

int main() {
	yyparse();
}

%}

%token ARTICLE NOUN PRONOUN VERB ADVERB ADJECTIVE PREPOSITION CONJUNCTION

%%

sentence: 
  subject VERB ARTICLE object 
  { printf("Sentence is valid.\n"); }
  ;

subject: 
  NOUN | 
  PRONOUN
  ;

object: 
  NOUN
  ;

%%
