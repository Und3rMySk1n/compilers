%{

#include "lexglobal.h"
#include <stdio.h>


#define YY_DECL int yylex(struct LexContext *ctx)
#define fileno _fileno
#pragma warning(disable:4013)

%}

%option noyywrap

%%
           
"+" {
  return TK_PLUS;
}

"-" {
  return TK_MINUS;
}

"*" {
  return TK_STAR;
}

"/" {
  return TK_SLASH;
}

"%" {
  return TK_PERCENT;
}

"(" {
  return TK_LPAREN;
}

")" {
  return TK_RPAREN;
}

[0-9]+ {
  ctx->tokenValue = atoi(yytext);   
  return TK_NUMBER;
}

[ \t\n\r]

%%


