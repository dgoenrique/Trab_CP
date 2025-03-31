/*
Autor: Diego Enrque da Silva Lima 
Última alteração: 31/03/2025
*/

#include <cstdio>
#include "tokens.h"

// Declaração externa da função yylex() gerada pelo Flex
extern int yylex();

// Variável externa para o arquivo de entrada
extern FILE *yyin;

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Uso: %s <arquivo fonte>\n", argv[0]);
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    
    yyin = file;
    
    int token;
    while ((token = yylex()) != 0) {
        switch (token) {
            case ID:
                printf("Token: %d, Lexema: %s\n", token, yylval.sval);
                break;
            case NUMINT:
                printf("Token: %d, Número: %d\n", token, yylval.ival);
                break;
            case CONSTSTRING:
                printf("Token: %d, ConstString: %s\n", token, yylval.sval);
                break;
            default:
                printf("Token: %d\n", token);
                break;
        }
    }
    
    fclose(file);
    return 0;
}
