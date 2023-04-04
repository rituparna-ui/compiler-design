%{
#include <stdio.h>
#include <stdlib.h>
#include "main.tab.h"
int condition = 0;
int update = 0;
int delete = 0;
int terminate = 0;
%}

%%

Employee |
employee |
Employees |
employees {
  if (update)
  {
    strcat(yylval.ch, " Employee set");
  }
  else if (delete)
  {
    strcat(yylval.ch, " from Employee");
  }
  else
  {
    strcat(yylval.ch, " Employee");
  }

  return TABLE;
}

all {
  strcat(yylval.ch, " *");
  return '*';
}

show |
give |
select {
  strcat(yylval.ch, "select");
  return SELECT;
}

insert |
add {
  strcat(yylval.ch, "insert");
  return INSERT;
}

update |
modify {
  strcat(yylval.ch, "update");
  update = 1;
  return UPDATE;
}

delete |
remove {
  strcat(yylval.ch, "delete");
  delete = 1;
  return DELETE;
}

create {
  strcat(yylval.ch, "create");
  return CREATE;
}

database    {
  strcat(yylval.ch, " database");
  return DATABASE;
}

from | 
for |
of {
  strcat(yylval.ch, " from");
  return FROM;
}

where |
whose |
having {
  int len = strlen(yylval.ch);
  strcat(yylval.ch, " where");
  condition = 1;
  return WHERE;
}

null |
none |
not {
  int len = strlen(yylval.ch);
  yylval.ch[len - 1] = '\0';
  strcat(yylval.ch, " IS NULL");
  return NONE;
}

values  {
  strcat(yylval.ch, " values");
  return VALUES;
}

into {
  strcat(yylval.ch, " into");
  return INTO;
}

and {
  if (condition)
  {
    strcat(yylval.ch, " and");
    return AND;
  }
  strcat(yylval.ch, " ,");
  return ',';
}

or {
  strcat(yylval.ch, " or");
  return OR;
}

set {
  strcat(yylval.ch, " set");
  return SET;
}

age {
  strcat(yylval.ch, " age");
  return AGE;
};
                        
name    {
  strcat(yylval.ch, " name");
  return NAME;
};

salary  {
  strcat(yylval.ch, " salary");
  return SALARY;
};

"is greater"|[>]    {
  if (condition)
  {
    strcat(yylval.ch, " >");
    return '>';
  }
};

"is greater than or equal to"|[>=]    {
  if (condition)
  {
    strcat(yylval.ch, " >=");
    return GREATER_THAN;
  }
};

"is smaller"|[<]    {
  if (condition)
  {
    strcat(yylval.ch, " <");
    return '<';
  }
};

"is smaller than or equal to"|[<=]    {
  if (condition)
  {
    strcat(yylval.ch, " <=");
    return SMALLER_THAN;
  }
};

[*] {
  strcat(yylval.ch, " *");
  return *yytext;
}

[,] {
  strcat(yylval.ch, " ,");
  return *yytext;
}

is|[=]|equals|as    {
  if (condition)
  {
    strcat(yylval.ch, " =");
    return '=';
  }
}

to {
  strcat(yylval.ch, " =");
  return '=';
}

[.|;] {
  strcat(yylval.ch, ";\n");
  terminate = 1;
  return ';';
}

[0-9]+ {
  strcat(yylval.ch, " ");
  strcat(yylval.ch, yytext);
  return NUMBER;
}


[0-9]+[.][0-9]+ {
  strcat(yylval.ch, " ");
  strcat(yylval.ch, yytext);
  return NUMBER;
}      

\"[a-zA-Z]*\" {
  strcat(yylval.ch, yytext);
  return WORD;
}

\n {
  if (terminate)
  {
    return *yytext;
  }
}	

[ \t]+      ;

[a-zA-Z]*   ;

.           ;

%%