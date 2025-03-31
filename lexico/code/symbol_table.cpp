/*
Autor: Diego Enrque da Silva Lima 
Última alteração: 24/03/2025
*/

#include "symbol_table.h"
#include <iostream>

SymbolTable::SymbolTable() {
    init();
}

 //Limpeza se necessário (o vector se encarrega da desalocação dos escopos)
SymbolTable::~SymbolTable() {}
 
//cria o escopo global inicial
void SymbolTable::init() {
    scopes.clear();
    puschScope();
}

//pusch no scopo
void SymbolTable::puschScope() {
    Scope newScope;
    scopes.push_back(newScope);
}

//pop no escopo
void SymbolTable::popScope() {
    if (!scopes.empty()) {
        scopes.pop_back();
    }
    else {
        std::cerr <<"Erro: Pilha de escopos vazia ao tentar desempilhar. " << std::endl;
    }
}

//procura o lexema
Symbol* SymbolTable::searchSymbol(const std::string &lexeme){
    // procura do topo para base
    for (int i = scopes.size() - 1; i>= 0; --i){
        auto it = scopes[i].symbols.find(lexeme);
        if (it != scopes[i].symbols.end()){
            return &(it->second);
        }
    }
    return nullptr;
}

bool SymbolTable::insertFunction(const std::string &name, int numParams, int retType){
    //insere a função no escopo atual no topo
    if (scopes.empty()) return false;

    // verifica se já existe um símbolo com o mesmo nome no escopo atual
    Scope &atualScope = scopes.back();
    if (atualScope.symbols.find(name) != atualScope.symbols.end()) {
        std::cerr << "Erro: Funcao'" << name << "' ja declarada no escopo atual. " << std::endl;
        return false;
    }

    Symbol sym;
    sym.lexeme = name;
    sym.kind = FUNCTION;
    sym.numParams = numParams;
    sym.type = retType;
    sym.pos = -1;
    sym.function = nullptr;

    atualScope.symbols[name] = sym;
    return true;
}

bool SymbolTable::insertVariable(const std::string &name, int type, int pos) {
    if (scopes.empty()) return false;

    Scope &atualScope = scopes.back();
    if (atualScope.symbols.find(name) != atualScope.symbols.end()){
        std::cerr << "Erro: Variavel '" << name << "' ja declarada no escopo atual. " << std::endl;
        return false;
    }

    Symbol sym;
    sym.lexeme = name;
    sym.kind = VAR;
    sym.type = type;
    sym.pos = pos;
    sym.numParams = 0;
    sym.function = nullptr;

    atualScope.symbols[name] = sym;
    return true;
}

bool SymbolTable::insertParameter(const std::string &name, int type, int pos, Symbol* funcSymbol){
    if (scopes.empty()) return false;

    Scope &atualScope = scopes.back();
    if (atualScope.symbols.find(name) != atualScope.symbols.end()){
        std::cerr << "Erro: Parametro '" << name << "' ja declarado no escopo atual." << std::endl;
        return false;
    }

    Symbol sym;
    sym.lexeme = name;
    sym.kind = PARAMETER;
    sym.type = type;
    sym.pos = pos;
    sym.numParams = 0;
    sym.function = funcSymbol;

    atualScope.symbols[name] = sym;
    return true;
}

// Printa na tela os símbolos em cada escopo para correção
void SymbolTable::print() {
    std::cout << "=== Pilha de escopos ===" << std::endl;
    for (size_t i = 0; i < scopes.size(); i++){
        std::cout << "Escopo " << i << ": " << std::endl;
        for (const auto &pair : scopes[i].symbols){
            std::cout << " " << pair.first << " -> ";
            switch (pair.second.kind)
            {
            case VAR:
                std::cout << "VAR, "; 
                break;
            case FUNCTION: 
                std::cout << "FUNCTION ";
                break;
            case PARAMETER:
                std::cout << "PARAMETER, ";
                break;
            }
            std::cout << "Tipo: " << pair.second.type;
            if (pair.second.kind == FUNCTION){
                std::cout << "NumParams: " << pair.second.numParams;
            }
            if (pair.second.kind == VAR || pair.second.kind == PARAMETER){
                std::cout << ", Pos: " << pair.second.pos;
            }
            std::cout << std::endl;
        }
    }
    std::cout << "=====================================" << std::endl;
}