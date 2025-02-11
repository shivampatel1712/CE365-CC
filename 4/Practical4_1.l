%option noyywrap
%{
    #include<stdio.h>
%}

%%
([a-zA-Z]+) {}
([^0-9\n]+) {}
([0-9]+) {printf("%d\n ",atoi(yytext));}
\n

%%

int main(){
    
    printf("Enter String:");
    yylex();
    return 0;
}