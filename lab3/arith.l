%{
#include <string.h>
#include <stdio.h>
 
char identifiers[100][100];
int id_count = 0;
char operators[100][100];
int op_count = 0;
int valid=1;
%}
 
%%
[0-9]+ { 
  printf("Number: %s\n", yytext); 
}
[a-zA-Z][a-zA-Z0-9]* {
    strcpy(identifiers[id_count++], yytext);
}
[+\-*/=%] {
    strcpy(operators[op_count++], yytext);
}
[ \t\n] ;
. { 
  valid = 0;
}
 
%%
int main() {
    yyin=fopen("ar.txt","r");
    yylex();
    if(valid==0){
      printf("Invalid expression\n");
      return 0;
    }
    printf("\nIdentifiers: ");
    for (int i = 0; i < id_count; i++) {
        printf("%s ", identifiers[i]);
    }
    printf("\nOperators: ");
    for (int i = 0; i < op_count; i++) {
        printf("%s ", operators[i]);
    }
    printf("\n");
    return 0;
}
 
int yywrap()
{
    return 1;
}