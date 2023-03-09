%{
#include <stdio.h>
#include "y.tab.h"
extern int yylval;
%}

%%
noun      return NOUN;
verb      return VERB;

a  |
an |
the       return ARTICLE;

[ \t]+    ; 
%%