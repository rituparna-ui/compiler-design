%{
#include<stdio.h>
int i=0,yr=0,valid=0;
char *date="00-00-0000";
%}

%%
([0][0])\-([0][0])\-([0-9][0-9][0-9][0-9]) {printf("");}

([0-2][0-9]|[3][0-1])\/((0(1|3|5|7|8))|(10|12))\/([1-2][0-9][0-9][-0-9]) |
([0-2][0-9]|30)\/((0(4|6|9))|11)\/([1-2][0-9][0-9][0-9]) |
([0-1][0-9]|2[0-8])\/02\/([1-2][0-9][0-9][0-9]) {
  valid=1; 
  printf("Valid date %s\n",yytext);
  char * token = strtok(yytext, "/");
  while( token != NULL ) {
    printf( " %s\n", token );
    token = strtok(NULL, "/");
  }
}
29\/02\/([1-2][0-9][0-9][0-9]) { 
  while(yytext[i]!='/')i++;
  i++;
  while(yytext[i]!='/')i++;
  i++;
  while(i<yyleng){
      yr=(10*yr)+(yytext[i++]-'0');
  } 
  if(yr%4==0||(yr%100==0&&yr%400!=0)){
    valid=1;
    printf("Valid date %s\n",yytext);
    char * token = strtok(yytext, "/");
    while( token != NULL ) {
      printf( " %s\n", token );
      token = strtok(NULL, "/");
    }
  }
}


([0-2][0-9]|[3][0-1])\-((0(1|3|5|7|8))|(10|12))\-([1-2][0-9][0-9][-0-9]) |
([0-2][0-9]|30)\-((0(4|6|9))|11)\-([1-2][0-9][0-9][0-9]) |
([0-1][0-9]|2[0-8])\-02\-([1-2][0-9][0-9][0-9]) {
  valid=1; 
  printf("Valid date %s\n",yytext);
  char * token = strtok(yytext, "-");
  while( token != NULL ) {
    printf( " %s\n", token );
    token = strtok(NULL, "-");
  }
}
29\-02\-([1-2][0-9][0-9][0-9]) { 
  while(yytext[i]!='-')i++;
  i++;
  while(yytext[i]!='-')i++;
  i++;
  while(i<yyleng)yr=(10*yr)+(yytext[i++]-'0');
  if(yr%4==0||(yr%100==0&&yr%400!=0)){
    valid=1;
    printf("Valid date %s\n",yytext);
    char * token = strtok(yytext, "-");
    while( token != NULL ) {
      printf( " %s\n", token );
      token = strtok(NULL, "-");
    }
  }
}

    
([0-2][0-9]|[3][0-1])\-(jan|mar|may|jul|aug|oct|dec)\-([1-2][0-9][0-9][-0-9]) |
([0-2][0-9]|30)\-(apr|jun|sep|nov)\-([1-2][0-9][0-9][0-9]) |
([0-1][0-9]|2[0-8])\-feb\-([1-2][0-9][0-9][0-9]) {
  valid=1; 
  printf("Valid date %s\n",yytext);
  char * token = strtok(yytext, "-");
  while( token != NULL ) {
    printf( " %s\n", token );
    token = strtok(NULL, "-");
  }
}
29\-feb\-([1-2][0-9][0-9][0-9]) { 
  while(yytext[i]!='-')i++;
  i++;
  while(yytext[i]!='-')i++;
  i++;
  while(i<yyleng)yr=(10*yr)+(yytext[i++]-'0');
  if(yr%4==0||(yr%100==0&&yr%400!=0)){
    valid=1;
    printf("Valid date %s\n",yytext);
  }
  char * token = strtok(yytext, "-");
  while( token != NULL ) {
    printf( " %s\n", token );
    token = strtok(NULL, "-");
  }
}

([0-2][0-9]|[3][0-1])\/(jan|mar|may|jul|aug|oct|dec)\/([1-2][0-9][0-9][-0-9]) |
([0-2][0-9]|30)\/(apr|jun|sep|nov)\/([1-2][0-9][0-9][0-9]) |
([0-1][0-9]|2[0-8])\/feb\/([1-2][0-9][0-9][0-9]) {
  valid=1; 
  printf("Valid date %s\n",yytext);
  char * token = strtok(yytext, "/");
  while( token != NULL ) {
    printf( " %s\n", token );
    token = strtok(NULL, "/");
  }
}
29\/feb\/([1-2][0-9][0-9][0-9]) { 
  while(yytext[i]!='-')i++;
  i++;
  while(yytext[i]!='-')i++;
  i++;
  while(i<yyleng)yr=(10*yr)+(yytext[i++]-'0');
  if(yr%4==0||(yr%100==0&&yr%400!=0)){
    valid=1;
    printf("Valid date %s\n",yytext);
  }
  char * token = strtok(yytext, "/");
  while( token != NULL ) {
    printf( " %s\n", token );
    token = strtok(NULL, "/");
  }
}

.+ {printf("");}

%%


int main()
{
  yyin=fopen("date.txt","r");
  yylex();
  return 0;
}
int yywrap()
{
return 1;
}