%{
#include<stdio.h>
#include<string.h>
void add_tag(char* str, int len);
%}
 
%%
 
"<"[^>]*> { add_tag(yytext, yyleng); };
. ;  {};
%%
 
struct tag
{
    char name[10];
    int count;
};
 
int tag_len = 0;
 
struct tag list[25];
 
int yywrap()
{
    return 1;
}
 
void add_tag(char* str, int len)
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
    for(int i = 0; i < tag_len ; i++)
    {
        if(strcmp(list[i].name, tag) == 0)
        {
            list[i].count += 1;
            return;
        }
    }
    strcpy(list[tag_len].name, tag);
    list[tag_len].count += 1;
    tag_len +=1;
 
}
 
int main()
{
    yyin=fopen("sample.html","r");
    yyout=fopen("sample_out.txt","w");
    yylex();
    for(int i = 0; i < 25; i++)
    {
        if(list[i].count > 0)
        {
            printf("%s --> %d\n", list[i].name, list[i].count);
        }
    }
    return 0;
}