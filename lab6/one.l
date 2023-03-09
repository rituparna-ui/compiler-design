%{
#include <stdio.h>
#include "y.tab.h"
extern int yylval;
%}

%%
SELECT					        return SELECT;
FROM					          return FROM;
WHERE					          return WHERE;
AND						          return AND;
UPDATE						      return UPDATE;
SET   						      return SET;
VALUES 						      return VALUES;
DROP 						        return DROP;
DATABASE 						    return DATABASE;
DELETE 						      return DELETE;
CREATE 						      return CREATE;
TABLE 						      return TABLE;
[*]						          return *yytext;
[,]						          return *yytext;
[=]						          return *yytext;
[a-zA-Z][a-zA-Z0-9]+	  return IDENTIFIER;
\n        						  return *yytext;
[ \t]+					        ;
%%