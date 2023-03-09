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

%%

%token SELECT FROM IDENTIFIER WHERE AND UPDATE SET VALUES DELETE DROP DATABASE CREATE TABLE;

line1: 
    key items from '\n' { printf("Select Command\n"); return 0; } |
    key items using condition '\n' { printf("Select with condition\n"); return 0; } |
    key IDENTIFIER key key updateCondition '\n' { printf("Update Command\n"); return 0; } |
    DROP createDrop IDENTIFIER '\n' { printf("Drop Command\n"); return 0; } |
    CREATE createDrop IDENTIFIER '\n' { printf("CREATE Command\n"); return 0; }
    ;

key:
    UPDATE |
    SET | 
    SELECT |
    VALUES
    ;

createDrop:
    TABLE |
    DATABASE
    ;
  
from:
  FROM identifiers;

items: 
    '*' | 
    identifiers
    ;

identifiers: 
    IDENTIFIER | 
    IDENTIFIER ',' identifiers
    ;

using: 
    FROM IDENTIFIER WHERE
    ;

condition: 
    IDENTIFIER '=' IDENTIFIER | 
    IDENTIFIER '=' IDENTIFIER AND condition
    ;

updateCondition:
    WHERE condition
    ;
%%