%{
 #include<stdio.h>
 #include<string.h>
 char *reverse(char *);


 
%}


%union{
    char* str;
}
%token EOL
%token<str> STRING
%token<str> REVERSE
%token HASH
%token BRO
%token BRC
%type<str> exp
%type<str> S



%%

input: S input 
| EOL
;


S: exp     {printf("%s\n",$1);}
| EOL      
;

exp: STRING  {$$ = $1;}
|    exp HASH exp {$$ = strcat($1,$3);}
|    REVERSE BRO STRING BRC {$$=reverse($3);}
;

%%

int main(){
    yyparse();
    return 0;
}

char* reverse(char *str1)
{
     int len=strlen(str1);
    char* rev=(char*)malloc(100*sizeof(char));
    
    int j=len-1;
    for(int i=0;i<len;i++){
        rev[i]=str1[j];
        j--;
    }
    
    return rev;
} 
