%{
#include<stdio.h>
int ddl = 0;
int dml = 0;  
%}

%%
("CREATE".*;\n)  |
("DROP".*;\n)    |
("ALTER".*;\n)   {printf("");ddl++;}

("SELECT".*\n)  |
("INSERT".*\n)  |
("UPDATE".*\n)  {printf("");dml++;}
%%

int main(){
  yyin=fopen("sql.txt","r");
  yylex();
  printf("DDL %d\n",ddl);
  printf("DML %d\n",dml);
  return 0;
}
int yywrap(){
  return 1;
}