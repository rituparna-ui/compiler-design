%{

#include <stdio.h>
#include <stdlib.h>

int yylex(void);

void yyerror (const char *str) {
	fprintf(stderr, "error: %s\n", str);
}

%}

%union
{
    int num;
    char* ch;
}

%%

%token SELECT CREATE DATABASE DELETE INSERT INTO FROM TABLE WHERE AND SET UPDATE IDENTIFIER OR VALUES SEMI GREATER_THAN SMALLER_THAN;
%token AGE NAME SALARY NUMBER WORD NONE;



line: 
	SELECT fields FROM TABLE ';' '\n' 
	{ 
		printf("%s", yylval.ch);
		return 0;
	}
;
line: 
	SELECT fields FROM TABLE WHERE nested ';' '\n' 
	{ 
		printf("%s", yylval.ch);
		return 0;
	}
;
line: 
	UPDATE TABLE update_nested WHERE nested ';' '\n' 
	{ 
		printf("%s", yylval.ch);
		return 0;
	}
;
line: 
	DELETE TABLE  WHERE nested ';' '\n' 
	{ 
		printf("%s", yylval.ch);
		return 0;
	}
;



fields: 
	field | 
	field ',' field |
	'*'
;

field: 
	AGE | 
	SALARY | 
	NAME
;

name_value: 
	NAME '=' WORD | 
	AGE '=' NUMBER | 
	SALARY '=' NUMBER | 
	NAME '=' NONE | 
	AGE '=' NONE | 
	SALARY '=' NONE
;

update_nested: 
	name_value ',' name_value | 
	name_value
;

nested: 
	condition | 
	condition AND condition
;

condition: 
	AGE '=' NUMBER |
	AGE '>' NUMBER | 
	AGE '<' NUMBER | 
	SALARY '=' NUMBER | 
	SALARY '<' NUMBER | 
	SALARY '>' NUMBER | 
	NAME '=' WORD | 
	NAME '=' NONE | 
	AGE '=' NONE | 
	SALARY '=' NONE | 
	SALARY GREATER_THAN NUMBER | 
	SALARY SMALLER_THAN NUMBER | 
	AGE GREATER_THAN NUMBER | 
	AGE SMALLER_THAN NUMBER
;

%%

int yywrap() {
	return 1;
}

int main() 
{
	yylval.ch = (char*)calloc(100, sizeof(char));
	freopen("parser/input.txt","r",stdin);
	freopen("parser/output.txt","w",stdout);
	yyparse();
}
