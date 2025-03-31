/*
Autor: Diego Enrque da Silva Lima 
Última alteração: 24/03/2025
*/

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <unordered_map>
#include <vector>

/*
Ideia até agora:
ter uma pilha de escopos, onde cada escopo é representado por uma tabela que mapeia 
o lexema (nome) para uma entrada de símbolo. Cada entrada terá info:
* lexema: nome do identificacor
* Tipo e/ou info de fução
* posição na declaração
* número de parâmetros (para funções)
* pontiro de entrada da função (para parâmetros)
*/ 

// tipo de símbolo. P/ distinguer entre variáveis, funções e parâmetros
enum SymbolKind {
    VAR,
    FUNCTION,
    PARAMETER
};

// estrutura para uma entrada na tabela de símbolos
struct Symbol {
    std::string lexeme;
    SymbolKind kind;
    int type; //tipo 
    int pos; // posição na declaração
    int numParams; //quantidade de parâmetros (para funções)
    Symbol* function;
};

// estrutura para cada escopo, onde cada uma será uma tabela mapeando lexemas para símbolos
struct Scope {
    std::unordered_map<std::string, Symbol> symbols;
};

// Classe para gerenciar a pilha de escopos e fornecer funções básicas
class SymbolTable{
public:
    SymbolTable();
    ~SymbolTable(); //Limpeza se necessário (o vector se encarrega da desalocação dos escopos)

    // inicializa a piplha 
    void init();   

    // cria um novo escopo e empilha na pilha de tabelas
    void puschScope();

    // remove o escoppo atual (topo da pilha)
    void popScope();

    //pesquisa um símbolo, retornando um ponteiro para o símbolo ou um nullptr 
    Symbol* searchSymbol(const std::string &lexeme);

    //insere uma função no escopo
    bool insertFunction(const std::string &name, int numParams, int retType);

    // insere variável no escopo
    bool insertVariable(const std::string &name, int type, int pos);

    // insere um parâmetro no escopo (associando a função correspondente)
    bool insertParameter(const std::string &name, int type, int pos, Symbol* functionSymbol);

    // imprime a pilha de símbolos (para ver os erros)
    void print();

private:
    //pilha de escopos
    std::vector<Scope> scopes;

};

#endif 