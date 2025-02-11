%option noyywrap
%{
    #include<stdio.h>
    int Charcnt = 0;
    int Wordcnt = 0;
    int Linecnt = 0;
%}

/* rule section */
%%
([a-zA-Z0-9]+) {Charcnt += yyleng; Wordcnt++;}
([^a-zA-Z0-9\n]) {Charcnt++;}
\n {Charcnt++; Linecnt++; return 0;}
%%

int main(){
    printf("Enter String:");
    yylex();  
    printf("Character:%d\n Words:%d\n Lines:%d\n",Charcnt,Wordcnt,Linecnt);

    return 0;
}