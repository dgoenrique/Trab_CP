/*
Autor: Diego Enrque da Silva Lima 
Última alteração: 31/03/2025
*/


#include <cstdio>
#include "tokens.h"

//declaração externa da função yylex() gerada pelo Flex
extern int yylex();

//variável externa que aponta para o arquivo de entrada
extern FILE *yyin;

//variável externa que mantém o controle do número da linha (se utilizada no Flex)
extern int linha;

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
    //loop para chamar yylex() até o fim do arquivo
    while ((token = yylex()) != 0) { 
        //dependendo do token, imprime o lexema (se aplicável)
        switch (token) {
            case ID:
                printf("Token: %d, Lexema: %s, Linha: %d\n", token, yylval.sval, linha);
                break;
            case NUMINT:
                printf("Token: %d, Número: %d, Linha: %d\n", token, yylval.ival, linha);
                break;
            case CONSTSTRING:
                printf("Token: %d, ConstString: %s, Linha: %d\n", token, yylval.sval, linha);
                break;
            default:
                //para os demais tokens, apenas imprime o código do token e a linha
                printf("Token: %d, Linha: %d\n", token, linha);
                break;
        }
    }
    
    fclose(file);
    return 0;
}
