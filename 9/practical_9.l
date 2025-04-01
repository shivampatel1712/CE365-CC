%{
#include <stdio.h>
#include "y.tab.h"
%}

%%
i       { return I; }
b       { return B; }
t       { return T; }
a       { return A; }
e       { return E_TOKEN; }  /* Changed from E to E_TOKEN */
\n      { return 0; }  /* End of input */
[ \t]   { /* Ignore whitespace */ }
.       { return yytext[0]; }  /* Catch any other character */
%%

int yywrap() {
    return 1;
}
