%{
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "tokens.h"


int linha = 1;
%}

%option noyywrap
%option c++


%x COMMENT


DIGIT      [0-9]
LETTER     [a-zA-Z]
ID         {LETTER}({LETTER}|{DIGIT})*
NUMINT     {DIGIT}+


STRING     \"([^\"\n]|(\\.))*\"

%%


"programa"      { return PROGRAMA; }
"car"           { return CAR; }
"int"           { return INT; }
"retorne"       { return RETORNE; }
"leia"          { return LEIA; }
"escreva"       { return ESCREVA; }
"novalinha"     { return NOVALINHA; }
"se"            { return SE; }
"entao"         { return ENTAO; }
"senao"         { return SENAO; }
"enquanto"      { return ENQUANTO; }
"execute"       { return EXECUTE; }


{ID}            { yylval.sval = strdup(yytext); return ID; }


{NUMINT}        { yylval.ival = atoi(yytext); return NUMINT; }


{STRING}        { yylval.sval = strdup(yytext); return CONSTSTRING; }


\"([^\"\n]|(\\.))*\n {
    printf("ERRO: CADEIA DE CARACTERES OCUPA MAIS DE UMA LINHA %d\n", linha);
    // Pode-se optar por retornar um token especial de erro ou sair
}


"/*"            { BEGIN(COMMENT); }


<COMMENT>{
    "*/"       { BEGIN(INITIAL); }
    \n         { linha++; }  // Incrementa o contador de linha dentro do comentário
    .          { /* Consome demais do comentário */ }
}


<COMMENT><<EOF>> {
    printf("ERRO: COMENTARIO NAO TERMINA %d\n", linha);
    exit(1);
}


[ \t\r]+        { /* Ignorar */ }


\n              { linha++; }


"=="            { return OP_EQ; }
"!="            { return OP_NE; }
"<="            { return OP_LE; }
">="            { return OP_GE; }
"+"             { return OP_AD; }
"-"             { return OP_SUB; }
"*"             { return OP_MUL; }
"/"             { return OP_DIV; }
"%"             { return OP_MOD; }
"="             { return OP_ASSIGN; }
"<"             { return OP_LT; }
">"             { return OP_GT; }


";"             { return SEMICOLON; }
","             { return COMMA; }
"("             { return LPAREN; }
")"             { return RPAREN; }
"{"             { return LBRACE; }
"}"             { return RBRACE; }


.               { printf("ERRO: CARACTERE INVALIDO %d\n", linha); }

%%
