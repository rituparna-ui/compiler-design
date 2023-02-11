
%{
 #include<stdio.h>
 #include<string.h>
 #include<math.h>
 
 


 
%}


%union{
    int num;
    char * str;
    double val;
    
}
%token EOL

%token<num> NUM
%token<num> REGULAR
%token SIMPLE
%token COMPOUND
%token BRO
%token COM
%token BRC

%type<val> E
%type<val> S
%type<val> expr



%%

input: S input
|EOL
;

S: E     {printf("%lf\n",$1);}
| EOL
;

E :  
REGULAR BRO  expr COM expr BRC  {$$ = $3 + ($3*2.01)/100*$5;}
|SIMPLE BRO  expr COM expr BRC   {$$ = $3 + ($3 * 5.5 * $5) / 100;}
|COMPOUND BRO  expr COM expr BRC  {$$ = $3 * pow((1 + 5.7/$5), $5);}
| NUM  {$$=(double)yylval.num; }


epsilon :  ;
expr : E   {$$=$1;}
| epsilon  {$$=0;}

%%

int main(){
    yyparse();
    return 0;
}

