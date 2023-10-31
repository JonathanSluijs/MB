//
// Created by Jonat on 16/10/2023.
//

#include "iostream"
#include "set"

#include <string>
#include <vector>

#ifndef INC_1_SYMBOL_H
#define INC_1_SYMBOL_H



// Base class for symbols
class Symbol {
public:
    Symbol(const std::string& symbol);

    static bool compare(const Symbol* lhs, const Symbol* rhs);

    bool operator<(const Symbol& other) const {
        // Compare symbols based on their names
        return symbol < other.symbol;
    }

    const std::string& getSymbol() const;

    virtual bool isTerminal() const = 0;

private:
    std::string symbol;
};

// Subclass representing non-terminals
class NonTerminal : public Symbol {
public:
    NonTerminal(const std::string& symbol);

    bool isTerminal() const override;

};

// Subclass representing terminals
class Terminal : public Symbol {
public:
    Terminal(const std::string& symbol);

    bool isTerminal() const override;
};




#endif //INC_1_SYMBOL_H
