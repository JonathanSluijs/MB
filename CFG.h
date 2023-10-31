//
// Created by Jonat on 16/10/2023.
//
#include <set>
#include "iostream"
#include "vector"
#include "Symbol.h"
#include "Production.h"
#include "ReadJson.h"


#ifndef INC_1_CFG_H
#define INC_1_CFG_H



class CFG {
public:
    CFG(std::string filepath);

    CFG();

    void print() const;

    std::vector<Symbol*> sortSymbols(const std::vector<std::string>& symbols) const;

    Symbol* findSymbol(const std::string& inputSymbol,bool isTerminal) const;

    Symbol* findSymbol(const std::string& inputSymbol) const;

    bool addToTerminals(const std::string& symbol);

    bool addToProductions( Production* Production);

    bool addToNonTerminals(const std::string& symbol);

    const std::set<Symbol *, decltype(&Symbol::compare)> &getNonTerminals() const;

    void setNonTerminals(const std::set<Symbol *, decltype(&Symbol::compare)> &nonTerminals);

    const std::set<Symbol *, decltype(&Symbol::compare)> &getTerminals() const;

    void setTerminals(const std::set<Symbol *, decltype(&Symbol::compare)> &terminals);

    const std::set<Production*, decltype(&Production::compare)> &getProductions() const;

    void setProductions(std::set<Production*, decltype(&Production::compare)> &productions);

    Symbol *getStartSymbol() const;

    void setStartSymbol(Symbol *startSymbol);


private:

private:
    std::set<Symbol*, decltype(&Symbol::compare)> nonTerminals{Symbol::compare};
    std::set<Symbol*, decltype(&Symbol::compare)> terminals{Symbol::compare};
    std::set<Production*, decltype(&Production::compare)> productions{Production::compare};
    Symbol* startSymbol;
};


#endif //INC_1_CFG_H
