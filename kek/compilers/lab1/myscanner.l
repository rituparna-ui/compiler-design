%{
  #include<stdio.h>
  int comments=0;
  int empty=0;
  int code=0;
  int brackets=0;
  int keyword=0;
  int identifier=0;
  int number=0;
%}
%%


"/*"[^*/]*"*/" {comments++;}
"//".* {comments++;}
^\r\n {empty++;}
.\n {code++;}
[(){}] {brackets++;}
auto|double|int|struct|main|break|else|long|switch|case|enum|register|typedef|char|extern|return|union|continue|for|signed|void|do|if|static|while|default|goto|sizeof|volatile|const|float|short|unsigned {keyword++;}
[a-zA-Z_][a-zA-Z0-9_]* {identifier++;}
[1-9][0-9]* {number++;}
. {;}






%%
int yywrap() {}
int main(){

    
    yylex();
    printf("no. of comments %d \n",comments);
    printf("no. of empty lines %d \n",empty);
    printf("no. of code lines %d \n",code);
    printf("no. of brackets %d\n",brackets);
    printf("no. of keywords %d\n",keyword);
    printf("no. of identifier %d\n",identifier);
    printf("no. of number %d\n",number);
    


    
}
