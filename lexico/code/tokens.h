/*
Autor: Diego Enrque da Silva Lima 
Última alteração: 31/03/2025
*/

#ifndef TOKENS_H
#define TOKENS_H

#include <cstdlib>
#include <cstring>

// Tokens das palavras reservadas e demais elementos
enum TokenType {
    // Palavras reservadas da linguagem Goianinha
    PROGRAMA = 256,
    CAR,
    INT,
    RETORNE,
    LEIA,
    ESCREVA,
    NOVALINHA,
    SE,
    ENTAO,
    SENAO,
    ENQUANTO,
    EXECUTE,
    // Outros tokens
    ID,
    NUMINT,
    CONSTSTRING,
    // Operadores e delimitadores
    OP_AD,      // +
    OP_SUB,     // -
    OP_MUL,     // *
    OP_DIV,     // /
    OP_MOD,     // %
    OP_ASSIGN,  // =
    OP_EQ,      // ==
    OP_NE,      // !=
    OP_LT,      // <
    OP_LE,      // <=
    OP_GT,      // >
    OP_GE,      // >=
    SEMICOLON,  // ;
    COMMA,      // ,
    LPAREN,     // (
    RPAREN,     // )
    LBRACE,     // {
    RBRACE      // }
};

// União para armazenar valores semânticos: números ou lexemas
union YYSTYPE {
    int ival;
    char* sval;
};

#define YYSTYPE YYSTYPE

// Declaração externa da variável utilizada pelo analisador para valores semânticos
extern YYSTYPE yylval;

#endif // TOKENS_H
