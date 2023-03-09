%{
#include <stdio.h>
#include "y.tab.h"
extern int yylval;
%}

%%
verb        { return VERB; }
adj         { return ADJECTIVE; }
adv         { return ADVERB; }
noun        { return NOUN; }
prep        { return PREPOSITION; }
pron        { return PRONOUN; }
conj        { return CONJUNCTION; }
a   | 
an  | 
the         { return ARTICLE; }
[ \t]+      ;
%%