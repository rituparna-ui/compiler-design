
%{
 #include<stdio.h>
 #include<string.h>
 #include<math.h>
 
 


 
%}


%union{
    int num;
    char * str;
    
}
%token EOL

%token<num> NUM
%token<str> REGULAR
%token SIMPLE
%token COMPOUND
%token BRO
%token COM
%token BRC

%type<num> E
%type<num> S
%type<num> expr



%%



S: E     {printf("%d\n",$1);}
 
;

E :  
REGULAR BRO  expr COM expr BRC  {$$=$3+(($3*2.01)/(100+$5));}
|SIMPLE BRO  expr COM expr BRC   {$$=$3+(($3*5.5*$5)/100);}
|COMPOUND BRO  expr COM expr BRC  {$$=$3*pow(1+(5.7/$5),$5);}
| NUM  {$$=$1 ; }

;

expr : E   {$$=$1 ; }

%%

int main(){
    yyparse();
    return 0;
}

