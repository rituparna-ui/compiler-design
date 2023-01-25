%{
  #include<stdio.h>
  
  struct TagCount
  {
    char tag[10];
    int count;
  };

  int arrLen = 0;

  struct TagCount count[10];

  void add(char* str, int len)
  {
    int start =1;
    len = len-2;
    char tag[10];
    if(str[1] == '/')
    {
      start = 2;
      len = len-1;
    }
    strncpy(tag, str+start, len);
    tag[len] = '\0';
    for(int i = 0; i < arrLen ; i++)
    {
      if(strcmp(count[i].tag, tag) == 0)
      {
        count[i].count += 1;
        return;
      }
    }
    strcpy(count[arrLen].tag, tag);
    count[arrLen].count += 1;
    arrLen +=1;
  }
%}

%option noyywrap

%%
"<"[^>]*> { add(yytext, yyleng); }
.|\n     ;
%%



int main()
{
yyin=fopen("kek.html","r");
yylex();
for(int i = 0; i < 10; i++)
{
  if(count[i].count > 0)
  {
    printf("%s = %d\n", count[i].tag, count[i].count);
  }
}
return 0;
}