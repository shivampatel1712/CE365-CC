%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex(void);
extern char *yytext;
%}

%token I B T A E_TOKEN  /* Changed from E to E_TOKEN */

%%
start   : S       { printf("Valid string\n"); return 0; }
        ;

S       : I E T S Sprime
        | A
        ;

Sprime  : E_TOKEN S  /* Changed from E to E_TOKEN */
        | /* epsilon */
        ;

E       : B
        ;
%%

void yyerror(const char *s) {
    printf("Invalid string\n");
}

int main(void) {
    int result = yyparse();
    return result;
}
