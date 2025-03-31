/*
Autor: Diego Enrque da Silva Lima 
Última alteração: 31/03/2025
*/

#include "symbol_table.h"
#include <iostream>

int main() {
    SymbolTable symTable;
    
    // Teste: Inserir variáveis e funções no escopo global
    std::cout << "Inserindo no escopo global..." << std::endl;
    symTable.insertVariable("x", 0, 1);         // Supondo 0 para 'int'
    symTable.insertVariable("y", 0, 2);
    symTable.insertFunction("fatorial", 1, 0);    // Função 'fatorial' com 1 parâmetro e retorno int (0)
    
    // Teste: Pesquisar símbolo
    Symbol* sym = symTable.searchSymbol("x");
    if(sym) {
        std::cout << "Símbolo encontrado: " << sym->lexeme << std::endl;
    }
    
    // Criar um novo escopo (por exemplo, um bloco interno)
    symTable.puschScope();
    std::cout << "Inserindo no novo escopo (interno)..." << std::endl;
    symTable.insertVariable("x", 0, 1);  // Pode haver outra 'x' em escopo interno
    
    // Pesquisar a variável 'x' (deve encontrar a do escopo interno)
    sym = symTable.searchSymbol("x");
    if(sym) {
        std::cout << "Símbolo encontrado no escopo interno: " << sym->lexeme << std::endl;
    }
    
    // Remover o escopo interno
   // symTable.popScope();
    
    // Imprimir o estado atual da pilha de escopos
    symTable.print();
    
    return 0;
}
