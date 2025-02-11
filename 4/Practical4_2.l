%option noyywrap
%{
    #include<stdio.h>
%}

/* rule section */
%%
([cC][hH][aA][rR][uU][sS][aA][tT]) {printf("university");}
. {printf("%s", yytext);}


%%

int main(){
    printf("Enter String:");
    yylex();  //call rule section
    return 0;
}