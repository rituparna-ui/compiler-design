rm sql
lex one.l
yacc -d one.y
gcc lex.yy.c y.tab.c -o sql