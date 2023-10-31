//
// Created by Jonat on 16/10/2023.
//

#include "Symbol.h"

Symbol::Symbol(const std::string& symbol) : symbol(symbol) {}

const std::string& Symbol::getSymbol() const {
    return symbol;
}

NonTerminal::NonTerminal(const std::string& symbol) : Symbol(symbol) {}

bool NonTerminal::isTerminal() const {
return false;
}

bool Symbol::compare(const Symbol* lhs, const Symbol* rhs) {
    return *lhs < *rhs;
}

Terminal::Terminal(const std::string& symbol) : Symbol(symbol) {}

bool Terminal::isTerminal() const {
return true;
}